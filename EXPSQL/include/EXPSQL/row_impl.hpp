//
//  row_impl.hpp
//  EXPSQL
//
//  Created by Nick Fagan on 12/8/17.
//

#ifndef row_impl_h
#define row_impl_h

template<typename ...T>
template<typename N, typename X>
bool EXP::sql::row<T...>::commit(X data)
{
    auto &field_ = get<N>();
    return field_.commit(data);
}

//template<typename ...T>
//EXP::sql::row<T...>::row()
//{
//    //
//}
//
//template<typename ...T>
//EXP::sql::row<T...>::row(T... inputs) : fields(inputs...)
//{
//    //
//}
//
//template<typename ...T>
//template<typename X>
//constexpr auto& EXP::sql::row<T...>::get()
//{
//    return std::get<X>(fields);
//}
//
//template<typename ...T>
//template<int N>
//constexpr auto& EXP::sql::row<T...>::get()
//{
//    return std::get<N>(fields);
//}
//
//template<typename ...T>
//template<typename N, typename X>
//bool EXP::sql::row<T...>::commit(X data)
//{
//    auto &field_ = this->get<N>();
//    return field_.commit(data);
//}
//
//template<typename ...T>
//template<int N, typename X>
//bool EXP::sql::row<T...>::commit(X data)
//{
//    constexpr auto &field_ = get<N>();
//    return field_.commit(data);
//}


#endif /* row_impl_h */
