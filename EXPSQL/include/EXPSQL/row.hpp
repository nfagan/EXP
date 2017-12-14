//
//  row.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/24/17.
//

#ifndef exp_sql_row_h
#define exp_sql_row_h

#include <EXPSQL/field.hpp>
#include <tuple>

namespace EXP {
    namespace sql {
        template<typename ...T>
        class row
        {
        public:
            row() = default;
            row(T... inputs);
            ~row() = default;
            
            template<int N>
            constexpr auto& get();
            
            template<typename X>
            constexpr auto& get();
            
            template<int N, typename X>
            bool commit(X data);
            
            template<typename L, typename X>
            bool commit(X data);
            
            void reset();
            
            bool all_committed();
            bool all_committed(std::string &non_committed);
            
            template<typename F>
            void for_each(F f);
            
            constexpr int size();
        private:
            static const int N = (sizeof...(T));
            std::tuple<T...> fields;
        };
    }
}

//
// impl
//

#include <EXPSQL/row_impl.hpp>

#endif /* row_h */
