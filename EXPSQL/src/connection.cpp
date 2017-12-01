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

EXP::sql::connection::connection(std::string file, bool do_open) : file(file), is_open_(false)
{
    if (do_open)
        open();
}

EXP::sql::connection::~connection()
{
    if (is_open_)
        close();
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
        std::cout << "Failed to open database `" << file << "`, with message:" << std::endl;
        std::cout << sqlite3_errmsg(db) << std::endl;
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
        std::cout << "Failed to close database `" << file << "`, with message:" << std::endl;
        std::cout << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    is_open_ = false;
    return true;
}

std::shared_ptr<EXP::sql::cursor> EXP::sql::connection::get_cursor() const
{
    return std::make_shared<EXP::sql::cursor>(this);
}

bool EXP::sql::connection::exec(const std::string &query) const
{
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "Failed to execute query `" << query << "`, with message:" << std::endl;
        std::cout << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}
