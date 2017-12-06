//
//  TargetSet.hpp
//  EXP
//
//  Created by Nick Fagan on 11/13/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef TargetSet_hpp
#define TargetSet_hpp

#include <EXPGL/Input/InputXY.hpp>
#include <EXPTask/Tracking/Target.hpp>
#include <EXPTask/Time/Timings.hpp>
#include <EXPTask/Time/Timer.hpp>
#include <EXPTask/Time/Keeper.hpp>
#include <functional>
#include <atomic>
#include <memory>
#include <unordered_map>

namespace EXP {
    
    class State;
    
    class TargetSet
    {
        friend class State;
    private:
        struct timed_target {
            std::shared_ptr<Target> target;
            Time::Timer timer;
            bool was_in_bounds;
            bool called_ellapsed;
            
            timed_target(std::shared_ptr<Target> in_target, std::shared_ptr<Time::Keeper> keeper, Time::duration_s duration);
            timed_target() = default;
            ~timed_target() = default;
            void reset();
        };
        
        TargetSet() = default;
        ~TargetSet() = default;
        
        void initialize(State *parent, std::shared_ptr<Time::Keeper> keeper);
        void update();
        void update_one(timed_target &targ);
        void reset();
        static void empty(State*, const std::shared_ptr<Target>) {};
        
        std::atomic<State*> parent;
        std::shared_ptr<Time::Keeper> keeper;
        unsigned int n_targets;
        std::unordered_map<unsigned int, timed_target> targets;
        
        std::function<void(State*, std::shared_ptr<Target>)> on_target_exit = &TargetSet::empty;
        std::function<void(State*, std::shared_ptr<Target>)> on_target_entry = &TargetSet::empty;
        std::function<void(State*, std::shared_ptr<Target>)> on_ellapsed = &TargetSet::empty;
        
    public:
        std::shared_ptr<Target> Create(std::shared_ptr<InputXY> inupt_source, Time::duration_s threshold);
        void OnTargetExit(std::function<void(State*, std::shared_ptr<Target>)> on_target_exit);
        void OnTargetEntry(std::function<void(State*, std::shared_ptr<Target>)> on_target_entry);
        void OnEllapsed(std::function<void(State*, std::shared_ptr<Target>)> on_ellapsed);
        std::shared_ptr<Target> GetTargetById(unsigned id);
    };
}

#endif /* TargetSet_hpp */
