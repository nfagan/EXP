//
//  Task.hpp
//  EXP
//
//  Created by Nick Fagan on 10/29/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Task_hpp
#define Task_hpp

#include <stdio.h>
#include <EXPTask/State/State.hpp>
#include <unordered_map>
#include <atomic>
#include <memory>

namespace EXP {
    class Task : public StatePrimitive
    {
    
    public:
        Task(std::shared_ptr<EXP::Time::Keeper> keeper);
        virtual ~Task();
        
        void Run(void);
        void OnLoop(std::function<void(Task*)> on_loop);
        void OnExit(std::function<void(Task*)> on_exit);
        void OnError(std::function<void(Task*, const std::runtime_error&)> on_error);
        
        bool IsRunning();
        void LogTime(void) const;
        
        EXP::State* CreateState(unsigned *id);
        EXP::State* GetStateById(unsigned id);
        
    protected:
        std::atomic<bool> is_running;
        EXP::StatePrimitive *previous = nullptr;
        std::unordered_map<unsigned, EXP::State*> states;
        unsigned n_states;
        
        std::function<void(Task*)> on_loop = &EXP::Task::empty;
        std::function<void(Task*)> on_exit = &EXP::Task::empty;
        std::function<void(Task*, const std::runtime_error&)> on_error;
        
        void empty();
        void loop();
        void exit();
        void error(const std::runtime_error &err);
    };
}

#endif /* Task_hpp */
