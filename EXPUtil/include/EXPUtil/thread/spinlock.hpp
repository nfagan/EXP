//
//  spinlock.hpp
//  EXPUtil
//
//  Created by Nick Fagan on 11/6/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef spinlock_hpp
#define spinlock_hpp

#include <atomic>

namespace EXP {
    class spinlock
    {
    public:
        spinlock();
        ~spinlock();
        
        void lock(void);
        void unlock(void);
    private:
        std::atomic<bool> is_locked;
    };
}

#endif /* spinlock_hpp */
