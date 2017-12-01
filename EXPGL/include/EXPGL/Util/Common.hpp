//
//  Common.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/30/17.
//

#ifndef Common_h
#define Common_h

namespace EXP {
    namespace util {
        namespace units {
            enum UNITS {
                NORMALIZED,
                PIXELS,
                MIXED
            };
        }
        
        namespace projection_types {
            enum PROJECTION_TYPES {
                ORTHOGRAPHIC,
                PERSPECTIVE
            };
        }
    }
}

#endif /* Common_h */
