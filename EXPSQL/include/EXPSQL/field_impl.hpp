//
//  field_impl.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/8/17.
//

#ifndef field_impl_h
#define field_impl_h

template<const char *name_, typename T>
EXP::sql::field<name_, T>::field()
{
    name = name_;
    did_commit = false;
}

template<const char *name_, typename T>
bool EXP::sql::field<name_, T>::commit(T data)
{
    return set_data(data);
}

template<const char *name_, typename T>
const T& EXP::sql::field<name_, T>::get_data() const
{
    return data;
}

template<const char *name_, typename T>
const std::string& EXP::sql::field<name_, T>::get_sql_type() const
{
    return sql_type;
}

template<const char *name_, typename T>
const std::string EXP::sql::field<name_, T>::get_name() const
{
    return name;
}

template<const char *name_, typename T>
void EXP::sql::field<name_, T>::create_table(std::string &query) const
{
    query += (name + " " + get_sql_type() + " NOT NULL,");
}

template<const char *name_, typename T>
void EXP::sql::field<name_, T>::insert_value(std::string &query) const
{
    query += to_string();
    query += ",";
}

template<const char *name_, typename T>
void EXP::sql::field<name_, T>::insert_name(std::string &query) const
{
    query += name;
    query += ",";
}

template<const char *name_, typename T>
void EXP::sql::field<name_, T>::reset()
{
    did_commit = false;
}

template<const char *name_, typename T>
bool EXP::sql::field<name_, T>::set_data(T data)
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
    if (std::is_same<T, std::string>::value || std::is_same<T, hexfloat>::value)
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

template<const char *name_, typename T>
const std::string EXP::sql::field<name_, T>::to_string() const
{
    return to_string_impl(data);
}

#endif /* field_impl_h */
