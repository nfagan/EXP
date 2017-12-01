//
//  spinlock.cpp
//  EXPUtil
//
//  Created by Nick Fagan on 11/6/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPUtil/thread/spinlock.hpp>
#include <iostream>

EXP::spinlock::spinlock()
{
    is_locked.store(false, std::memory_order_seq_cst);
}

EXP::spinlock::~spinlock() {};

void EXP::spinlock::lock()
{
    while (is_locked.load(std::memory_order_seq_cst))
    {
        //
    }
    is_locked.store(true, std::memory_order_seq_cst);
}

void EXP::spinlock::unlock()
{
    is_locked.store(false, std::memory_order_seq_cst);
}
