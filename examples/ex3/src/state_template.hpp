//
//  state_template.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/9/17.
//

#ifndef state_template_h
#define state_template_h

#include "globals.hpp"

namespace ex3 {
    namespace states {
        
        using std::shared_ptr;
        
        struct state_template
        {
            State *state;
            shared_ptr<globals::task> task;
            shared_ptr<globals::gl> gl;
//            shared_ptr<globals::db> db;
            
            state_template() = default;
            state_template(State *state, shared_ptr<globals::task> task,
                           shared_ptr<globals::gl> gl)
            {
                this->state = state;
                this->task = task;
                this->gl = gl;
//                this->db = db;
            }
        };
    }
}

#endif /* state_template_h */
