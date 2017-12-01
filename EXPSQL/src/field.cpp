//
//  field.cpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/24/17.
//

#include <EXPSQL/field.hpp>
#include <sqlite3/sqlite3.h>
#include <string>

const std::string EXP::sql::field<std::string>::to_string() const
{
    char *text = sqlite3_mprintf("%Q", data.c_str());
    std::string text_(text);
    sqlite3_free(text);
    return text_;
}
