//
//  Keeperr.hpp
//  EXP
//
//  Created by Nick Fagan on 10/29/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Keeperr_hpp
#define Keeperr_hpp

#include <stdio.h>
#include <EXPTask/Time/Keeper.hpp>
#include <memory>

namespace EXP {
    namespace Time {
        class Timer
        {
        public:
            Timer() = default;
            Timer(std::shared_ptr<EXP::Time::Keeper> time);
            Timer(std::shared_ptr<EXP::Time::Keeper> time, EXP::Time::duration_ms duration);
            ~Timer() = default;
            
            void Initialize(std::shared_ptr<EXP::Time::Keeper> time, EXP::Time::duration_ms duration);
            void SetDuration(EXP::Time::duration_ms duration);
            void Reset();
            bool Ellapsed() const;
            double EllapsedTime() const;
        private:
            void init_time();
            bool did_initialize = false;
            double start;
            std::shared_ptr<EXP::Time::Keeper> time;
            EXP::Time::duration_ms duration;
        };
    }
}

#endif /* Keeperr_hpp */
