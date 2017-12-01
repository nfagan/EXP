//
//  ResourceIdentifier.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/5/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Resource/GLResourceIdentifier.hpp>

EXP::GLResourceIdentifier::GLResourceIdentifier() {
    SetId(0);
    SetName("");
    SetTag("");
};

void EXP::GLResourceIdentifier::SetId(unsigned id)
{
    this->id = id;
}

void EXP::GLResourceIdentifier::SetName(std::string name)
{
    this->name = name;
}

void EXP::GLResourceIdentifier::SetTag(std::string tag)
{
    this->tag = tag;
}

const std::string& EXP::GLResourceIdentifier::GetName() const
{
    return name;
}

const std::string& EXP::GLResourceIdentifier::GetTag() const
{
    return tag;
}

unsigned EXP::GLResourceIdentifier::GetId() const
{
    return id;
}

void EXP::GLResourceIdentifier::clone_from(const EXP::GLResourceIdentifier &source)
{
    SetName(source.GetName());
    SetTag(source.GetTag());
    SetId(source.GetId());
}
