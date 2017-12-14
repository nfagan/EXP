//
//  Field.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 11/15/17.
//

#ifndef exp_Field_hpp
#define exp_Field_hpp

#include <type_traits>
#include <string>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <EXPSQL/connection.hpp>
#include <EXPSQL/data_types.hpp>

namespace EXP {
    namespace sql {
        class cursor;

        template<const char *name_, typename T>
        class field
        {
        public:
            field();
            ~field() = default;
            
            bool commit(T data);
            const T& get_data() const;
            const std::string& get_sql_type() const;
            const std::string get_name() const;
            void create_table(std::string &query) const;
            void insert_value(std::string &query) const;
            void insert_name(std::string &query) const;
            
            void reset();
            bool did_commit;
        private:
            std::string name;
            std::string sql_type;
            T data;
            
            bool set_data(T data);
            const std::string to_string() const;
        };
        
        //
        //  impl
        //

        #include <EXPSQL/field_impl.hpp>
    }
}

#endif /* Field_hpp */
