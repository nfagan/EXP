//
//  InputKeyboard.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/26/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Input/InputKeyboard.hpp>

void EXP::InputKeyboard::Update(std::shared_ptr<EXP::RenderTarget> target)
{
    key_lock.lock();
    auto window = target->GetPrimaryWindow()->GetWindow();
    for (const auto &key : keys)
    {
        press_status[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }
    key_lock.unlock();
}

bool EXP::InputKeyboard::contains(int key) const
{
    return press_status.find(key) != press_status.end();
}

void EXP::InputKeyboard::Register(int key)
{
    key_lock.lock();
    if (contains(key))
    {
        key_lock.unlock();
        return;
    }
    keys.push_back(key);
    press_status[key] = false;
    key_lock.unlock();
}

bool EXP::InputKeyboard::KeyDown(int key)
{
    if (!contains(key))
        Register(key);
    return press_status[key];
}
