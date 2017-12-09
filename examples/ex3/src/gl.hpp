//
//  gl.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/9/17.
//

#ifndef ex2_gl_h
#define ex2_gl_h

#include "ex3.hpp"

namespace ex3 {
    namespace globals {
        
        using namespace EXP;
        using std::shared_ptr;
        using std::make_shared;
        
        struct gl
        {
            shared_ptr<GLContextManager> context;
            shared_ptr<GLPipeline> pipeline;
            
            shared_ptr<InputXY> mouse;
            shared_ptr<InputKeyboard> keyboard;
            
            struct ids_ {
                unsigned shader = 0;
                unsigned fixation_square = 0;
                unsigned triangle = 0;
                unsigned error_square = 0;
            } ids;
            
            gl()
            {
                context = make_shared<GLContextManager>();
                pipeline = make_shared<GLPipeline>(context);
                
                mouse = make_shared<InputXY>();
                keyboard = make_shared<InputKeyboard>();
            }
        };
        
    }
}

#endif /* gl_h */
