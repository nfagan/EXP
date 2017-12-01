//
//  TextureLoader.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <EXPGL/Texture/Texture.hpp>

namespace EXP {
    class TextureLoader
    {
    public:
        TextureLoader();
        ~TextureLoader();
        
        Texture* GetTexture(const char* filename);
    private:
        std::unordered_map<const char*, Texture*> textures;
    };
}

#endif /* TextureLoader_hpp */
