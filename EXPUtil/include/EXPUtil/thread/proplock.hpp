//
//  proplock.hpp
//  EXPUtil
//
//  Created by Nick Fagan on 11/13/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef proplock_h
#define proplock_h

#include "spinlock.hpp"

namespace EXP {
    template<typename T>
    class proplock
    {
    public:
        proplock() = default;
        ~proplock() = default;
        
        const T& Get(void) const
        {
            return resource;
        }
        
        void Set(T resource)
        {
            resource_lock.lock();
            this->resource = resource;
            resource_lock.unlock();
        }
    private:
        spinlock resource_lock;
        T resource;
    };
}


#endif /* proplock_h */
