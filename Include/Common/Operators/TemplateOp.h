#ifndef _TEMPLATEOP_HPP
#define _TEMPLATEOP_HPP
#include "Common/Numeric/Promotion.h"
#include "Common/Utils/Empty.h"

template<template<typename,typename> class OpT1,template<typename,typename> class OpT2,typename P = Empty>
struct LessThanComparable
    :P
{
    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator <= (const OpT1<U1,Tag1>& lhs,const OpT2<U2,Tag2>& rhs)
    {
	return ((lhs < rhs) || (lhs == rhs));
    }

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator > (const OpT1<U1,Tag1>& lhs,const OpT2<U2,Tag2>& rhs)
    {
	return !(lhs <= rhs);
    }

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator > (const OpT1<U1,Tag1>& lhs,const OpT2<U2,Tag2>& rhs)
    {
	return !(lhs < rhs);
    }

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator <= (const OpT2<U2,Tag2>& lhs,const OpT1<U1,Tag1>& rhs)
    {
	return (rhs >= lhs); 
    }

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator > (const OpT2<U2,Tag2>& lhs,const OpT1<U1,Tag1>& rhs)
    {
	return (rhs > lhs);
    }

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator >= (const OpT2<U2,Tag2>& lhs,const OpT1<U1,Tag1>& rhs)
    {
	return (rhs <= lhs);
    }
};

template<template<typename,typename> class OpT,typename P>
struct LessThanComparable<OpT,OpT,P>
    :P
{
    template<typename T1,typename Tag1,typename T2,typename Tag2>
    friend bool operator <= (const OpT<T1,Tag1>& lhs,const OpT<T2,Tag2>& rhs)
    {
	return ((lhs < rhs) || (lhs == rhs));
    }

    template<typename T1,typename Tag1,typename T2,typename Tag2>
    friend bool operator > (const OpT<T1,Tag1>& lhs,const OpT<T2,Tag2>& rhs)
    {
	return !(lhs <= rhs);
    }

    template<typename T1,typename Tag1,typename T2,typename Tag2>
    friend bool operator >= (const OpT<T1,Tag1>& lhs,const OpT<T2,Tag2>& rhs)
    {
	return !(lhs < rhs);
    }
};

template<template<typename,typename> class OpT1,template<typename,typename> class OpT2,typename P = Empty>
struct EqualityComparable
    :P
{
    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator == (const OpT2<U2,Tag2>& lhs,const OpT1<U1,Tag1>& rhs)
    {
	return (rhs == lhs);
    }

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator != (const OpT1<U1,Tag1>& lhs,const OpT2<U2,Tag2>& rhs)
    {
	return !(lhs == rhs);
    }

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator != (const OpT2<U2,Tag2>& lhs,const OpT1<U1,Tag1>& rhs)
    {
	return !(rhs == lhs);
    }
};

template<template <typename,typename> class OpT,typename P>
struct EqualityComparable<OpT,OpT,P>
    :P
{
    template<typename T1,typename Tag1,typename T2,typename Tag2>
    friend bool operator != (const OpT<T1,Tag1>& lhs,const OpT<T2,Tag2>& rhs)
    {
	return !(lhs == rhs);
    }
};

template<template<typename,typename> class OpT,typename P = Empty>
struct Incrementable
    :P
{
    template<typename T,typename Tag>
    friend OpT<T,Tag> operator++(OpT<T,Tag>& op,int)
    {
	OpT<T,Tag> retOp(op);
	++op;
	return retOp;
    }
};

template<template<typename,typename> class OpT,typename P = Empty>
struct Decrementable
    :P
{
    template<typename T,typename Tag>
    friend OpT<T,Tag> operator--(OpT<T,Tag>& op,int)
    {
	OpT<T,Tag> retOp(op);
	--op;
	return retOp;
    }
};

#define OP_RETURNTYPE typename Promotion<OpT1<T1,Tag1>,OpT2<T2,Tag2> >::type
#define GEN_DIFF_OPERATOR(OpT1,OpT2,PP) \
    template<typename T1,typename Tag1,typename T2,typename Tag2>\
    friend const OP_RETURNTYPE operator PP (const OpT1<T1,Tag1>& lhs,const OpT2<T2,Tag2>& rhs)\
    {\
	OP_RETURNTYPE tmp(lhs);\
	tmp PP##= rhs;\
	return tmp;\
    }

#define OP_RETURNTYPE1 typename Promotion<OpT<T1,Tag1>,OpT<T2,Tag2> >::type
#define GEN_SAME_OPERATOR(OpT,PP)\
    template<typename T1,typename Tag1,typename T2,typename Tag2>\
    friend const OP_RETURNTYPE1 operator PP (const OpT<T1,Tag1>& lhs,const OpT<T2,Tag2>& rhs)\
    {\
	OP_RETURNTYPE1 tmp(lhs);\
	tmp PP##= rhs;\
	return tmp;\
    }

#define GEN_COMMUTTED_TYPE_OPS(NN,PP)\
template<template<typename,typename> class OpT1,template<typename,typename> class OpT2,typename P = Empty>\
struct NN\
    :P\
{\
    GEN_DIFF_OPERATOR(OpT1,OpT2,PP)\
    GEN_DIFF_OPERATOR(OpT2,OpT1,PP)\
};\
template<template<typename,typename> class OpT,typename P>\
struct NN<OpT,OpT,P>\
    :P\
{\
    GEN_SAME_OPERATOR(OpT,PP)\
};\

GEN_COMMUTTED_TYPE_OPS(Addable,+)
GEN_COMMUTTED_TYPE_OPS(Multipliable,*)
GEN_COMMUTTED_TYPE_OPS(Orable,|)
GEN_COMMUTTED_TYPE_OPS(Andable,&)
GEN_COMMUTTED_TYPE_OPS(XOrable,^)
GEN_COMMUTTED_TYPE_OPS(LeftShiftAble,<<)
GEN_COMMUTTED_TYPE_OPS(RightShiftAble,>>)

#define GEN_PARTIAL_TYPE_OPS(NN,PP)\
template<template<typename,typename> class OpT1,template<typename,typename> class OpT2,typename P = Empty>\
struct NN\
    :P\
{\
    GEN_DIFF_OPERATOR(OpT1,OpT2,PP)\
};\
template<template<typename,typename> class OpT1,template<typename,typename> class OpT2,typename P = Empty>\
struct NN##Left\
    :P\
{\
    GEN_DIFF_OPERATOR(OpT2,OpT1,PP)\
};\
template<template<typename,typename> class OpT,typename P>\
struct NN<OpT,OpT,P>\
    :P\
{\
    GEN_SAME_OPERATOR(OpT,PP)\
};\

GEN_PARTIAL_TYPE_OPS(Subtractable,-)
GEN_PARTIAL_TYPE_OPS(Dividable,/)
GEN_PARTIAL_TYPE_OPS(Modable,%)

#define GEN_COMPONENT_OPS(NN,N1,N2)\
template<template<typename,typename> class OpT1,template<typename,typename> class OpT2,typename P = Empty>\
struct NN\
    :N1<OpT1,OpT2\
    ,N2<OpT1,OpT2,P> >\
{};
#define GEN_COMPONENT_OPS1(NN,N1,N2,N3)\
template<template<typename,typename> class OpT1,template<typename,typename> class OpT2,typename P = Empty>\
struct NN\
    :N1<OpT1,OpT2\
    ,N2<OpT1,OpT2\
    ,N3<OpT1,OpT2,P> > >\
{};
#define SPECIALFY_COMPONENT_OPS(NN,N1,N2)\
template<template<typename,typename> class OpT,typename P>\
struct NN<OpT,OpT,P>\
    :N1<OpT,OpT\
    ,N2<OpT,OpT,P> >\
{};

template<template<typename,typename> class OpT,typename P>
struct UnitSteppable
    :Incrementable<OpT,Decrementable<OpT,P> >
{};
GEN_COMPONENT_OPS(TotallyOrdered,LessThanComparable,EqualityComparable)
GEN_COMPONENT_OPS(ShiftAble,LeftShiftAble,RightShiftAble)
GEN_COMPONENT_OPS(Additive,Addable,Subtractable)
GEN_COMPONENT_OPS(Multiplicative,Multipliable,Dividable)
GEN_COMPONENT_OPS(IntegerMultiplicative,Multiplicative,Modable)
GEN_COMPONENT_OPS(Arithmetic,Additive,Multiplicative)
GEN_COMPONENT_OPS(IntegerArithmetic,Additive,IntegerMultiplicative)
GEN_COMPONENT_OPS1(Bitwise,Andable,Orable,XOrable)
GEN_COMPONENT_OPS1(RingOperators,Additive,SubtractableLeft,Multipliable)
SPECIALFY_COMPONENT_OPS(RingOperators,Additive,Multipliable)
GEN_COMPONENT_OPS(OrderedRingOperators,RingOperators,TotallyOrdered)
GEN_COMPONENT_OPS1(FieldOperators,RingOperators,Dividable,DividableLeft)
SPECIALFY_COMPONENT_OPS(FieldOperators,RingOperators,Dividable)
GEN_COMPONENT_OPS(OrderedFieldOperators,FieldOperators,TotallyOrdered)
GEN_COMPONENT_OPS1(EuclidianRingOperators,FieldOperators,Modable,ModableLeft)
SPECIALFY_COMPONENT_OPS(EuclidianRingOperators,FieldOperators,Modable)
GEN_COMPONENT_OPS(OrderedEuclidianRingOperators,EuclidianRingOperators,TotallyOrdered)
#undef GEN_DIFF_OPERATOR
#undef GEN_SAME_OPERATOR
#undef GEN_COMMUTTED_TYPE_OPS
#undef GEN_PARTIAL_TYPE_OPS
#undef GEN_COMPONENT_OPS 
#undef GEN_COMPONENT_OPS1
#undef SPECIALFY_COMPONENT_OPS
#endif

