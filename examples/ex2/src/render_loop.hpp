//
//  render_loop.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef render_loop_h
#define render_loop_h

#include "ex2.hpp"

namespace ex3 {
namespace render_loop {
    
    using namespace EXP;
    
    auto main = [] (auto loop) {
        auto &gl = globals::gl::get();
        gl.pipeline->Update();
        gl.mouse->Update(gl.pipeline->GetTarget());
        gl.keyboard->Update(gl.pipeline->GetTarget());
    };
    
}
}

#endif /* render_loop_h */
