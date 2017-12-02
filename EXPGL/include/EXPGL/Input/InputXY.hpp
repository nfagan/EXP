//
//  InputXY.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/24/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef InputXY_hpp
#define InputXY_hpp

#include <EXPGL/Render/RenderTarget.hpp>
#include <glm/glm.hpp>
#include <atomic>
#include <memory>

namespace EXP {
    class InputXY
    {
    public:
        InputXY(std::shared_ptr<EXP::RenderTarget> target);
        virtual ~InputXY() = default;
        
        virtual glm::vec2 GetCoordinates() const;
        virtual void UpdateCoordinates();
        virtual void PrintCoordinates() const;
    protected:
        std::shared_ptr<EXP::RenderTarget> target;
        std::atomic<float> x;
        std::atomic<float> y;
    };
}

#endif /* InputXY_hpp */
