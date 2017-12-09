//
//  cursor_impl.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/8/17.
//

#ifndef cursor_impl_h
#define cursor_impl_h

template<typename ...T>
bool EXP::sql::cursor::require(std::shared_ptr<row<T...>> &value, std::string name)
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

template <typename ...T>
bool EXP::sql::cursor::create(std::shared_ptr<row<T...>> &value, std::string name) const
{
    std::string query = "CREATE TABLE " + name;
    query += "(ID INT PRIMARY KEY NOT NULL,";
    value->for_each([&query] (auto &x) { x.create_table(query); });
    query.erase(query.length()-1, 1);
    query += ");";
    return exec(query, nullptr);
}

template<typename ...T>
bool EXP::sql::cursor::insert(std::shared_ptr<row<T...>> &value, int id, std::string table) const
{
    std::string non_committed;
    bool all_committed = value->all_committed(non_committed);
    if (!all_committed)
    {
        std::stringstream msg;
        msg << "Inserting data requires that fields `" << non_committed  << "` be committed first.";
        conn->log.error << msg.str();
        return false;
    }
    std::string query = "INSERT INTO " + table + " (ID,";
    value->for_each([&query] (auto &x) { x.insert_name(query); });
    query.erase(query.length()-1, 1);
    query += ") VALUES (" + std::to_string(id) + ",";
    value->for_each([&query] (auto &x) { x.insert_value(query); });
    query.erase(query.length()-1, 1);
    query += ");";
    return exec(query, nullptr);
}

#endif /* cursor_impl_h */
