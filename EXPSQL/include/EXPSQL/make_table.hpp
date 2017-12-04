//
//  make_table.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/3/17.
//

#ifndef make_table_h
#define make_table_h

#include <EXPSQL/table.hpp>

#define MAKE_FIELD(typename, fieldname, type)                               \
    namespace {                                                             \
        const char fieldname[] = #fieldname;                                \
        typedef sql::field<fieldname, type> typename;                       \
    }                                                                       \

#define MAKE_TABLE(name, ...)                                               \
    typedef sql::table<__VA_ARGS__> name;

#endif /* make_table_h */
