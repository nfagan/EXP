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
                
                if (gl->keyboard->KeyDown(Keys::A))
                    std::cout << 'a' << std::endl;
                if (gl->keyboard->KeyDown(Keys::S))
                    std::cout << 's' << std::endl;
                if (gl->keyboard->KeyDown(Keys::D))
                    std::cout << 'd' << std::endl;
                if (gl->keyboard->KeyDown(Keys::W))
                    std::cout << 'w' << std::endl;
                if (gl->keyboard->KeyDown(Keys::C))
                {
                    std::cout << 'c' << std::endl;
                }
            });
            looper->Loop();
        }
        
    };
}

#endif /* render_loop_h */
