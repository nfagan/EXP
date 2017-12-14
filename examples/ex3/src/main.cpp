//
//  main.cpp
//  EXP
//
//  Created by Nick Fagan on 10/28/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <stdlib.h>

#include "ex3.hpp"

using namespace EXP;
using namespace ex3;

int main(int argc, const char * argv[])
{
    auto gl = make_shared<globals::gl>();
    auto task = make_shared<globals::task>();
    auto task_looper = task_loop(task, gl);
    auto render_looper = render_loop(gl);
    
    //  opengl initialization; opens a 400x400 window
	gl->pipeline->Begin(0, 400, 400);

	if (!gl->pipeline->IsInitialized())
	{
		std::cout << "Failed to initialize the render context." << std::endl;
		return EXIT_FAILURE;
	}

	//  Start the time thread
	task->time->Start();

	//  Start the task thread, and wait until setup is finished.
	task_looper.setup();
    std::thread t1([&task_looper] {
        task_looper.main();
    });

	//  Start the render loop. The loop proceeds until it
	//  is canceled by the task thread (e.g., by pressing the esc key)
    render_looper.loop();

	//  Wait for the task thread to finish
	t1.join();

	return EXIT_SUCCESS;
}
