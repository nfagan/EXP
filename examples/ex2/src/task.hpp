//
//  task.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/9/17.
//

#ifndef ex2_task_h
#define ex2_task_h

#include "ex2.hpp"

namespace ex2 {
    namespace globals {
        
        using namespace EXP;
        using std::shared_ptr;
        using std::make_shared;
        
        struct task : public singleton<task>
        {
            friend struct singleton<task>;
        public:
            shared_ptr<Time::Keeper> time;
            shared_ptr<Task> runner;
            TASK_DATA task_data;
            
            struct ids_ {
                unsigned fixation = 0;
                unsigned choice = 0;
                unsigned mistake = 0;
            } ids;
        private:
            task()
            {
                time = make_shared<Time::Keeper>();
                runner = make_shared<Task>(time);
            }
        };
        
    }
}

#endif /* task_h */
