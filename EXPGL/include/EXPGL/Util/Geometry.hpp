//
//  Geometry.hpp
//  EXPGL
//
//  Created by Nick Fagan on 12/2/17.
//

#ifndef Geometry_h
#define Geometry_h

#include <EXPGL/Model/Model.hpp>
#include <EXPGL/Render/RenderTarget.hpp>

namespace EXP {
    namespace util {
        namespace geometry {
            static const Rect<float> get_bounding_rect_pixels(const std::shared_ptr<RenderTarget> &target, const Model* model)
            {
                Rect<float> screen = target->GetFullRect();
                glm::vec3 pos = model->get_units_position(screen);
                glm::vec3 scl = model->get_units_scale(screen);
                
                float left = pos.x - scl.x;
                float right = pos.x + scl.x;
                float top = pos.y - scl.y;
                float bottom = pos.y + scl.y;
                
                return Rect<float>(left, top, right, bottom);
            }
        }
    }
}


#endif /* Geometry_h */
