//
//  get_full_path.hpp
//  EXPUtil
//
//  Created by Nick Fagan on 12/3/17.
//

#ifndef get_full_path_h
#define get_full_path_h

#include <string>

namespace EXP {
    namespace file {
        static std::string get_full_path(const char *relative)
        {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            char full[_MAX_PATH];
            if (_fullpath(full, relative, _MAX_PATH) != NULL)
            {
                return std::string(full);
            }
            else
            {
                std::cout << "Invalid path" << std::endl;
                return "";
            }
#else
            char *abs_path = realpath(relative, nullptr);
            if (!abs_path)
            {
                std::cout << "Invalid path" << std::endl;
                return "";
            }
            return std::string(abs_path);
            free(abs_path);
#endif
        }
    }
}

#endif /* get_full_path_h */
