//
//  GLResourcePrimitive.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/5/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef GLResourcePrimitive_hpp
#define GLResourcePrimitive_hpp

#include <stdio.h>
#include <EXPGL/Resource/GLResourceIdentifier.hpp>

namespace EXP {
    
    class RenderTarget;
    
    class GLResourcePrimitive
    {
        friend class GLResourceManager;
    public:
        GLResourcePrimitive();
        virtual ~GLResourcePrimitive() = default;
        virtual GLResourceIdentifier GetIdentifier() const;
        virtual void Initialize(RenderTarget *target);
        virtual void SetTag(const std::string &tag);
        
    protected:
        virtual void set_identifier(const GLResourceIdentifier &identifier);
        GLResourceIdentifier identifier;
    };
}

#endif /* GLResourcePrimitive_hpp */
