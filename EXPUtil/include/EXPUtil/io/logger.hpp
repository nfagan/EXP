//
//  logger.hpp
//  EXPUtil
//
//  Created by Nick Fagan on 12/4/17.
//

#ifndef logger_h
#define logger_h

#include <iostream>
#include <atomic>

namespace EXP {
    
    namespace severity {
        enum severity_ {
            all = 0,
            debug = 1,
            info = 2,
            warn = 3,
            error = 4,
            none = 5
        };
    }
    
    namespace {
        template <int severity>
        struct ostream_impl {
            std::atomic<int> *threshold;
            ostream_impl() = default;
            void set_threshold(std::atomic<int> *thresh)
            {
                threshold = thresh;
            }
            template<typename T>
            void operator <<(const T &arg) const
            {
                if (severity > threshold->load())
                {
                    std::cout << arg;
                }
            }
        };
    }
    class logger
    {
    private:
        std::atomic<int> severity_;
        struct all_impl : public ostream_impl<severity::all> {};
        struct debug_impl : public ostream_impl<severity::debug> {};
        struct info_impl : public ostream_impl<severity::info> {};
        struct warn_impl : public ostream_impl<severity::warn> {};
        struct error_impl : public ostream_impl<severity::error> {};
        
    public:
        logger()
        {
            severity_ = severity::all;
            all.set_threshold(&severity_);
            debug.set_threshold(&severity_);
            info.set_threshold(&severity_);
            warn.set_threshold(&severity_);
            error.set_threshold(&severity_);
        }
        ~logger() = default;
        
        void set_severity(severity::severity_ severity)
        {
            this->severity_ = severity;
        }
        
        all_impl all;
        debug_impl debug;
        info_impl info;
        warn_impl warn;
        error_impl error;
    };
    
}

#endif /* logger_h */
