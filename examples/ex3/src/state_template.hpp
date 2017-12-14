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
        using std::function;
        
        struct state_template
        {
            typedef function<void(RenderLoop *looper)> looper_cb;
            typedef function<void(State *state)> state_cb;
            typedef function<void(State *state, shared_ptr<Target> target)> target_cb;
            
            state_cb on_entry;
            state_cb on_exit;
            state_cb on_loop;
            
            State *state;
            
            shared_ptr<globals::task> task;
            shared_ptr<globals::gl> gl;
            shared_ptr<globals::db> db;
            
            state_template() = default;
            state_template(State *state, shared_ptr<globals::task> task,
                           shared_ptr<globals::gl> gl, shared_ptr<globals::db> db)
            {
                this->state = state;
                this->task = task;
                this->gl = gl;
                this->db = db;
            }
        };
    }
}

#endif /* state_template_h */
