//
//  InputXY.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/24/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Input/InputXY.hpp>

EXP::InputXY::InputXY(EXP::RenderTarget *target)
{
    this->target = target;
    x.store(0.0f);
    y.store(0.0f);
}

glm::vec2 EXP::InputXY::GetCoordinates() const
{
    return glm::vec2(x.load(), y.load());
}

void EXP::InputXY::UpdateCoordinates()
{
    double x_, y_;
    glfwGetCursorPos(target->GetPrimaryWindow()->GetWindow(), &x_, &y_);
    x.store((float)x_);
    y.store((float)y_);
}

void EXP::InputXY::PrintCoordinates() const
{
    fprintf(stderr, "\nInputXY: X: %0.3f, Y: %0.3f", x.load(), y.load());
}


