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
#include <sqlite3/sqlite3.h>

namespace EXP {
namespace sql {

class cursor;
    
namespace {
    template<typename T> std::string to_string_impl(T data);
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
        char *text = sqlite3_mprintf("%Q", data.c_str());
        std::string text_(text);
        sqlite3_free(text);
        return text_;
    }
}

template<const char *name_, typename T>
class field
{
public:
    field() : did_commit(false), name(name_) {};
    
    ~field() = default;
    
    void commit(T data) { set_data(data); }
    const T& get_data(void) const { return data; }
    const std::string& get_sql_type(void) const { return sql_type; };
    
    void create_table(std::string &query) const
    {
        query += (name + " " + get_sql_type() + " NOT NULL,");
    }
    
    void insert_value(std::string &query) const
    {
        throw_if_not_committed("insertion");
        query += to_string();
        query += ",";
    }
    
    void insert_name(std::string &query) const
    {
        throw_if_not_committed("insertion");
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
    
    void set_data(T data)
    {
        if (did_commit)
        {
            std::string msg = "Already commited data for field named `" + name + "`.";
            throw std::runtime_error(msg);
        }
        if (std::is_same<T, int>::value)
        {
            sql_type = "INT";
        }
        if (std::is_same<T, std::string>::value)
        {
            sql_type = "TEXT";
        }
        if (std::is_same<T, float>::value)
        {
            sql_type = "REAL";
        }
        this->data = data;
        did_commit = true;
    }
    
    virtual const std::string to_string() const
    {
        return to_string_impl(data);
    }
    
    void throw_if_not_committed(std::string op_name = "(unnamed)") const
    {
        if (!did_commit)
        {
            std::string msg = "Operation `" + op_name + "` requires that data in `" + name + "` be committed first.";
            throw std::runtime_error(msg);
        }
    };
};
}
}

#endif /* Field_hpp */
