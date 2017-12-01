//
//  MaterialAttribute.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/12/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef MaterialAttribute_hpp
#define MaterialAttribute_hpp

#include <EXPGL/Resource/GLResourcePrimitive.hpp>
#include <EXPGL/Texture/Texture.hpp>
#include <EXPGL/Render/Shader.hpp>
#include <EXPUtil/thread/spinlock.hpp>
#include <glm/glm.hpp>

namespace EXP {
    class MaterialAttribute : public GLResourcePrimitive
    {
        friend class Material;
    public:
        MaterialAttribute();
        MaterialAttribute(glm::vec3 data);
        MaterialAttribute(const Texture *data);
        MaterialAttribute(float data);
        MaterialAttribute(const MaterialAttribute &data);
        
        ~MaterialAttribute() = default;
        
        MaterialAttribute& operator=(const MaterialAttribute& other);
        
        void Set(glm::vec3 data);
        void Set(const Texture *data);
        void Set(float data);
        
        void Configure(Shader *shader);
    protected:
        std::string name;
        spinlock name_lock;
        struct Attribute {
            enum { VEC3, TEXTURE, FLOAT } tag = VEC3;
            union Data {
                glm::vec3 vec3_value;
                const Texture *tex_value;
                float float_value;
                Data() { vec3_value = glm::vec3(1.0f); }
            } data;
        } attribute;
        spinlock data_lock;
        
        void set_name(std::string name);
        void copy_from(const MaterialAttribute &other);
    };
}

#endif /* MaterialAttribute_hpp */
