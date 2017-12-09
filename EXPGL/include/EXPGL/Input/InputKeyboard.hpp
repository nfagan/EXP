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
#include <memory>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <EXPUtil/thread/spinlock.hpp>

namespace EXP {
    
    class InputKeyboard
    {
    public:
        InputKeyboard() = default;
        ~InputKeyboard() = default;
        
        void Register(int key);
        void Update(std::shared_ptr<EXP::RenderTarget> target);
        bool KeyDown(int id);
    private:
        spinlock key_lock;
        std::vector<int> keys;
        std::unordered_map<int, std::atomic<bool>> press_status;
        
        bool contains(int key) const;
    };
}

#endif /* InputKeyboard_hpp */
