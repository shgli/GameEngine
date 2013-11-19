#ifndef _TYPEOP_HPP
#define _TYPEOP_HPP
#include <boost/operators.hpp>
#include "Common/Numeric/Promotion.h"
#include "Common/Utils/Empty.h"
template<typename OpT1,typename OpT2,typename P = Empty>
struct TLessThanComparable
    :P
{
    friend bool operator <= (const OpT1& lhs,const OpT2& rhs)
    {
	return ((lhs < rhs) || (lhs == rhs));
    }

    friend bool operator > (const OpT1& lhs,const OpT2& rhs)
    {
	return !(lhs <= rhs);
    }

    friend bool operator >= (const OpT1& lhs,const OpT2& rhs)
    {
	return !(lhs < rhs);
    }

    friend bool operator <= (const OpT2& lhs,const OpT1& rhs)
    {
	return (rhs >= lhs); 
    }

    friend bool operator < (const OpT2& lhs,const OpT1& rhs)
    {
	return (rhs > lhs);
    }

    friend bool operator >= (const OpT2& lhs,const OpT1& rhs)
    {
	return (rhs <= lhs);
    }
};

template<typename OpT,typename P>
struct TLessThanComparable<OpT,OpT,P>
    :P
{
    friend bool operator <= (const OpT& lhs,const OpT& rhs)
    {
	return ((lhs < rhs) || (lhs == rhs));
    }

    friend bool operator > (const OpT& lhs,const OpT& rhs)
    {
	return !(lhs <= rhs);
    }

    friend bool operator >= (const OpT& lhs,const OpT& rhs)
    {
	return !(lhs < rhs);
    }
};

template<typename OpT1,typename OpT2,typename P = Empty>
struct TEqualityComparable
    :P
{
    friend bool operator == (const OpT2& lhs,const OpT1& rhs)
    {
	return (rhs == lhs);
    }

    friend bool operator != (const OpT1& lhs,const OpT2& rhs)
    {
	return !(lhs == rhs);
    }

    friend bool operator != (const OpT2& lhs,const OpT1& rhs)
    {
	return !(rhs == lhs);
    }
};

template<typename OpT,typename P>
struct TEqualityComparable<OpT,OpT,P>
    :P
{
    friend bool operator != (const OpT& lhs,const OpT& rhs)
    {
	return !(lhs == rhs);
    }
};

#define GEN_DIFF_OPERATOR(T1,T2,PP) \
    friend const PT(T1,T2) operator PP (const T1& lhs,const T2& rhs)\
    {\
	PT(T1,T2) tmp(lhs);\
	tmp PP##= rhs;\
	return tmp;\
    }

#define GEN_SAME_OPERATOR(T,PP)\
friend const T operator PP (const T& lhs,const T& rhs)\
    {\
	T tmp(lhs);\
	tmp PP##= rhs;\
	return tmp;\
    }

#define GEN_COMMUTTED_TYPE_OPS(NN,PP)\
template<typename OpT1,typename OpT2,typename P = Empty>\
struct NN\
    :P\
{\
    GEN_DIFF_OPERATOR(OpT1,OpT2,PP)\
    GEN_DIFF_OPERATOR(OpT2,OpT1,PP)\
};\
template<typename OpT,typename P>\
struct NN<OpT,OpT,P>\
    :P\
{\
    GEN_SAME_OPERATOR(OpT,PP)\
};\

GEN_COMMUTTED_TYPE_OPS(TAddable,+)
GEN_COMMUTTED_TYPE_OPS(TMultipliable,*)
GEN_COMMUTTED_TYPE_OPS(TOrable,|)
GEN_COMMUTTED_TYPE_OPS(TAndable,&)
GEN_COMMUTTED_TYPE_OPS(TXOrable,^)
GEN_COMMUTTED_TYPE_OPS(TLeftShiftAble,<<)
GEN_COMMUTTED_TYPE_OPS(TRightShiftAble,>>)
#define GEN_PARTIAL_TYPE_OPS(NN,PP)\
template<typename OpT1,typename OpT2,typename P = Empty>\
struct NN\
    :P\
{\
    GEN_DIFF_OPERATOR(OpT1,OpT2,PP)\
};\
template<typename OpT1,typename OpT2,typename P = Empty>\
struct NN##Left\
    :P\
{\
    GEN_DIFF_OPERATOR(OpT2,OpT1,PP)\
};\
template<typename OpT,typename P>\
struct NN<OpT,OpT,P>\
    :P\
{\
    GEN_SAME_OPERATOR(OpT,PP)\
};\

GEN_PARTIAL_TYPE_OPS(TSubtractable,-)
GEN_PARTIAL_TYPE_OPS(TDividable,/)
GEN_PARTIAL_TYPE_OPS(TModable,%)

#define GEN_COMPONENT_OPS(NN,N1,N2)\
template<typename OpT1,typename OpT2,typename P = Empty>\
struct NN\
    :N1<OpT1,OpT2\
    ,N2<OpT1,OpT2,P> >\
{};
#define GEN_COMPONENT_OPS1(NN,N1,N2,N3)\
template<typename OpT1,typename OpT2,typename P = Empty>\
struct NN\
    :N1<OpT1,OpT2\
    ,N2<OpT1,OpT2\
    ,N3<OpT1,OpT2,P> > >\
{};
#define SPECIALFY_COMPONENT_OPS(NN,N1,N2)\
template<typename OpT,typename P>\
struct NN<OpT,OpT,P>\
    :N1<OpT,OpT\
    ,N2<OpT,OpT,P> >\
{};


GEN_COMPONENT_OPS(TTotallyOrdered,TLessThanComparable,TEqualityComparable)
GEN_COMPONENT_OPS(TShiftAble,TLeftShiftAble,TRightShiftAble)
GEN_COMPONENT_OPS(TAdditive,TAddable,TSubtractable)
GEN_COMPONENT_OPS(TMultiplicative,TMultipliable,TDividable)
GEN_COMPONENT_OPS(TIntegerMultiplicative,TMultiplicative,TModable)
GEN_COMPONENT_OPS(TArithmetic,TAdditive,TMultiplicative)
GEN_COMPONENT_OPS(TIntegerArithmetic,TAdditive,TIntegerMultiplicative)
GEN_COMPONENT_OPS1(TBitwise,TAndable,TOrable,TXOrable)
GEN_COMPONENT_OPS1(TRingOperators,TAdditive,TSubtractableLeft,TMultipliable)
SPECIALFY_COMPONENT_OPS(TRingOperators,TAdditive,TMultipliable)
GEN_COMPONENT_OPS(TOrderedRingOperators,TRingOperators,TTotallyOrdered)
GEN_COMPONENT_OPS1(TFieldOperators,TRingOperators,TDividable,TDividableLeft)
SPECIALFY_COMPONENT_OPS(TFieldOperators,TRingOperators,TDividable)
GEN_COMPONENT_OPS(TOrderedFieldOperators,TFieldOperators,TTotallyOrdered)
GEN_COMPONENT_OPS1(TEuclidianRingOperators,TFieldOperators,TModable,TModableLeft)
SPECIALFY_COMPONENT_OPS(TEuclidianRingOperators,TFieldOperators,TModable)
GEN_COMPONENT_OPS(TOrderedEuclidianRingOperators,TEuclidianRingOperators,TTotallyOrdered)
#undef GEN_DIFF_OPERATOR
#undef GEN_SAME_OPERATOR
#undef GEN_COMMUTTED_TYPE_OPS
#undef GEN_PARTIAL_TYPE_OPS
#undef GEN_COMPONENT_OPS 
#undef GEN_COMPONENT_OPS1
#undef SPECIALFY_COMPONENT_OPS

#define TUnitSteppable boost::unit_steppable
#endif

