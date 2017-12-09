//
//  singleton.hpp
//  EXPUtil
//
//  Created by Nick Fagan on 12/9/17.
//

#ifndef singleton_h
#define singleton_h

namespace EXP {
    template<typename T>
    struct singleton
    {
    public:
        static T& get()
        {
            static T instance;
            return instance;
        }
        singleton<T>(singleton<T> const&) = delete;
        void operator=(singleton<T> const&) = delete;
    protected:
        singleton<T>() = default;
    };
}

#endif /* singleton_h */
