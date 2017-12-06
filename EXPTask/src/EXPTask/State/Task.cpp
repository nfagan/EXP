//
//  Task.cpp
//  EXP
//
//  Created by Nick Fagan on 10/29/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPTask/State/Task.hpp>
#include <iostream>

EXP::Task::Task(std::shared_ptr<EXP::Time::Keeper> time_keeper) : EXP::StatePrimitive(time_keeper)
{
    n_states = 0;
    is_running.store(false);
    AddExitCondition<EXP::exit_conditions::null_next>();
}

EXP::Task::~Task()
{
    for (auto it = states.begin(); it != states.end(); ++it)
    {
        delete it->second;
    }
}

bool EXP::Task::IsRunning()
{
    return is_running.load();
}

void EXP::Task::OnLoop(std::function<void (Task *)> on_loop)
{
    this->on_loop = on_loop;
}

void EXP::Task::OnError(std::function<void (Task *, const std::runtime_error &err)> on_error)
{
    this->on_error = on_error;
}

void EXP::Task::OnExit(std::function<void (Task *)> on_exit)
{
    this->on_exit = on_exit;
}

void EXP::Task::Run()
{
    bool first_entry = true;
    EXP::StatePrimitive *current = next;
	GetTimer()->Reset();
    is_running.store(true);
    try {
        while (!should_exit())
        {
            loop();

            if (first_entry)
            {
                current->entry();
                first_entry = false;
            }

            if (current->should_exit())
            {
                current->exit();
                previous = current;
                next = current->GetNext();
                current = next;
                first_entry = true;
            }
            else
            {
                current->loop();
            }
        }
        exit();
        is_running.store(false);
    } catch (const std::runtime_error &err) {
        on_error(this, err);
    }
}

void EXP::Task::LogTime() const
{
    std::string display_name = get_display_name();
    std::cout << "\nTiming info for task: " << display_name;
    std::cout << "\n\tEllapsed time: " << EllapsedTime().count() << " (s)" << std::endl;
}

void EXP::Task::exit()
{
    on_exit(this);
}

void EXP::Task::loop()
{
    on_loop(this);
}

void EXP::Task::empty()
{
    //
}

void EXP::Task::error(const std::runtime_error &err)
{
    throw err;
}

EXP::State* EXP::Task::CreateState(unsigned int *id)
{
    EXP::State *state = new EXP::State(time_keeper);
    state->set_id(n_states);
    state->set_parent(this);
    states[n_states] = state;
    *id = n_states;
    n_states++;
    return state;
}

EXP::State* EXP::Task::GetStateById(unsigned id)
{
    auto it = states.find(id);
    if (it == states.end())
    {
        std::cout << "Requested non-existent state `" << id << "`." << std::endl;
        return nullptr;
    }
    return it->second;
}
