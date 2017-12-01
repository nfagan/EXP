//
//  commitable.hpp
//  EXPUtil
//
//  Created by Nick Fagan on 11/11/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef commitable_hpp
#define commitable_hpp
#include <EXPUtil/assert/EXP_ASSERT.h>

namespace EXP {
    template<typename T>
    class commitable
    {
    public:
        commitable() : did_commit(false) {};
        ~commitable() = default;
        void commit(T val)
        {
            EXP_ASSERT(!did_commit, "Data were already committed.");
            value = val;
            did_commit = true;
        }
        const T& get_value(void) const
        {
            return value;
        }
    protected:
        T value;
        bool did_commit;
    };
}

#endif /* commitable_hpp */
