//
//  row_impl.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/13/17.
//

#ifndef row_impl_h
#define row_impl_h

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
    }
}


template<typename ...T>
EXP::sql::row<T...>::row(T... inputs)
{
    fields = std::make_tuple<inputs...>();
}

template<typename ...T>
template<int N>
constexpr auto& EXP::sql::row<T...>::get()
{
    return std::get<N>(fields);
}

template<typename ...T>
template<typename X>
constexpr auto& EXP::sql::row<T...>::get()
{
    return std::get<X>(fields);
}

template<typename ...T>
template<int N, typename X>
bool EXP::sql::row<T...>::commit(X data)
{
    auto &field_ = get<N>();
    return field_.commit(data);
}

template<typename ...T>
template<typename L, typename X>
bool EXP::sql::row<T...>::commit(X data)
{
    auto &field_ = get<L>();
    return field_.commit(data);
}

template<typename ...T>
void EXP::sql::row<T...>::reset()
{
    for_each([] (auto &x) { x.reset(); });
}

template<typename ...T>
bool EXP::sql::row<T...>::all_committed()
{
    std::string dummy_non_committed;
    return all_committed(dummy_non_committed);
}

template<typename ...T>
bool EXP::sql::row<T...>::all_committed(std::string &non_committed)
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

template<typename ...T>
template<typename F>
void EXP::sql::row<T...>::for_each(F f)
{
    for_each_impl(fields, f, gen_seq<N>());
}

template<typename ...T>
constexpr int EXP::sql::row<T...>::size()
{
    return N;
}

#endif /* row_impl_h */
