//
//  InputKeyboard.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/26/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Input/InputKeyboard.hpp>

EXP::InputKeyboard::InputKeyboard(std::shared_ptr<EXP::RenderTarget> target) : target(target)
{
    
}

void EXP::InputKeyboard::Update() {};

bool EXP::InputKeyboard::KeyDown(int id) const
{
    return glfwGetKey(target->GetPrimaryWindow()->GetWindow(), id) == GLFW_PRESS;
}
