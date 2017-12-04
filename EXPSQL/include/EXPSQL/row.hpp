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

// https://stackoverflow.com/questions/16387354/template-tuple-calling-a-function-on-each-element

namespace {
    template<int... Is>
    struct seq {};
    
    template<int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};
    
    template<int... Is>
    struct gen_seq<0, Is...> : seq<Is...> {};
    
    template<typename T, typename F, int... Is>
    void for_each_impl(T&& t, F f, seq<Is...>)
    {
        auto l = { (f(std::get<Is>(t)), 0)... };
    }
}

template<typename ...T>
class row
{
public:
    row() {};
    row(T... inputs) : fields(inputs...)
    {
        //
    }
    
    ~row() = default;
    
    template<int N>
    constexpr auto& get()
    {
        return std::get<N>(fields);
    }
    
    template<int N, typename X>
    bool commit(X data)
    {
        auto &field_ = get<N>();
        return field_.commit(data);
    }
    
    void reset()
    {
        for_each([] (auto &x) { x.reset(); });
    }
    
    bool all_committed(std::string &non_committed)
    {
        bool any_not_committed = false;
        for_each([&any_not_committed, &non_committed] (const auto &x) {
            if (!x.did_commit)
            {
                any_not_committed = true;
                non_committed += x.get_name() + ",";
            }
        });
        return !any_not_committed;
    }
    
    template<typename F>
    void for_each(F f)
    {
        for_each_impl(fields, f, gen_seq<N>());
    }
    
private:
    static const int N = (sizeof...(T));
    std::tuple<T...> fields;
};

}
}


#endif /* row_h */
