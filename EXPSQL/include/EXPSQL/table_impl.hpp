//
//  table_impl.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/8/17.
//

#ifndef table_impl_h
#define table_impl_h

template<const char *name_, typename ...T>
EXP::sql::table<name_, T...>::table(std::shared_ptr<cursor> curs)
{
    this->curs = curs;
    this->name = std::string(name_);
    row_ = std::make_shared<row<T...>>();
    status = true;
    require();
    get_size();
}

template<const char *name_, typename ...T>
template<typename N, typename X>
bool EXP::sql::table<name_, T...>::commit(X data)
{
    bool result = row_->template commit<N>(data);
    return result;
}

template<const char *name_, typename ...T>
bool EXP::sql::table<name_, T...>::insert()
{
    if (!curs->insert(row_, size, name))
        return false;
    row_->reset();
    size++;
    return true;
}

template<const char *name_, typename ...T>
bool EXP::sql::table<name_, T...>::create()
{
    return curs->create(row_, name);
}

template<const char *name_, typename ...T>
bool EXP::sql::table<name_, T...>::drop()
{
    if (curs->drop(name))
    {
        size = 0;
        return true;
    }
    return false;
}

template<const char *name_, typename ...T>
void EXP::sql::table<name_, T...>::get_size()
{
    if (!status) return;
    status = curs->size(name, &size);
}

template<const char *name_, typename ...T>
void EXP::sql::table<name_, T...>::require()
{
    if (!status) return;
    status = curs->require(row_, name);
}

#endif /* table_impl_h */
