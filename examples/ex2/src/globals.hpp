//
//  globals.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef globals_h
#define globals_h

#include "EXP.hpp"
#include "database.hpp"
#include "data.hpp"

namespace ex2 {
    
    using namespace EXP;
    using std::shared_ptr;

    namespace gl {
        extern shared_ptr<GLContextManager> context;
        extern shared_ptr<GLPipeline> pipeline;
        
        extern shared_ptr<InputXY> mouse;
        extern shared_ptr<InputKeyboard> keyboard;
        
        namespace ids {
            extern unsigned shader;
            extern unsigned fixation_square;
            extern unsigned triangle;
            extern unsigned error_square;
        }
    }
    
    namespace task {
        extern shared_ptr<Time::Keeper> time;
        extern shared_ptr<Task> task;
        extern shared_ptr<TASK_DATA> task_data;
        
        namespace ids {
            extern unsigned fixation;
            extern unsigned choice;
            extern unsigned mistake;
        }
    }
    
    namespace db {
        extern shared_ptr<sql::connection> conn;
        extern shared_ptr<sql::cursor> curs;
        extern shared_ptr<db::DATABASE> database;
    }

}

#endif /* globals_h */
