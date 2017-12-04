//
//  Field.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/15/17.
//

#ifndef exp_Field_hpp
#define exp_Field_hpp

#include <type_traits>
#include <string>
#include <assert.h>
#include <vector>
#include <EXPSQL/connection.hpp>

namespace EXP {
namespace sql {

class cursor;
    
namespace {
    template<typename T> std::string to_string_impl(T data);
    template<> std::string to_string_impl<double>(double data)
    {
        return std::to_string(data);
    }
    template<> std::string to_string_impl<float>(float data)
    {
        return std::to_string(data);
    }
    template<> std::string to_string_impl<int>(int data)
    {
        return std::to_string(data);
    }
    template<> std::string to_string_impl<std::string>(std::string data)
    {
        return connection::require_quoted_text("%Q", data);
    }
}

template<const char *name_, typename T>
class field
{
public:
    field() : did_commit(false), name(name_) {};
    
    ~field() = default;
    
    bool commit(T data)
    {
        return set_data(data);
    }
    const T& get_data() const
    {
        return data;
    }
    const std::string& get_sql_type() const
    {
        return sql_type;
    }
    const std::string get_name() const
    {
        return name;
    }
    void create_table(std::string &query) const
    {
        query += (name + " " + get_sql_type() + " NOT NULL,");
    }
    void insert_value(std::string &query) const
    {
        query += to_string();
        query += ",";
    }
    void insert_name(std::string &query) const
    {
        query += name;
        query += ",";
    }
    void reset()
    {
        did_commit = false;
    }
    
    bool did_commit;
protected:
    static constexpr const char *name__ = name_;
    std::string name;
    std::string sql_type;
    T data;
    
    bool set_data(T data)
    {
        if (did_commit)
        {
            std::string msg = "Already commited data for field named `" + name + "`.";
            return false;
        }
        if (std::is_same<T, int>::value)
        {
            sql_type = "INT";
        }
        if (std::is_same<T, std::string>::value)
        {
            sql_type = "TEXT";
        }
        if (std::is_same<T, float>::value || std::is_same<T, double>::value)
        {
            sql_type = "REAL";
        }
        this->data = data;
        did_commit = true;
        return true;
    }
    
    const std::string to_string() const
    {
        return to_string_impl(data);
    }
};
}
}

#endif /* Field_hpp */
