//
//  ex2.hpp
//  EXP
//
//  Created by Nick Fagan on 11/1/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef ex2_h
#define ex2_h

#include <iostream>
#include <memory>
#include "EXP.hpp"
#include "globals.hpp"
#include "states.hpp"
#include "database.hpp"
#include "data.hpp"
#include "render_loop.hpp"
#include "task_loop.hpp"

namespace ex2 {
    
using namespace EXP;

int start()
{
    //  open gl init
    gl::pipeline->Begin(0, 400, 400);
    
    if (!gl::pipeline->IsInitialized())
    {
        std::cout << "Failed to initialize the render context." << std::endl;
        return EXIT_FAILURE;
    }
    
    //  Start the time thread
    task::time->Start();
    
    //  Start the task thread, and wait until setup is finished.
    task_loop::setup();
    std::thread t1(task_loop::main);
    
    //  Start the render loop. The loop proceeds until it
    //  is canceled by the task thread (e.g., by pressing the esc key)
    auto looper = gl::pipeline->GetRenderLoop();
    looper->OnLoop(render_loop::main);
    looper->Loop();
    
    //  Wait for the task thread to finish
    t1.join();
    
    return EXIT_SUCCESS;
}
        
}

#endif


