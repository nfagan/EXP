//
//  make_table.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/3/17.
//

#ifndef make_table_h
#define make_table_h

#include <EXPSQL/table.hpp>

#define EXPSQL_MAKE_FIELD(fieldname, type)                                  \
    namespace {                                                             \
        const char fieldname##__[] = #fieldname;                            \
        typedef field<fieldname##__, type> fieldname;                       \
    }                                                                       \

#define EXPSQL_MAKE_TABLE(name, ...)                                        \
    typedef table<__VA_ARGS__> name;

#endif /* make_table_h */
