//
//  field_impl.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/8/17.
//

#ifndef field_impl_h
#define field_impl_h

//
//  for insertion query conversion
//

namespace {
    template<typename T> std::string to_string_impl(T data)
    {
        return std::to_string(data);
    }
    template<> std::string to_string_impl<EXP::sql::hexfloat_t>(EXP::sql::hexfloat_t data)
    {
        std::stringstream ss;
        ss << std::hexfloat << data.value;
        return connection::require_quoted_text("%Q", ss.str());
    }
    template<> std::string to_string_impl<std::string>(std::string data)
    {
        return connection::require_quoted_text("%Q", data);
    }    
}

template<const char *name_, typename T>
EXP::sql::field<name_, T>::field()
{
    name = name_;
    did_commit = false;
    sql_type = sql_field_type<T>::value;
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
