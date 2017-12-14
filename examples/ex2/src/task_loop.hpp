//
//  task_loop.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef task_loop_h
#define task_loop_h

#include "ex2.hpp"
#include <atomic>

namespace ex2 {
    namespace task_loop {
        using namespace EXP;

        auto on_exit = [] (auto task) {
            auto &gl = globals::gl::get();
            gl.pipeline->GetRenderLoop()->CancelLoop();
        };
        
        auto on_error = [] (auto task, auto err) {
            //
        };
        
        void setup()
        {
            auto &task = globals::task::get();
            auto &gl = globals::gl::get();
            auto runner = task.runner;
            
            //	setup fixation
            auto state_fixation = runner->CreateState(&task.ids.fixation);
            states::fixation::setup(state_fixation);
            
            //  setup choice
            auto state_choice = runner->CreateState(&task.ids.choice);
            states::choice::setup(state_choice);
            
            //  setup error
            auto state_mistake = runner->CreateState(&task.ids.mistake);
            states::mistake::setup(state_mistake);
            
            //	setup task
            runner->OnExit(on_exit);
            runner->OnError(on_error);
            runner->ExitOnKeyPress(gl.keyboard, Keys::ESC);
            runner->Next(state_fixation);
        }
        
        void main()
        {
            auto &task = globals::task::get();
            task.runner->Run();
            task.runner->LogTime();
        }
    }
}

#endif /* task_loop_h */
