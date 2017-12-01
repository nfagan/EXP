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

namespace EXP {
namespace sql {

class cursor;

template<typename T>
class field_priv
{
public:
    field_priv(std::string name) : did_commit(false)
    {
        set_name(name);
    }
    
    field_priv(std::string name, T data) : did_commit(false)
    {
        set_name(name);
        set_data(data);
    }
    
    ~field_priv() = default;
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
    void set_name(std::string name) { this->name = name; }
    
    virtual const std::string to_string(void) const { return ""; }
    
    //
    //  Iterators
    //
    
    struct name_inserter {
        std::string &query;
        name_inserter(std::string &query) : query(query) {};
        template<typename X = field_priv<T>>
        void operator () (X&& t)
        {
            t.insert_name(this->query);
        }
    };
    
    struct value_inserter {
        std::string &query;
        value_inserter(std::string &query) : query(query) {};
        template<typename X = field_priv<T>>
        void operator () (X&& t)
        {
            t.insert_value(this->query);
        }
    };
    
    struct table_creator {
        std::string &query;
        table_creator(std::string &query) : query(query) {};
        template<typename X = field_priv<T>>
        void operator () (X&& t)
        {
            t.create_table(this->query);
        }
    };
    
    void throw_if_not_committed(std::string op_name = "(unnamed)") const
    {
        if (!did_commit)
        {
            std::string msg = "Operation `" + op_name + "` requires that data in `" + name + "` be committed first.";
            throw std::runtime_error(msg);
        }
    };
};

template<typename T> class field;

//
//  string
//

template <> class field<std::string> : public field_priv<std::string>
{
friend class cursor;
public:
    field(std::string name) : field_priv(name) {};
    field(std::string name, std::string val) : field_priv(name, val) {};
    
    const std::string to_string(void) const;
};
    
//
//  int
//
    
template <> class field<int> : public field_priv<int>
{
friend class cursor;
public:
    field(std::string name) : field_priv(name) {};
    field(std::string name, int val) : field_priv(name, val) {};
    
    const std::string to_string(void) const { return std::to_string(data); }
};

//
//  float
//
    
template <> class field<float> : public field_priv<float>
{
friend class cursor;
public:
    field(std::string name) : field_priv(name) {};
    field(std::string name, float val) : field_priv(name, val) {};
    
    const std::string to_string(void) const { return std::to_string(data); }
};

////
////  vector
////
//
//template <> class field<std::vector<double>> : public field_priv<std::vector<double>>
//{
//friend class cursor;
//public:
//    field(std::string name) : field_priv(name) {};
//    field(std::string name, std::vector<double> val) : field_priv(name, val) {};
//
//    const std::string to_string(void) const
//    {
//        std::string res = "";
//        for (unsigned i = 0; i < data.size(); ++i)
//        {
//            res += std::to_string(data[i]);
//        }
//        return res;
//    }
//};
}
}

#endif /* Field_hpp */
