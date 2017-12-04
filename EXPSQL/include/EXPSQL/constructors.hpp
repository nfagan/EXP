//
//  make_table.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/3/17.
//

#ifndef constructors_h
#define constructors_h

#include <EXPSQL/table.hpp>

#define EXPSQL_MAKE_FIELD(fieldname, type) \
    namespace { \
        extern const char fieldname##__[] = #fieldname; \
    } \
    typedef EXP::sql::field<fieldname##__, type> fieldname;

//#define EXPSQL_MAKE_TABLE(name, ...)                                        \
//    typedef EXP::sql::table<__VA_ARGS__> name;

#define EXPSQL_MAKE_TABLE(name, ...) \
    namespace { \
        extern const char name##__[] = #name; \
    } \
    class name : public EXP::sql::table<name##__, __VA_ARGS__> \
    { \
    public: \
    name (std::shared_ptr<EXP::sql::cursor> curs) : EXP::sql::table<name##__, __VA_ARGS__>(curs) {} \
    }

#endif /* constructors_h */
