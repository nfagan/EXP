//
//  Texture.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Texture/Texture.hpp>

EXP::Texture::Texture(unsigned id) : EXP::GLResourcePrimitive()
{
    this->id = id;
    this->index = 0;
    this->width = 0;
    this->height = 0;
}

EXP::Texture::Texture(unsigned id, int width, int height) : EXP::GLResourcePrimitive()
{
    this->id = id;
    this->index = 0;
    this->width = width;
    this->height = height;
}

EXP::Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void EXP::Texture::SetIndex(unsigned int index)
{
    this->index = index;
}

void EXP::Texture::Activate()
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
}

int EXP::Texture::GetWidth() const
{
    return width;
}

int EXP::Texture::GetHeight() const
{
    return height;
}

int EXP::Texture::GetIndex() const
{
    return index;
}
