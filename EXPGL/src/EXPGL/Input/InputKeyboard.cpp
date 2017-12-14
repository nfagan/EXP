//
//  InputKeyboard.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/26/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Input/InputKeyboard.hpp>
#include <iostream>
#include <assert.h>

void EXP::InputKeyboard::Update(std::shared_ptr<EXP::RenderTarget> target)
{
    key_lock.lock();
    auto window = target->GetPrimaryWindow()->GetWindow();
    for (unsigned i = 0; i < keys.size(); ++i)
    {
        press_status[keys[i]] = glfwGetKey(window, keys[i]) == GLFW_PRESS;
    }
    key_lock.unlock();
}

bool EXP::InputKeyboard::contains(int key)
{
    key_lock.lock();
    for (unsigned i = 0; i < keys.size(); ++i)
    {
        if (keys[i] == key)
        {
            key_lock.unlock();
            return true;
        }
    }
    key_lock.unlock();
    return false;
}

void EXP::InputKeyboard::Register(int key)
{
    if (contains(key))
        return;
    key_lock.lock();
    keys.push_back(key);
    press_status[key] = false;
    key_lock.unlock();
}

bool EXP::InputKeyboard::KeyDown(int key)
{
    Register(key);
    key_lock.lock();
    bool status = press_status[key];
    key_lock.unlock();
    return status;
}
