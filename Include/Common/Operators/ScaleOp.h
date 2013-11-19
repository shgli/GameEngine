#ifndef _SCALEOP_HPP
#define _SCALEOP_HPP
#include <boost/operators.hpp>
#include "Common/Numeric/Promotion.h"
#include "Common/Utils/Empty.h"
#include "Common/Numeric/CIntypes.h"
#define CALL4SCALE(MACRO,a)  MACRO(a,uint8_t) MACRO(a,uint16_t) MACRO(a,uint32_t) MACRO(a,uint64_t) \
        MACRO(a,int8_t) MACRO(a,int16_t) MACRO(a,int32_t) MACRO(a,int64_t) MACRO(a,float) MACRO(a,double)

template<template<typename,typename> class OpT,typename P = Empty>
struct SLessThanComparable
    :P
{
#define LESSTHANOP(a,U)\
    template<typename T,typename Tag>\
    friend bool operator <= (const OpT<T,Tag>& lhs,const U& rhs)\
    {\
	return ((lhs < rhs) || (lhs == rhs));\
    }\
\
    template<typename T,typename Tag>\
    friend bool operator > (const OpT<T,Tag>& lhs,const U& rhs)\
    {\
	return !(lhs <= rhs);\
    }\
\
    template<typename T,typename Tag>\
    friend bool operator >= (const OpT<T,Tag>& lhs,const U& rhs)\
    {\
	return !(lhs < rhs);\
    }\
\
    template<typename T,typename Tag>\
    friend bool operator <= (const U& lhs,const OpT<T,Tag>& rhs)\
    {\
	return (rhs >= lhs); \
    }\
\
    template<typename T,typename Tag>\
    friend bool operator < (const U& lhs,const OpT<T,Tag>& rhs)\
    {\
	return (rhs > lhs);\
    }\
\
    template<typename T,typename Tag>\
    friend bool operator >= (const U& lhs,const OpT<T,Tag>& rhs)\
    {\
	return (rhs <= lhs);\
    }

    CALL4SCALE(LESSTHANOP,~)
#undef LESSTHANOP
};

template<template<typename,typename> class OpT,typename P = Empty>
struct SEqualityComparable
    :P
{
#define EQUALITYOP(a,U)\
    template<typename T,typename Tag>\
    friend bool operator != (const OpT<T,Tag>& lhs,const U& rhs)\
    {\
	return !(lhs == rhs);\
    }\
\
    template<typename T,typename Tag>\
    friend bool operator == (const U& lhs,const OpT<T,Tag>& rhs)\
    {\
	return (rhs == lhs);\
    }\
\
    template<typename T,typename Tag>\
    friend bool operator != (const U& lhs,const OpT<T,Tag>& rhs)\
    {\
	return !(rhs == lhs);\
    }

    CALL4SCALE(EQUALITYOP,~)
#undef EQUALITYOP
};
template<typename T,typename U> struct NumericTagTraits;
#define GEN_DIFF_OPERATOR(PP,U) \
    template<typename T,typename Tag>\
    friend const OpT<PT(T,U),typename NumericTagTraits<T,U>::type> operator PP (const OpT<T,Tag>& lhs,const U& rhs)\
    {\
	OpT<PT(T,U),typename NumericTagTraits<T,U>::type> tmp(lhs);\
	tmp PP##= rhs;\
	return tmp;\
    }

#define GEN_DIFF_OPERATOR1(PP,U)\
    template<typename T,typename Tag>\
    friend const OpT<PT(T,U),typename NumericTagTraits<T,U>::type> operator PP (const U& lhs,const OpT<T,Tag>& rhs)\
    {\
	OpT<PT(T,U),typename NumericTagTraits<T,U>::type> tmp(lhs);\
	tmp PP##= rhs;\
	return tmp;\
    }

#define GEN_COMMUTTED_TYPE_OPS(NN,PP)\
template<template<typename,typename> class OpT,typename P = Empty>\
struct NN\
    :P\
{\
    CALL4SCALE(GEN_DIFF_OPERATOR,PP) \
    CALL4SCALE(GEN_DIFF_OPERATOR1,PP)\
};

GEN_COMMUTTED_TYPE_OPS(SAddable,+)
GEN_COMMUTTED_TYPE_OPS(SMultipliable,*)
GEN_COMMUTTED_TYPE_OPS(SOrable,|)
GEN_COMMUTTED_TYPE_OPS(SAndable,&)
GEN_COMMUTTED_TYPE_OPS(SXOrable,^)
GEN_COMMUTTED_TYPE_OPS(SLeftShiftAble,<<)
GEN_COMMUTTED_TYPE_OPS(SRightShiftAble,>>)

#define GEN_PARTIAL_TYPE_OPS(NN,PP)\
template<template<typename,typename> class OpT,typename P = Empty>\
struct NN\
    :P\
{\
    CALL4SCALE(GEN_DIFF_OPERATOR,PP)\
};\
template<template<typename,typename> class OpT,typename P = Empty>\
struct NN##Left\
    :P\
{\
    CALL4SCALE(GEN_DIFF_OPERATOR1,PP)\
};

GEN_PARTIAL_TYPE_OPS(SSubtractable,-)
GEN_PARTIAL_TYPE_OPS(SDividable,/)
GEN_PARTIAL_TYPE_OPS(SModable,%)

#define GEN_COMPONENT_OPS(NN,N1,N2)\
template<template<typename,typename> class OpT,typename P = Empty>\
struct NN\
    :N1<OpT\
    ,N2<OpT,P> >\
{};
#define GEN_COMPONENT_OPS1(NN,N1,N2,N3)\
template<template<typename,typename> class OpT,typename P = Empty>\
struct NN\
    :N1<OpT\
    ,N2<OpT\
    ,N3<OpT,P> > >\
{};


GEN_COMPONENT_OPS(STotallyOrdered,SLessThanComparable,SEqualityComparable)
GEN_COMPONENT_OPS(SShiftAble,SLeftShiftAble,SRightShiftAble)
GEN_COMPONENT_OPS(SAdditive,SAddable,SSubtractable)
GEN_COMPONENT_OPS(SMultiplicative,SMultipliable,SDividable)
GEN_COMPONENT_OPS(SIntegerMultiplicative,SMultiplicative,SModable)
GEN_COMPONENT_OPS(SArithmetic,SAdditive,SMultiplicative)
GEN_COMPONENT_OPS(SIntegerArithmetic,SAdditive,SIntegerMultiplicative)
GEN_COMPONENT_OPS1(SBitwise,SAndable,SOrable,SXOrable)
GEN_COMPONENT_OPS1(SRingOperators,SAdditive,SSubtractableLeft,SMultipliable)
GEN_COMPONENT_OPS(SOrderedRingOperators,SRingOperators,STotallyOrdered)
GEN_COMPONENT_OPS1(SFieldOperators,SRingOperators,SDividable,SDividableLeft)
GEN_COMPONENT_OPS(SOrderedFieldOperators,SFieldOperators,STotallyOrdered)
GEN_COMPONENT_OPS1(SEuclidianRingOperators,SFieldOperators,SModable,SModableLeft)
GEN_COMPONENT_OPS(SOrderedEuclidianRingOperators,SEuclidianRingOperators,STotallyOrdered)
#undef GEN_DIFF_OPERATOR
#undef GEN_DIFF_OPERATOR1
#undef GEN_COMMUTTED_TYPE_OPS
#undef GEN_COMPONENT_OPS 
#undef GEN_COMPONENT_OPS1
#undef GEN_PARTIAL_TYPE_OPS
#undef SPECIALFY_COMPONENT_OPS

#endif

