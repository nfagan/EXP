//
//  task_loop.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef task_loop_h
#define task_loop_h

#include "ex3.hpp"

namespace ex3 {
    
    using namespace EXP;
    using std::shared_ptr;
    
    struct task_loop
    {
        shared_ptr<globals::task> task;
        shared_ptr<globals::gl> gl;
        
        states::fixation fixation;
        
        task_loop(shared_ptr<globals::task> task, shared_ptr<globals::gl> gl)
        {
            this->task = task;
            this->gl = gl;
        }
        
        void setup()
        {
            auto runner = task->runner;
            
            //    setup fixation
            auto state_fixation = runner->CreateState(&(task->ids.fixation));
            fixation = states::fixation(state_fixation, task, gl);
            fixation.setup();

            runner->OnExit([this] (auto task) {
                gl->pipeline->GetRenderLoop()->CancelLoop();
            });
            
            runner->ExitOnKeyPress(gl->keyboard, Keys::ESC);
            runner->Next(fixation.state);
        }
        
        void main()
        {
            task->runner->Run();
            task->runner->LogTime();
        }
    };
}

#endif /* task_loop_h */
