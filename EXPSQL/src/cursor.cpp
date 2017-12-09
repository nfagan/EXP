//
//  cursor.cpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/24/17.
//

#include <stdio.h>
#include <sqlite3/sqlite3.h>
#include <EXPSQL/cursor.hpp>
#include <EXPSQL/field.hpp>
//#include <EXPSQL/row.hpp>

EXP::sql::cursor::cursor(const EXP::sql::connection *conn) : conn(conn)
{
    //
}

bool EXP::sql::cursor::exec(const std::string &query, std::string *result) const
{
    return conn->exec(query, result);
}

bool EXP::sql::cursor::drop(std::string name)
{
    return conn->drop(name);
}

bool EXP::sql::cursor::size(std::string name, int *sz)
{
    if (sz == nullptr) return false;
    bool err;
    conn->size(name, &err, sz);
    return err;
}



