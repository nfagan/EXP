//
//  Target.cpp
//  EXPTask
//
//  Created by Nick Fagan on 12/2/17.
//

#include <EXPTask/Tracking/Target.hpp>

EXP::Target::Target(std::shared_ptr<EXP::InputXY> input_source) : input_source(input_source)
{
     bounds_function = &Target::bounds_function_circle;
}

unsigned int EXP::Target::GetId()
{
    return id.load();
}

void EXP::Target::SetSize(float size)
{
    this->size.store(size);
}

void EXP::Target::SetPosition(glm::vec2 position)
{
    position_lock.lock();
    this->position = position;
    position_lock.unlock();
}

void EXP::Target::OnBoundsCheck(std::function<bool(Target*)> bounds_function)
{
    bounds_function_lock.lock();
    this->bounds_function = bounds_function;
    bounds_function_lock.unlock();
}

bool EXP::Target::InBounds()
{
    bounds_function_lock.lock();
    bool in_bounds = bounds_function(this);
    bounds_function_lock.unlock();
    return in_bounds;
}

glm::vec2 EXP::Target::get_position()
{
    position_lock.lock();
    glm::vec2 copy = position;
    position_lock.unlock();
    return copy;
}

bool EXP::Target::bounds_function_circle()
{
    glm::vec2 coordinates = input_source->GetCoordinates();
    glm::vec2 pos = get_position();
    float distance = glm::distance(coordinates, pos);
    return glm::abs(distance) <= size;
}

void EXP::Target::set_id(unsigned int id)
{
    this->id.store(id);
}
