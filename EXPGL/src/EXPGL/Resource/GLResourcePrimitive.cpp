//
//  GLResourcePrimitive.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/5/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Resource/GLResourcePrimitive.hpp>
#include <iostream>

EXP::GLResourcePrimitive::GLResourcePrimitive() {
    identifier = EXP::GLResourceIdentifier();
};

void EXP::GLResourcePrimitive::Initialize(EXP::RenderTarget *target) {};

EXP::GLResourceIdentifier EXP::GLResourcePrimitive::GetIdentifier() const
{
    return identifier;
}

void EXP::GLResourcePrimitive::SetTag(const std::string &tag)
{
    identifier.SetTag(tag);
}

void EXP::GLResourcePrimitive::set_identifier(const EXP::GLResourceIdentifier &identifier)
{
    this->identifier = identifier;
}
