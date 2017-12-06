//
//  InputXY.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/24/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef InputXY_hpp
#define InputXY_hpp

//#define EXPGL_TARGET_INPUT

#include <EXPGL/Render/RenderTarget.hpp>
#include <glm/glm.hpp>
#include <atomic>
#include <memory>

namespace EXP {
    class InputXY
    {
    public:
#ifdef EXPGL_TARGET_INPUT
        InputXY(std::shared_ptr<EXP::RenderTarget> target);
#else
        InputXY();
#endif
        virtual ~InputXY() = default;
        
        virtual glm::vec2 GetCoordinates() const;
#ifdef EXPGL_TARGET_INPUT
        virtual void UpdateCoordinates();
#else
        virtual void UpdateCoordinates(const std::shared_ptr<EXP::RenderTarget> target);
#endif
    protected:
#ifdef EXPGL_TARGET_INPUT
        std::shared_ptr<EXP::RenderTarget> target;
#endif
        std::atomic<float> x;
        std::atomic<float> y;
    };
}

#endif /* InputXY_hpp */
