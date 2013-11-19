// DataTypeDef.h
// 版权所有(C) 李书淦
// Homepage:
// Email:asd1831031@163.com
// purpose:
// 初次建立:2009/1/2
/////////////////////////////////////////////////////////////////////////////////
#ifndef _DATATYPEDEF_H
#define _DATATYPEDEF_H
#include <bitset>
#include <boost/cstdint.hpp>
#include <boost/type_traits/is_float.hpp>
#include "Common/Operators/TemplateOp.h"
#include "Common/Operators/ScaleOp.h"
#include "Common/Operators/TypeOp.h"
#include "Common/Numeric/NumericPromos.h"
#include "Common/Numeric/Value.h"
#include "Common/Numeric/CIntypes.h"
using namespace boost;

class BitsView
{
public:
    static const size_t SIZE_OF_BITS = 64;
    std::bitset<SIZE_OF_BITS> m_bits;

    bool Test(size_t nPos)const {return m_bits.test(nPos);}
    void Set(size_t nPos) {m_bits.set(nPos);}
    void Reset(size_t nPos){m_bits.reset(nPos);}
    void Flip( void ){m_bits.flip();}
    void Flip(size_t nPos ){m_bits.flip(nPos);}

    std::string ToString( size_t nSize = 8 ,size_t nGroup = 16)
    {
	const static char I_TO_H[] = "0123456789abcdef";
	std::string strRet;
	for(size_t nStart = SIZE_OF_BITS - 8 * nSize;nStart < SIZE_OF_BITS; nStart += 4)
	{
	    strRet += I_TO_H[(m_bits.test(nStart) ? 8 : 0) + (m_bits.test(nStart + 1) ? 4 : 0)
	       	+ (m_bits.test(nStart + 2) ? 2 : 0) + (m_bits.test(nStart + 3) ? 1 : 0)];

	    if((nGroup - 4) == (nStart % nGroup))
	    {
		strRet += ' ';
	    }
	}
	strRet.erase(strRet.size() - 1);

	return strRet;
    }
};

BitsView GetBitsView(uint64_t v);
template<typename T,typename U,typename P = Empty>
struct IntegerOps
    :TOrderedEuclidianRingOperators<T,U
    ,TBitwise<T,U
    ,TShiftAble<T,U,P> > >
{};

struct NumericBaseTag{};
struct IntTag
{
    template<typename T,typename U>
    static bool LessThan(const T& lhs,const U& rhs) { return lhs < rhs; }

    template<typename T,typename U>
    static bool Equal(const T& lhs,const U& rhs) { return lhs == rhs; }

    template<typename T>
    static T INFINATE(bool isPositive) { return isPositive ? MAX_INT : -MAX_INT ;}

    static int32_t ZeroThreshold() { return 0; }
};

struct FloatTag
{
    template<typename T,typename U>
    static bool LessThan(T lhs,U rhs)
    {
	return !Equal(lhs,rhs) && (lhs < rhs);
    }

    template<typename T,typename U>
    static bool Equal(T v1,U v2) 
    { 
    	bool bEqual = (v1 - v2 <= 0) ? ((v2 - v1)  <= 1.00e-06) : ((v1 - v2) <= 1.00e-06);
        return  bEqual;
    }

    template<typename T>
    static T INFINATE(bool isPositive) { return isPositive ? MAX_REAL : -MAX_REAL;}

    static double ZeroThreshold() { return EPSILON; }

};

template<typename U1,typename U2>
struct NumericTagTraits
{
    typedef typename mpl::if_<is_float<U1>
	                     ,FloatTag
			     ,typename mpl::if_<is_float<U2>,FloatTag,IntTag>::type
			     >::type type;
};

//========================define of Numeric base =================================
template<typename T,typename Tag>
struct DLLEXPORT Numeric
    :Tag
{
public:
    typedef T value_type;
    T value;

    Numeric(T v = T()):value(v){}

    operator const T ( void ) const { return value;}

public:
    size_t Size( void )const {return sizeof(T);}

    Numeric operator- ( void ) const { return Numeric(-value);}

    Numeric Abs( void ) const { return (value > 0 ? value : -value) ;}

    template<typename U,typename TagU>
    Numeric& operator += (const Numeric<U,TagU>& rhs);

    template<typename U,typename TagU>
    Numeric& operator -= (const Numeric<U,TagU>& rhs);

    template<typename U,typename TagU>
    Numeric& operator *= (const Numeric<U,TagU>& rhs);

    template<typename U,typename TagU>
    Numeric& operator /= (const Numeric<U,TagU>& rhs);

#define GEN_NUMERIC_SELFOP_DECLARE(OP)\
    template<typename U>\
    Numeric& operator OP##=(U o);
GEN_NUMERIC_SELFOP_DECLARE(+)
GEN_NUMERIC_SELFOP_DECLARE(-)
GEN_NUMERIC_SELFOP_DECLARE(*)
GEN_NUMERIC_SELFOP_DECLARE(/)
#undef GEN_NUMERIC_SELFOP_DECLARE

    Numeric& operator++() {++this->value;return *this;}

    Numeric& operator--() {--this->value;return *this;}

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator < (const Numeric<U1,Tag1>&,const Numeric<U2,Tag2>&);

    template<typename U1,typename Tag1,typename U2,typename Tag2>
    friend bool operator == (const Numeric<U1,Tag1>&,const Numeric<U2,Tag2>&);

    template<typename U1,typename Tag1,typename U2>
    friend bool operator < (const Numeric<U1,Tag1>&,U2 );

    template<typename U1,typename Tag1,typename U2>
    friend bool operator > (U2 ,const Numeric<U1,Tag1>&);

    template<typename U1,typename Tag1,typename U2>
    friend bool operator == (const Numeric<U1,Tag1>&,U2);

    template<typename U1,typename Tag1>
    friend std::ostream& operator<<(std::ostream& os,const Numeric<U1,Tag1>& o);

    template<typename U1,typename Tag1>
    friend std::istream& operator>>(std::istream& os,Numeric<U1,Tag1>& o);
};

#define BACK_HACK(z,n,text) >
struct NumericOperators
    :SOrderedFieldOperators<Numeric               
    ,UnitSteppable<Numeric
    ,OrderedFieldOperators<Numeric,Numeric,Empty
    BOOST_PP_REPEAT(3,BACK_HACK,~)                 
{};

//=======================================define of integer==============================
#define INT_TAG SModable< ::Numeric\
	    ,SBitwise< ::Numeric\
		,SShiftAble< ::Numeric\
		,Modable< ::Numeric,::Numeric\
		,Bitwise< ::Numeric,::Numeric\
		,ShiftAble< ::Numeric,::Numeric,NumericOperators\
		BOOST_PP_REPEAT(6,BACK_HACK,~)
 
template<typename T>
struct DLLEXPORT Numeric<T,IntTag>
    :Numeric<T,INT_TAG>
{
    using Numeric<T,INT_TAG>::value;
    using Numeric<T,INT_TAG>::Size;

    Numeric(T v = T()):Numeric<T,INT_TAG>(v){}

    template<typename U,typename Tag> 
    Numeric(const Numeric<U,Tag>& o):Numeric<T,INT_TAG>(o.value){}

    BitsView TrueCode( void )const;

    BitsView OnesComplementalCode( void )const;
   
    BitsView ComplementalCode( void )const;

    std::string ToString( void )const { return ComplementalCode().ToString(sizeof(T)); }
    
#define GEN_INT_SELFOP_DECLARE(OP)\
    template<typename U>\
    Numeric& operator OP##=(U o);
GEN_INT_SELFOP_DECLARE(%)
GEN_INT_SELFOP_DECLARE(<<)
GEN_INT_SELFOP_DECLARE(>>)
GEN_INT_SELFOP_DECLARE(&)
GEN_INT_SELFOP_DECLARE(|)
GEN_INT_SELFOP_DECLARE(^)
#undef GEN_INT_SELFOP_DECLARE

};


//========================================define of Float ==================================
template<typename T>
struct FloatLayoutInfo;

template<>
struct FloatLayoutInfo<Float>
{
    typedef Int32 type;
    static const uint64_t Mask = 0x007fffff;
    static const uint64_t ExpSize = 8;
};

template<>
struct FloatLayoutInfo<Double>
{
    typedef Int64 type;
    static const uint64_t Mask = 0x000fffffffffffff;
    static const uint64_t ExpSize = 11 ;
};

                     
#define FLOAT_TAG NumericOperators
template<typename T>
struct DLLEXPORT Numeric<T,FloatTag>
    :Numeric<T,FLOAT_TAG>
{
    using Numeric<T,FLOAT_TAG>::value;    
    using Numeric<T,FLOAT_TAG>::Size;

    Numeric(T v = T()):Numeric<T,FLOAT_TAG>(v){}

    template<typename U,typename Tag>
    Numeric(const Numeric<U,Tag>& o):Numeric<T,FLOAT_TAG>(o.value){}

    Int16 Exponent( void )const;
    typename FloatLayoutInfo<Numeric>::type Fraction( void )const;

    std::string ToString( void )const;
};

#include "Src/Common/Numeric.hpp"
#endif

