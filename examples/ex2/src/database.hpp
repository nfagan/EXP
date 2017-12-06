//
//  database.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef database_h
#define database_h

#include <EXPSQL/EXPSQL.hpp>
#include <string>

namespace ex2 {
    
    using std::string;
    
    namespace db {
        EXPSQL_MAKE_FIELD(choice_type, string);
        //     EXPSQL_MAKE_FIELD(choice_time, sql::hexfloat);   //  store exact representation
        EXPSQL_MAKE_FIELD(choice_time, double);
        EXPSQL_MAKE_FIELD(trial_number, int);
        EXPSQL_MAKE_TABLE(DATABASE, trial_number, choice_type, choice_time);
    }
}

#endif /* database_h */
