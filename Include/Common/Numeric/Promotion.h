//promote1.hpp
#ifndef PROMOTION_HPP
#define PROMOTION_HPP
#include <boost/mpl/if.hpp>
template<typename T1,typename T2>
struct Promoted
{
    static const bool value = sizeof(T1) > sizeof(T2);
    typedef Promoted<T1,T2> type;
};

template<typename T1,typename T2>
struct Promotion
    :boost::mpl::if_<Promoted<T1,T2>,T1,T2>
{};

template<typename T>
struct Promotion<T,T>{ //针对两个相同类型的局部特化
	typedef T type;
};
//对基本类型和枚举类型：可能要提升为其他的更强大的类型，
//这需要另外的特化实现，为方便用户使用，把它们定义成宏
//把T1,T2提升为Tr
#define MK_PROMOTION(T1,T2,Tr)  \
template<> struct Promotion<T1,T2>\
{   \
    typedef Tr type;\
};\
\
template<>struct Promotion<T2,T1>\
{\
    typedef Tr type;\
};

#define PT(T1,T2) typename Promotion<T1,T2>::type
#endif
