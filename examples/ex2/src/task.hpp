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

	auto on_exit = [] (auto task) {
		gl::pipeline->GetRenderLoop()->CancelLoop();
	};
    
    void setup()
    {
		//	setup fixation
        auto state_fixation = task::task->CreateState(&task::ids::fixation);
		states::fixation::setup(state_fixation);
        
        //  setup choice
        auto state_choice = task::task->CreateState(&task::ids::choice);
        states::choice::setup(state_choice);
        
        //  setup error
        auto state_mistake = task::task->CreateState(&task::ids::mistake);
        states::mistake::setup(state_mistake);
        
		//	setup task
		task::task->OnExit(on_exit);
		task::task->SetTimeIn(Time::duration_s(10));
		task::task->ExitOnTimeExceeded();
        task::task->Next(state_fixation);
    }
    
    void main()
    {
        task::task->Run();
		task::task->LogTime();
    }
}
}

#endif /* task_loop_h */
