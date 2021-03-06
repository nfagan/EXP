//
//  main.cpp
//  EXP
//
//  Created by Nick Fagan on 10/28/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <stdlib.h>

#include "ex2.hpp"

using namespace EXP;
using namespace ex2;

int main(int argc, const char * argv[])
{
    auto &gl = globals::gl::get();
    auto &task = globals::task::get();
    
    //  opengl initialization; opens a 400x400 window
	gl.pipeline->Begin(0, 400, 400);

	if (!gl.pipeline->IsInitialized())
	{
		std::cout << "Failed to initialize the render context." << std::endl;
		return EXIT_FAILURE;
	}

	//  Start the time thread
	task.time->Start();

	//  Start the task thread, and wait until setup is finished.
	task_loop::setup();
    
    std::thread t1(task_loop::main);

	//  Start the render loop. The loop proceeds until it
	//  is canceled by the task thread (e.g., by pressing the esc key)
	auto looper = gl.pipeline->GetRenderLoop();
	looper->OnLoop(render_loop::main);
	looper->Loop();

	//  Wait for the task thread to finish
    t1.join();

	return EXIT_SUCCESS;
}
