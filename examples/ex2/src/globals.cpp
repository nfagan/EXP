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

    namespace gl {
        auto context = make_shared<GLContextManager>();
        auto pipeline = make_shared<GLPipeline>(gl::context);
        
        auto target = pipeline->GetTarget();
        auto mouse = make_shared<InputXY>();
        auto keyboard = make_shared<InputKeyboard>(gl::target);
        
        namespace ids {
            unsigned fixation_square = 0;
            unsigned rectangle = 0;
        }
    }

    namespace task {
        auto time = make_shared<Time::Keeper>();
        auto task = make_shared<Task>(time);
        auto task_data = make_shared<TASK_DATA>();
        
        namespace ids {
            unsigned fixation = 0;
            unsigned choice = 0;
        }
    }

    namespace db {
        auto conn = make_shared<sql::connection>("test1.db");
        auto curs = conn->get_cursor();
        auto database = make_shared<db::DATABASE>(curs);
    }
    
}
