//
//  choice.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef choice_h
#define choice_h

#include "EXP.hpp"
#include "globals.hpp"
#include <memory>

namespace ex2 {
    
using std::shared_ptr;
using namespace EXP;

namespace states {

	//
	//	fixation
	//
    
    namespace fixation {
        
        auto entry_render_function = [] (auto looper) {
            looper->ClearQueue();
            auto rsrc = gl::pipeline->GetResource();
            auto rect = rsrc->Get<Model>(gl::ids::fixation_square);
            looper->Queue(rect);
        };
        
        auto on_entry = [] (auto state) {
            gl::pipeline->GetRenderLoop()->OnceDrawReady(entry_render_function);
        };

		auto on_loop = [] (auto state) {
			std::cout << task::task->EllapsedTime().count() << std::endl;
		};
        
        auto setup = [] (auto state) {
            state->OnEntry(on_entry);
			state->OnLoop(on_loop);
            state->SetTimeIn(EXP::Time::duration_ms(5000));
            state->ExitOnTimeExceeded();
            
            auto rsrc = gl::pipeline->GetResource();
            auto fix_square = rsrc->CreateRectangle();
            auto shader = rsrc->CreateGenericShader();
            fix_square->SetShader(shader);
            fix_square->SetUnits(util::units::MIXED);
            fix_square->SetScale(10.0f);
            fix_square->SetPosition(Positions2D::CENTER);
            gl::ids::fixation_square = fix_square->GetUUID();
        };
    }

	//
	//	choice
	//
    
    namespace choice {
        
        auto entry_render_function = [] (auto looper) {
            looper->ClearQueue();
            auto rsrc = gl::pipeline->GetResource();
            auto rect = rsrc->Get<Model>(gl::ids::rectangle);
            looper->Queue(rect);
        };
        
        auto on_entry = [] (auto state) {
            gl::pipeline->GetRenderLoop()->OnceDrawReady(entry_render_function);
        };
        
        auto setup = [] (auto state) {
            state->OnEntry(states::choice::on_entry);
            state->SetTimeIn(EXP::Time::duration_ms(1000));
            state->ExitOnTimeExceeded();
        };
    }
}
}

#endif /* choice_h */
