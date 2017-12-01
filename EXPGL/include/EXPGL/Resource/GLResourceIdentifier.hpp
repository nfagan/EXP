//
//  ResourceIdentifier.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/5/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef ResourceIdentifier_hpp
#define ResourceIdentifier_hpp

#include <stdio.h>
#include <string>

namespace EXP {
    class GLResourceIdentifier
    {
    public:
        GLResourceIdentifier();
        ~GLResourceIdentifier() = default;
        
        void SetName(std::string name);
        void SetTag(std::string tag);
        void SetId(unsigned id);
        
        const std::string& GetName() const;
        const std::string& GetTag() const;
        unsigned GetId() const;
        
        void clone_from(const GLResourceIdentifier& source);
    private:
        unsigned id;
        std::string name;
        std::string tag;
    };
}

#endif /* ResourceIdentifier_hpp */
