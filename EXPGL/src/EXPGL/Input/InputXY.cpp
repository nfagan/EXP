//
//  InputXY.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/24/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Input/InputXY.hpp>
#include <GLFW/glfw3.h>

#ifdef EXPGL_TARGET_INPUT
EXP::InputXY::InputXY(std::shared_ptr<EXP::RenderTarget> target) : target(target)
{
    x.store(0.0f);
    y.store(0.0f);
}
#else
EXP::InputXY::InputXY()
{
    x.store(0.0f);
    y.store(0.0f);
}
#endif

glm::vec2 EXP::InputXY::GetCoordinates() const
{
    return glm::vec2(x.load(), y.load());
}

#ifdef EXPGL_TARGET_INPUT
void EXP::InputXY::UpdateCoordinates()
{
    double x_, y_;
    glfwGetCursorPos(target->GetPrimaryWindow()->GetWindow(), &x_, &y_);
    x.store((float)x_);
    y.store((float)y_);
}
#else
void EXP::InputXY::UpdateCoordinates(const std::shared_ptr<EXP::RenderTarget> target)
{
    double x_, y_;
    glfwGetCursorPos(target->GetPrimaryWindow()->GetWindow(), &x_, &y_);
    x.store((float)x_);
    y.store((float)y_);
}
#endif


