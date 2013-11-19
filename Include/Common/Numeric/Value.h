#ifndef _VALUE_GETTER_HPP
#define _VALUE_GETTER_HPP
#include <boost/type_traits/is_class.hpp>

template<bool isClass,typename T>
struct Value
{
    typedef typename T::value_type value_type;
    static  value_type get(const T& v){return v.value;}
};

template<typename T>
struct Value<false,T>
{
    typedef T value_type;
    static value_type get(const T& v) {return v;}
};

template<typename T>
typename Value<boost::is_class<T>::value,T>::value_type GetValue(const T& v)
{
    return Value<boost::is_class<T>::value,T>::get(v);
}
#endif

