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
struct Promotion<T,T>{ //���������ͬ���͵ľֲ��ػ�
	typedef T type;
};
//�Ի������ͺ�ö�����ͣ�����Ҫ����Ϊ�����ĸ�ǿ������ͣ�
//����Ҫ������ػ�ʵ�֣�Ϊ�����û�ʹ�ã������Ƕ���ɺ�
//��T1,T2����ΪTr
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
