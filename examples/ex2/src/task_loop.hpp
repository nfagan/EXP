//
//  task_loop.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef task_loop_h
#define task_loop_h

#include "EXP.hpp"
#include "globals.hpp"
#include "states.hpp"

namespace ex2 {
namespace task_loop {
    
    using namespace EXP;
    
    void setup()
    {
        auto state_fixation = task::task->CreateState(&task::ids::fixation);
        states::fixation::setup(state_fixation);
        
        task::task->OnExit([] (auto task) {
            gl::pipeline->GetRenderLoop()->CancelLoop();
        });
        
        task::task->SetTimeIn(EXP::Time::duration_s(10));
        task::task->ExitOnTimeExceeded();
        task::task->Next(state_fixation);
    }
    
    void main()
    {
        task::task->Run();
    }
}
}

#endif /* task_loop_h */
