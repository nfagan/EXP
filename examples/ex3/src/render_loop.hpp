//
//  render_loop.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef render_loop_h
#define render_loop_h

#include "ex3.hpp"

namespace ex3 {
    
    using std::shared_ptr;
    
    struct render_loop
    {
        shared_ptr<globals::gl> gl;
        render_loop(shared_ptr<globals::gl> gl) : gl(gl) {};
        
        void loop()
        {
            auto looper = gl->pipeline->GetRenderLoop();
            looper->OnLoop([this] (auto loop) {
                gl->pipeline->Update();
                gl->mouse->Update(gl->pipeline->GetTarget());
                gl->keyboard->Update(gl->pipeline->GetTarget());
            });
            looper->Loop();
        }
        
    };
}

#endif /* render_loop_h */
