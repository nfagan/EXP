//
//  render_loop.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/5/17.
//

#ifndef render_loop_h
#define render_loop_h

#include "EXP.hpp"
#include "globals.hpp"

namespace ex2 {
namespace render_loop {
    
    using namespace EXP;
    
    void main(RenderLoop *loop)
    {
        gl::pipeline->Update();
        gl::mouse->UpdateCoordinates(gl::pipeline->GetTarget());
    }
}
}

#endif /* render_loop_h */
