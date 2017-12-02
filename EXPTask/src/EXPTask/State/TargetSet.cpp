//
//  TargetSet.cpp
//  EXP
//
//  Created by Nick Fagan on 11/13/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPTask/State/TargetSet.hpp>
#include <iostream>

EXP::TargetSet::timed_target::timed_target(std::shared_ptr<EXP::Target> in_target,
                                           EXP::Time::Keeper *keeper, EXP::Time::duration_s duration)
{
    target = in_target;
    timer.Initialize(keeper, duration);
    reset();
}

void EXP::TargetSet::timed_target::reset()
{
    called_ellapsed = false;
    was_in_bounds = false;
    timer.Reset();
}

void EXP::TargetSet::initialize(EXP::State *parent, Time::Keeper *keeper)
{
    n_targets = 0;
    this->parent.store(parent);
    this->keeper.store(keeper);
}

std::shared_ptr<EXP::Target> EXP::TargetSet::Create(const std::shared_ptr<EXP::InputXY> input_source,
                                                    Time::duration_s threshold)
{
    std::shared_ptr<EXP::Target> target = std::make_shared<EXP::Target>(input_source);
    timed_target target_(target, keeper.load(), threshold);
    targets[n_targets] = target_;
    n_targets++;
    return target;
}

std::shared_ptr<EXP::Target> EXP::TargetSet::GetTargetById(unsigned id)
{
    auto it = targets.find(id);
    if (it == targets.end())
    {
        throw std::runtime_error("Requested non-existent target `" + std::to_string(id) + "`.");
    }
    return it->second.target;
}

void EXP::TargetSet::OnTargetEntry(std::function<void(State*, std::shared_ptr<Target>)> on_target_entry)
{
    this->on_target_entry = on_target_entry;
}

void EXP::TargetSet::OnTargetExit(std::function<void(State*, std::shared_ptr<Target>)> on_target_exit)
{
    this->on_target_exit = on_target_exit;
}

void EXP::TargetSet::OnEllapsed(std::function<void(State*, std::shared_ptr<Target>)> on_ellapsed)
{
    this->on_ellapsed = on_ellapsed;
}

void EXP::TargetSet::reset()
{
    for (auto it = targets.begin(); it != targets.end(); it++)
    {
        it->second.reset();
    }
}

void EXP::TargetSet::update()
{
    for (auto it = targets.begin(); it != targets.end(); it++)
    {
        update_one(it->second);
    }
}

void EXP::TargetSet::update_one(EXP::TargetSet::timed_target &target)
{
    if (target.target->InBounds())
    {
        if (!target.was_in_bounds)
        {
            on_target_entry(parent, target.target);
            target.was_in_bounds = true;
        }
    }
    else
    {
        target.timer.Reset();
        if (target.was_in_bounds)
        {
            on_target_exit(parent, target.target);
            target.was_in_bounds = false;
        }
    }
    
    if (target.timer.Ellapsed() && !target.called_ellapsed)
    {
        on_ellapsed(parent, target.target);
        target.called_ellapsed = true;
    }
}
