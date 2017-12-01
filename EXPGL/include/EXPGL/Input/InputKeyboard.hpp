//
//  InputKeyboard.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/26/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef InputKeyboard_hpp
#define InputKeyboard_hpp

#include <EXPGL/Render/RenderTarget.hpp>

namespace EXP {
    
    class InputKeyboard
    {
    public:
        InputKeyboard(EXP::RenderTarget *target);
        ~InputKeyboard() = default;
        
        void Update();
        bool KeyDown(int id) const;
    private:
        EXP::RenderTarget *target;
    };
}

#endif /* InputKeyboard_hpp */
