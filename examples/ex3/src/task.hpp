//
//  task.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/9/17.
//

#ifndef ex2_task_h
#define ex2_task_h

#include "ex3.hpp"

namespace ex3 {
    namespace globals {
        
        using namespace EXP;
        using std::shared_ptr;
        using std::make_shared;
        
        struct task
        {
            shared_ptr<Time::Keeper> time;
            shared_ptr<Task> runner;
            shared_ptr<TASK_DATA> task_data;
            
            struct ids_ {
                unsigned fixation = 0;
                unsigned choice = 0;
                unsigned mistake = 0;
            } ids;
            
            task()
            {
                time = make_shared<Time::Keeper>();
                runner = make_shared<Task>(time);
                task_data = make_shared<TASK_DATA>();
            }
        };
        
    }
}

#endif /* task_h */
