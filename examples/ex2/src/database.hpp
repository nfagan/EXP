//
//  database.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef database_h
#define database_h

#include "ex2.hpp"

namespace ex2 {
    
    using std::string;
    using namespace EXP;
    using std::shared_ptr;
    using std::make_shared;
    
    namespace db {
        EXPSQL_MAKE_FIELD(trial_number, int);
        
        EXPSQL_MAKE_FIELD(choice_type, string);
        //     EXPSQL_MAKE_FIELD(choice_time, sql::hexfloat_t);   //  store exact representation
        EXPSQL_MAKE_FIELD(choice_time, double);
        EXPSQL_MAKE_TABLE(trial_data, trial_number, choice_type, choice_time);
        
//        EXPSQL_MAKE_FIELD(fixation_onset)
    }
    
    namespace globals {
        struct db : public singleton<db>
        {
            friend struct singleton<db>;
        public:
            shared_ptr<sql::connection> conn;
            shared_ptr<sql::cursor> curs;
            shared_ptr<::ex2::db::trial_data> trial_data;
        private:
            db()
            {
                conn = make_shared<sql::connection>("test2.db");
                curs = conn->get_cursor();
                trial_data = make_shared<::ex2::db::trial_data>(curs);
            }
        };
    }
}

#endif /* database_h */
