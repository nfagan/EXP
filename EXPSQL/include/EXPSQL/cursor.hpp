//
//  cursor.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/24/17.
//

#ifndef cursor_h
#define cursor_h

#include <EXPSQL/connection.hpp>
#include <EXPSQL/field.hpp>
#include <iostream>
#include <memory>

namespace EXP {
namespace sql {
    
class connection;

template<typename ...X>
class row;
    
class cursor
{
public:
    cursor(const connection *conn);
    
    template <typename ...T>
    bool const create(std::shared_ptr<row<T...>> &value, std::string name)
    {
        std::string query = "CREATE TABLE " + name;
        query += "(ID INT PRIMARY KEY NOT NULL,";
        value->for_each(field<int>::table_creator(query));
        query.erase(query.length()-1, 1);
        query += ");";
        return exec(query);
    }
    
    template<typename ...T>
    bool const insert(std::shared_ptr<row<T...>> &value, int id, std::string table)
    {
        std::string query = "INSERT INTO " + table + " (ID,";
        value->for_each(field<int>::name_inserter(query));
        query.erase(query.length()-1, 1);
        query += ") VALUES (" + std::to_string(id) + ",";
        value->for_each(field<int>::value_inserter(query));
        query.erase(query.length()-1, 1);
        query += ");";
        return exec(query);
    }
    
private:
    const connection *conn = nullptr;
    
    bool exec(const std::string &query);
};

}
}


#endif /* cursor_h */
