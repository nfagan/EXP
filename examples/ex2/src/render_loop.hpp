//
//  render_loop.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef render_loop_h
#define render_loop_h

#include "ex2.hpp"

namespace ex2 {
    namespace render_loop {
        
        using namespace EXP;
        
        auto main = [] (auto loop) {
            auto &gl = globals::gl::get();
            gl.pipeline->Update();
            gl.mouse->Update(gl.pipeline->GetTarget());
            gl.keyboard->Update(gl.pipeline->GetTarget());
            
//            auto fix_square = gl.pipeline->GetResource()->Get<Model>(gl.ids.fixation_square);
            auto rsrc = gl.pipeline->GetResource();
            auto fix_square = rsrc->Get<Model>(gl.ids.fixation_square);
            auto pos = fix_square->GetPosition();
            float step_amount = 0.005f;
            
            if (gl.keyboard->KeyDown(Keys::A)) pos.x -= step_amount;
            if (gl.keyboard->KeyDown(Keys::S)) pos.y += step_amount;
            if (gl.keyboard->KeyDown(Keys::D)) pos.x += step_amount;
            if (gl.keyboard->KeyDown(Keys::W)) pos.y -= step_amount;
            if (gl.keyboard->KeyDown(Keys::C))
            {
                pos.x = 0.5f;
                pos.y = 0.5f;
            }
            
            if (gl.keyboard->KeyDown(Keys::ESC))
            {
//                loop->CancelLoop();
                return;
            }
            
            fix_square->SetPosition(pos);
        };
    }
}

#endif /* render_loop_h */
