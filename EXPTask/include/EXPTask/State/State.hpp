//
//  State.hpp
//  EXPTask
//
//  Created by Nick Fagan on 10/28/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include <EXPTask/State/StatePrimitive.hpp>
#include <EXPTask/Time/Timer.hpp>
#include <EXPTask/State/exit_conditions.hpp>
#include <EXPTask/State/TargetSet.hpp>
#include <memory>

namespace EXP {
    
    class Task;
    
    class State : public StatePrimitive
    {
        friend class Task;
        
    public:
        State(std::shared_ptr<Time::Keeper> time_keeper);
        virtual ~State() = default;
        
        TargetSet& GetTargetSet();
        unsigned GetUUID() const;
        State* GetStateById(unsigned id) const;
        
        void Next(State* state);
        
        void OnEntry(std::function<void(State*)> on_entry);
        void OnLoop(std::function<void(State*)> on_loop);
        void OnExit(std::function<void(State*)> on_exit);
        
    protected:
        unsigned id;
        Task *parent = nullptr;
        TargetSet target_set;
        
        std::vector<EXP::exit_conditions::general*> constant_exit_conditions;
        std::vector<EXP::exit_conditions::general*> transient_exit_conditions;
        
        std::function<void(State*)> on_entry = &EXP::State::empty;
        std::function<void(State*)> on_loop = &EXP::State::empty;
        std::function<void(State*)> on_exit = &EXP::State::empty;
        
        virtual void set_id(unsigned id);
        virtual void set_parent(EXP::Task *parent);
        
        virtual void run();
        virtual void empty();
        virtual void entry();
        virtual void loop();
        virtual void exit();
    };
}

#endif /* State_hpp */
