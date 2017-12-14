//
//  cursor.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/24/17.
//

#ifndef cursor_h
#define cursor_h

#include <EXPSQL/connection.hpp>
#include <EXPSQL/field.hpp>
#include <iostream>
#include <memory>
#include <sstream>

namespace EXP {
    namespace sql {
        class connection;

        template<typename ...X>
        class row;
        
        class cursor
        {
        public:
            cursor(const connection *conn);
            
            template<typename ...T>
            bool require(std::shared_ptr<row<T...>> &value, std::string name);
            
            bool size(std::string name, int *sz);
            bool drop(std::string name);
            
            template <typename ...T>
            bool create(std::shared_ptr<row<T...>> &value, std::string name) const;
            
            template<typename ...T>
            bool insert(std::shared_ptr<row<T...>> &value, int id, std::string table) const;
            
        private:
            const connection *conn = nullptr;
            bool exec(const std::string &query, std::string *result) const;
        };
        
        #include <EXPSQL/cursor_impl.hpp>
    }
}


#endif /* cursor_h */
