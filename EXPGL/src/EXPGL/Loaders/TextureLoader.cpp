//
//  TextureLoader.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Loaders/TextureLoader.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <gl.h>
#include <iostream>

EXP::TextureLoader::TextureLoader() {}

EXP::TextureLoader::~TextureLoader() {
    for (auto it = textures.begin(); it != textures.end(); ++it)
    {
        delete it->second;
    }
}

EXP::Texture* EXP::TextureLoader::GetTexture(const char *filename)
{
    if (textures.find(filename) != textures.end())
    {
        return textures[filename];
    }
    
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    
    int width, height, n_components;
    unsigned char *data = stbi_load(filename, &width, &height, &n_components, 0);
    
    if (data) {
        GLenum format;
        if (n_components == 1)
        {
            format = GL_RED;
        }
        else if (n_components == 3)
        {
            format = GL_RGB;
        }
        else if (n_components == 4)
        {
            format = GL_RGBA;
        }
        else
        {
            assert(false);
        }
        
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    } else {
        std::cout << "Failed to load texture: " << filename << std::endl;
        stbi_image_free(data);
        return NULL;
    }
    
    EXP::Texture *texture = new EXP::Texture(texture_id, width, height);
    textures[filename] = texture;
    
    return texture;
}
