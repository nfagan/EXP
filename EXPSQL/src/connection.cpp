//
//  connection.cpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/15/17.
//

#include <EXPSQL/connection.hpp>
#include <EXPSQL/cursor.hpp>
#include <sqlite3/sqlite3.h>
#include <iostream>
#include <memory>
#include <sstream>

EXP::sql::connection::connection(std::string file, bool do_open) : file(file)
{
    this->is_open_.store(false);
    this->is_transacting_.store(false);
    if (do_open)
        open();
}

EXP::sql::connection::~connection()
{
    if (is_open_)
        close();
}

void EXP::sql::connection::log_level(EXP::severity::severity_ level)
{
    log.set_severity(level);
}

bool EXP::sql::connection::is_open() const
{
    return is_open_;
}

bool EXP::sql::connection::open()
{
    if (is_open_)
        return true;
    
    int rc = sqlite3_open(file.c_str(), &db);
    
    if (rc != SQLITE_OK)
    {
        std::stringstream base;
        std::stringstream msg;
        base << "Failed to open database `" << file << "`, with message:" << std::endl;
        msg << sqlite3_errmsg(db) << std::endl;
        log.error << base.str();
        log.error << msg.str();
        close();
        return false;
    }
    
    is_open_ = true;
    return true;
}

bool EXP::sql::connection::close()
{
    if (!is_open_)
        return true;
    
    int rc = 0;
    
    if (db)
        rc = sqlite3_close(db);
    
    if (rc != SQLITE_OK)
    {
        std::stringstream base;
        std::stringstream msg;
        base << "Failed to close database `" << file << "`, with message:" << std::endl;
        msg << sqlite3_errmsg(db) << std::endl;
        log.error << base.str();
        log.error << msg.str();
        return false;
    }
    
    is_open_ = false;
    return true;
}

std::shared_ptr<EXP::sql::cursor> EXP::sql::connection::get_cursor() const
{
    return std::make_shared<EXP::sql::cursor>(this);
}

bool EXP::sql::connection::exec(const std::string &query, std::string *result) const
{
    int rc;
    if (result)
    {
        rc = sqlite3_exec(db, query.c_str(), EXP::sql::connection::sqlite_callback, (void*) result, NULL);
    }
    else
    {
        rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    }
    if (rc != SQLITE_OK)
    {
        std::stringstream base;
        std::stringstream msg;
        base << "Failed to execute query `" << query << "`, with message:" << std::endl;
        msg << sqlite3_errmsg(db) << std::endl;
        log.error << base.str();
        log.error << msg.str();
        return false;
    }
    return true;
}

void EXP::sql::connection::exists(const std::string &name, bool *err, bool *exist) const
{
    if (err == nullptr || exist == nullptr)
        throw std::logic_error("Passed null value(s) to exists().");
    
    const char *unsafe_query = "select count(type) from sqlite_master where type='table' and name=%Q;";
    std::string safe_query = require_quoted_text(unsafe_query, name);
    *err = false;
    *exist = false;
    int iexist;
    if (!exec_to_int(safe_query, &iexist))
    {
        *err = true;
        *exist = false;
    }
    else
    {
        *err = false;
        *exist = iexist == 1;
    }
}

void EXP::sql::connection::size(const std::string &name, bool *err, int *sz) const
{
    if (err == nullptr || sz == nullptr)
        throw std::logic_error("Passed null value(s) to size().");
    
    std::string safe_query = require_quoted_text("select count(*) from %Q;", name);
    int sz_;
    if (exec_to_int(safe_query, &sz_))
    {
        *err = false;
        *sz = sz_;
    }
    else
    {
        *err = true;
        *sz = 0;
    }
}

bool EXP::sql::connection::exec_to_int(const std::string &query, int *value) const
{
    if (value == nullptr)
        throw std::logic_error("Passed a null value to exec_to_int().");
    
    std::string result;
    bool status = exec(query, &result);
    if (!status)
        return false;
    try {
        int transformed = atoi(result.c_str());
        *value = transformed;
        status = true;
    } catch (...) {
        *value = 0;
        status = false;
    }
    return status;
}

bool EXP::sql::connection::drop(const std::string &name) const
{
    std::string query = require_quoted_text("DROP TABLE %Q;", name);
    return exec(query, nullptr);
}

bool EXP::sql::connection::begin()
{
    if (is_transacting_)
    {
        std::stringstream msg;
        msg << "Attempted to begin after already beginning." << std::endl;
        log.error << msg.str();
        return false;
    }
    if (exec("BEGIN TRANSACTION;", nullptr))
    {
        is_transacting_ = true;
        return true;
    }
    return false;
}

bool EXP::sql::connection::commit()
{
    if (!is_transacting_)
    {
        std::stringstream msg;
        msg << "Attempted to commit before beginning." << std::endl;
        log.error << msg.str();
        return false;
    }
    if (exec("END TRANSACTION;", nullptr))
    {
        is_transacting_ = false;
        return true;
    }
    return false;
}

int EXP::sql::connection::sqlite_callback(void *data, int argc, char *argv[], char *col_name[])
{
    std::string *result = (std::string*) data;
    for (unsigned int i = 0; i < argc; ++i)
    {
        if (argv[i])
        {
            result->append(argv[i]);
        }
    }
    
    return 0;
}

std::string EXP::sql::connection::require_quoted_text(const char *qstring, const std::string &values)
{
    char *result = sqlite3_mprintf(qstring, values.c_str());
    return std::string(result);
}
