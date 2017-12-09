//
//  data_types.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/8/17.
//

#ifndef data_types_h
#define data_types_h

#include <string>
#include <EXPSQL/connection.hpp>

namespace EXP {
    namespace sql {
        
        //
        //  custom types
        //
        
        struct hexfloat_t
        {
            double value = 0.0;
            hexfloat_t() = default;
            hexfloat_t(double value) : value(value) {};
        };
        
        //
        //  sql type mapping
        //
        
        struct sql_field_type_real
        {
            constexpr static const char *value = "REAL";
        };
        
        struct sql_field_type_int
        {
            constexpr static const char *value = "INT";
        };
        
        struct sql_field_type_text
        {
            constexpr static const char *value = "TEXT";
        };
        
        template<typename T> struct sql_field_type;
        
        //  real
        template<> struct sql_field_type<double> : public sql_field_type_real {};
        template<> struct sql_field_type<float> : public sql_field_type_real {};
        
        //  int
        template<> struct sql_field_type<int> : public sql_field_type_int {};
        template<> struct sql_field_type<unsigned int> : public sql_field_type_int {};
        template<> struct sql_field_type<long> : public sql_field_type_int {};
        template<> struct sql_field_type<unsigned long> : public sql_field_type_int {};
        
        //  text
        template<> struct sql_field_type<std::string> : public sql_field_type_text {};
        template<> struct sql_field_type<const char*> : public sql_field_type_text {};
        template<> struct sql_field_type<hexfloat_t> : public sql_field_type_text {};
        
    }
}

#endif /* data_types_h */
