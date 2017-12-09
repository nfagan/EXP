//
//  choice.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef choice_h
#define choice_h

#include "ex2.hpp"
#include "state_template.hpp"

namespace ex3 {
    
using std::shared_ptr;
using namespace EXP;

namespace states {

	//
	//	fixation
	//
    
//    struct fixations : public state_template
//    {
//        template<typename ...T>
//        fixations(T... args) : state_template(args...)
//        {
//            //
//        }
//    };
    
    namespace fixation {
        
        unsigned fix_targ_id;
        auto initial_fix_time = Time::duration_ms(1000);
        
        auto render_function = [] (auto looper) {
            looper->ClearQueue();
            auto &gl = globals::gl::get();
            auto rsrc = gl.pipeline->GetResource();
            auto rect = rsrc->Get<Model>(gl.ids.fixation_square);
            looper->Queue(rect);
        };
        
        auto on_entry = [] (auto state) {
            state->LogTime();
            auto &gl = globals::gl::get();
            auto &task = globals::task::get();
            gl.pipeline->GetRenderLoop()->OnceDrawReady(render_function);
            //  by default, go to mistake state.
            state->Next(task.ids.mistake);
        };

        auto on_loop = [] (auto state) {
            //
        };
        
        auto on_exit = [] (auto state) {
            //
        };
        
        auto on_target_entry = [] (auto state, auto target) {
            auto &task = globals::task::get();
            if (state->EllapsedTime() > initial_fix_time)
            {
                state->Next(task.ids.mistake);
                state->ExitNow();
                return;
            }
            state->Next(task.ids.choice);
        };
        
        auto on_target_exit = [] (auto state, auto target) {
            auto &task = globals::task::get();
            state->Next(task.ids.mistake);
            state->ExitNow();
        };
        
        auto setup = [] (auto state) {
            state->OnEntry(on_entry);
            state->OnLoop(on_loop);
            state->OnExit(on_exit);
            state->SetTimeIn(Time::duration_ms(2000));
            state->ExitOnTimeExceeded();
            
            float fix_size = 10.0f;
            auto &gl = globals::gl::get();
            auto rsrc = gl.pipeline->GetResource();
            auto fix_square = rsrc->CreateRectangle();
            auto shader = rsrc->CreateGenericShader();
            
            fix_square->SetShader(shader);
            fix_square->SetUnits(util::units::MIXED);
            fix_square->SetScale(fix_size);
            fix_square->SetPosition(Positions2D::CENTER);
            
            gl.ids.fixation_square = fix_square->GetUUID();
            gl.ids.shader = shader->GetUUID();
            
            auto &target_set = state->GetTargetSet();
            auto fix_targ = target_set.Create(gl.mouse, Time::duration_ms(200));
            fix_targ_id = fix_targ->GetId();
            
            auto rect = gl.pipeline->GetTarget()->GetFullRect();
            fix_targ->SetPosition(fix_square->get_units_position(rect));
            
            fix_targ->SetSize(fix_size);
            target_set.OnTargetEntry(on_target_entry);
            target_set.OnTargetExit(on_target_exit);
        };
    }

	//
	//	choice
	//
    
    namespace choice {
        
        auto render_function = [] (auto looper) {
            looper->ClearQueue();
            auto &gl = globals::gl::get();
            auto rsrc = gl.pipeline->GetResource();
            auto stim = rsrc->Get<Model>(gl.ids.triangle);
            looper->Queue(stim);
        };
        
        auto on_entry = [] (auto state) {
            auto &gl = globals::gl::get();
            gl.pipeline->GetRenderLoop()->OnceDrawReady(render_function);
        };
        
        auto on_exit = [] (auto state) {
            auto &task = globals::task::get();
            state->Next(task.ids.fixation);
        };
        
        auto setup = [] (auto state) {
            state->OnEntry(on_entry);
            state->OnExit(on_exit);
            state->SetTimeIn(EXP::Time::duration_ms(1000));
            state->ExitOnTimeExceeded();
            
            auto &gl = globals::gl::get();
            auto rsrc = gl.pipeline->GetResource();
            auto triangle = rsrc->CreateTriangle();
            auto fix_square = rsrc->Get<Model>(gl.ids.fixation_square);
            auto mat = triangle->GetMaterial();
            triangle->MakeLike(fix_square);
            mat->SetAlbedo(Colors::GREEN);
            triangle->SetMaterial(mat);
            
            gl.ids.triangle = triangle->GetUUID();
        };
    }
    
    //
    //  mistake
    //
    
    namespace mistake {
        
        auto render_function = [] (auto looper) {
            looper->ClearQueue();
            auto &gl = globals::gl::get();
            auto rsrc = gl.pipeline->GetResource();
            auto stim = rsrc->Get<Model>(gl.ids.error_square);
            looper->Queue(stim);
        };
        
        auto on_entry = [] (auto state) {
            auto &gl = globals::gl::get();
            gl.pipeline->GetRenderLoop()->OnceDrawReady(render_function);
        };
        
        auto on_exit = [] (auto state) {
            auto &task = globals::task::get();
            state->Next(task.ids.fixation);
        };
        
        auto setup = [] (auto state) {
            state->OnEntry(on_entry);
            state->OnExit(on_exit);
            state->SetTimeIn(Time::duration_ms(1000));
            state->ExitOnTimeExceeded();
            
            auto &gl = globals::gl::get();
            auto rsrc = gl.pipeline->GetResource();
            auto error_square = rsrc->CreateRectangle();
            auto mat = error_square->GetMaterial();
            auto tex = rsrc->GetTexture(file::get_full_path("../") + "/res/textures/tex1.png");
            auto fix_square = rsrc->Get<Model>(gl.ids.fixation_square);
            
            mat->SetAlbedo(tex);
            error_square->MakeLike(fix_square);
            error_square->SetMaterial(mat);
            error_square->SetScale(glm::vec2(50.0f));
            
            gl.ids.error_square = error_square->GetUUID();
        };
    }
}
}

#endif /* choice_h */
