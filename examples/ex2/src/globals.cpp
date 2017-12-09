//
//  globals.cpp
//  EXP_ex1
//
//  Created by Nick Fagan on 12/5/17.
//

#include <stdio.h>
#include "globals.hpp"
#include <memory>

namespace ex2 {
    
    using namespace EXP;
    using std::make_shared;
	using std::shared_ptr;

    namespace gl {
        shared_ptr<GLContextManager> context = make_shared<GLContextManager>();
        shared_ptr<GLPipeline> pipeline = make_shared<GLPipeline>(gl::context);
        
        shared_ptr<InputXY> mouse = make_shared<InputXY>();
        shared_ptr<InputKeyboard> keyboard = make_shared<InputKeyboard>(pipeline->GetTarget());
        
        namespace ids {
            unsigned shader = 0;
            unsigned fixation_square = 0;
            unsigned triangle = 0;
            unsigned error_square = 0;
        }
    }

    namespace task {
        shared_ptr<Time::Keeper> time = make_shared<Time::Keeper>();
        shared_ptr<Task> task = make_shared<Task>(time);
        shared_ptr<TASK_DATA> task_data = make_shared<TASK_DATA>();
        
        namespace ids {
            unsigned fixation = 0;
            unsigned choice = 0;
            unsigned mistake = 0;
        }
    }

    namespace db {
        shared_ptr<sql::connection> conn = make_shared<sql::connection>("test1.db");
        shared_ptr<sql::cursor> curs = conn->get_cursor();
        shared_ptr<db::DATABASE> database = make_shared<db::DATABASE>(curs);
    }
    
}
