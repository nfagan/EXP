//
//  Material.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/26/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <vector>
#include <atomic>
#include <EXPGL/Render/Shader.hpp>
#include <EXPGL/Resource/GLResourcePrimitive.hpp>
#include <EXPGL/Material/MaterialAttribute.hpp>
#include <EXPUtil/thread/proplock.hpp>

namespace EXP {
    
    class Material : public GLResourcePrimitive
    {        
    public:
        Material();
        virtual ~Material() = default;
        virtual void Configure(EXP::Shader *shader);
        
        virtual void SetAlbedo(MaterialAttribute albedo);
        virtual const MaterialAttribute& GetAlbedo(void) const;
    protected:
        proplock<MaterialAttribute> albedo;
    };
}

#endif /* Material_hpp */
