//
//  choice.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef choice_h
#define choice_h

#include "ex3.hpp"
#include "state_template.hpp"

namespace ex3 {
    
using std::shared_ptr;
using namespace EXP;

namespace states {

	//
	//	fixation
	//
    
    struct fixation : public state_template
    {
        
        Time::duration_ms initial_fix_time = Time::duration_ms(5);
        looper_cb render_function;
        
        template<typename ...T>
        fixation(T... args) : state_template(args...) {};
        
        target_cb on_target_entry;
        
        void setup()
        {
            float fix_size = 10.0f;
            auto rsrc = gl->pipeline->GetResource();
            auto fix_square = rsrc->CreateRectangle();
            auto shader = rsrc->CreateGenericShader();
            
            fix_square->SetShader(shader);
            fix_square->SetUnits(util::units::MIXED);
            fix_square->SetScale(fix_size);
            fix_square->SetPosition(Positions2D::CENTER);
            
            gl->ids.fixation_square = fix_square->GetUUID();
            gl->ids.shader = shader->GetUUID();
            
            auto &target_set = state->GetTargetSet();
            auto fix_targ = target_set.Create(gl->mouse, Time::duration_ms(200));
            
            auto rect = gl->pipeline->GetTarget()->GetFullRect();
            fix_targ->SetPosition(fix_square->get_units_position(rect));
            
            fix_targ->SetSize(fix_size);
            
            render_function = [this] (auto looper) {
                looper->ClearQueue();
                auto rsrc = gl->pipeline->GetResource();
                auto rect = rsrc->Get<Model>(gl->ids.fixation_square);
                looper->Queue(rect);
            };
            
            on_entry = [this] (auto s) {
                state->LogTime();
                gl->pipeline->GetRenderLoop()->OnceDrawReady(render_function);
                //  by default, go to mistake state.
                state->Next(task->ids.fixation);
            };
            
            on_target_entry = [this] (auto state, auto target) {
                if (state->EllapsedTime() > initial_fix_time)
                {
                    state->Next(task->ids.fixation);
                    state->ExitNow();
                    return;
                }
                state->Next(task->ids.fixation);
            };
            
            target_set.OnTargetEntry(on_target_entry);
            
            state->SetTimeIn(Time::duration_ms(2000));
            state->ExitOnTimeExceeded();
            state->OnEntry(on_entry);
            
        }
    };
}
}

#endif /* choice_h */
