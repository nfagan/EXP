//
//  Colors.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/24/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Colors_hpp
#define Colors_hpp

#include <glm/glm.hpp>

namespace EXP {
    namespace Colors {
        static const glm::vec3 BLACK(0.0f, 0.0f, 0.0f);
        static const glm::vec3 WHITE(1.0f, 1.0f, 1.0f);
        static const glm::vec3 RED(1.0f, 0.0f, 0.0f);
        static const glm::vec3 GREEN(0.0f, 1.0f, 0.0f);
        static const glm::vec3 BLUE(0.0f, 0.0f, 1.0f);
        static const glm::vec3 YELLOW(1.0f, 1.0f, 0.0f);
        static const glm::vec3 MAGENTA(1.0f, 0.0f, 1.0f);
        static const glm::vec3 CYAN(0.0f, 1.0f, 1.0f);
        static const glm::vec3 GREY_10(0.1f, 0.1f, 0.1f);
        static const glm::vec3 GREY_50(0.5f, 0.5f, 0.5f);
    }
}

#endif /* Colors_hpp */
