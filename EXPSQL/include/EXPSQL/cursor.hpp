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
    
    template<typename ...T>
    bool require(std::shared_ptr<row<T...>> &value, std::string name)
    {
        bool exist;
        bool err;
        
        conn->exists(name, &err, &exist);
        
        if (err)
            return false;
        
        if (!exist)
            return create(value, name);
        
        return true;
    }
    
    bool size(std::string name, int *sz)
    {
        if (sz == nullptr) return false;
        bool err;
        conn->size(name, &err, sz);
        return err;
    }
    
    template <typename ...T>
    bool create(std::shared_ptr<row<T...>> &value, std::string name) const
    {
        std::string query = "CREATE TABLE " + name;
        query += "(ID INT PRIMARY KEY NOT NULL,";
        value->for_each(field<int>::table_creator(query));
        query.erase(query.length()-1, 1);
        query += ");";
        return exec(query, nullptr);
    }
    
    template<typename ...T>
    bool insert(std::shared_ptr<row<T...>> &value, int id, std::string table) const
    {
        std::string query = "INSERT INTO " + table + " (ID,";
        value->for_each(field<int>::name_inserter(query));
        query.erase(query.length()-1, 1);
        query += ") VALUES (" + std::to_string(id) + ",";
        value->for_each(field<int>::value_inserter(query));
        query.erase(query.length()-1, 1);
        query += ");";
        return exec(query, nullptr);
    }
    
private:
    const connection *conn = nullptr;
    bool exec(const std::string &query, std::string *result) const;
};

}
}


#endif /* cursor_h */
