#include "Common/Utils/WordEndian.h"

template<typename U1,typename Tag1,typename U2,typename Tag2>
bool operator < (const Numeric<U1,Tag1>& lhs,const Numeric<U2,Tag2>& rhs)
{
    return NumericTagTraits<U1,U2>::type::LessThan(lhs.value,rhs.value);
}

template<typename U1,typename Tag1,typename U2,typename Tag2>
bool operator == (const Numeric<U1,Tag1>& lhs,const Numeric<U2,Tag2>& rhs)
{
    return NumericTagTraits<U1,U2>::type::Equal(lhs.value,rhs.value);
}

template<typename U1,typename Tag,typename U2>
bool operator < (const Numeric<U1,Tag>& lhs,U2 rhs)
{
    return NumericTagTraits<U1,U2>::type::LessThan(lhs.value,rhs);
}

template<typename U1,typename Tag,typename U2>
bool operator > (U2 lhs,const Numeric<U1,Tag>& rhs)
{
    return NumericTagTraits<U1,U2>::type::LessThan(rhs.value,lhs);
}

template<typename U1,typename Tag,typename U2>
bool operator == (const Numeric<U1,Tag>& lhs,U2 rhs)
{
    return NumericTagTraits<U1,U2>::type::Equal(lhs.value,rhs);
}

template<typename T,typename Tag>
template<typename U,typename TagU>
Numeric<T,Tag>& Numeric<T,Tag>::operator += (const Numeric<U,TagU>& rhs)
{
    value += rhs.value;
    return *this;
}

template<typename T,typename Tag>
template<typename U,typename TagU>
Numeric<T,Tag>& Numeric<T,Tag>::operator -= (const Numeric<U,TagU>& rhs)
{
    value -= rhs.value;
    return *this;
}

template<typename T,typename Tag>
template<typename U,typename TagU>
Numeric<T,Tag>& Numeric<T,Tag>::operator *= (const Numeric<U,TagU>& rhs)
{
    value *= rhs.value;
    return *this;
}

template<typename T,typename Tag>
template<typename U,typename TagU>
Numeric<T,Tag>& Numeric<T,Tag>::operator /= (const Numeric<U,TagU>& rhs)
{
    if(0 != rhs.value/*rhs.value > TagU::ZeroThreshold() || rhs.value < -TagU::ZeroThreshold()*/)
    {
        value /= rhs.value;
    }
    else
    {
	value = TagU::template INFINATE<T>((value > 0 && rhs.value > 0) || (value < 0 && rhs.value < 0));
    }

    return *this;
}

#define GEN_NUMERIC_OP_IMPL(OP)\
template<typename T,typename Tag>\
template<typename U>\
Numeric<T,Tag>& Numeric<T,Tag>::operator OP##= (U rhs)\
{\
    value OP##= rhs;\
    return *this;\
}
GEN_NUMERIC_OP_IMPL(+)
GEN_NUMERIC_OP_IMPL(-)
GEN_NUMERIC_OP_IMPL(*)
GEN_NUMERIC_OP_IMPL(/)
#undef GEN_NUMERIC_OP_IMPL
template<typename U1,typename Tag1>
std::ostream& operator<<(std::ostream& os,const Numeric<U1,Tag1>& o)
{
    os << o.value;
    return os;
}

template<typename U1,typename Tag1>
std::istream& operator>>(std::istream& is,Numeric<U1,Tag1>& o)
{
    is >> o.value;

    return is;
}
//=====================================implementation of int==========================
#define IntegerT Numeric<T,IntTag>
inline size_t Size2Bits(size_t nSize) {return 8 * nSize;}

template<typename T>
BitsView IntegerT::TrueCode( void )const
{
    if( value >= 0)
    {
	return GetBitsView(value);
    }
    else
    {
	BitsView ret = GetBitsView(-value);
	ret.Set(BitsView::SIZE_OF_BITS - Size2Bits(Size()));
	return ret;
    }
}

template<typename T>
BitsView IntegerT::OnesComplementalCode( void )const
{
    if( value >= 0)
    {
	return GetBitsView(value);
    }
    else
    {
	BitsView ret = GetBitsView(-value);
	ret.Flip();
	ret.Set(BitsView::SIZE_OF_BITS - Size2Bits(Size()));
	return ret;
    }
}

template<typename T>
BitsView IntegerT::ComplementalCode( void )const
{
    if(value >= 0)
    {
	return GetBitsView(value);
    }
    else
    {
	BitsView ret = GetBitsView(-value);
	ret.Flip();
	size_t nPos = BitsView::SIZE_OF_BITS - 1;
	if(ret.Test(nPos))
	{
	    ret.Reset(nPos);
	}
	ret.Set(nPos);
	ret.Set(BitsView::SIZE_OF_BITS - Size2Bits(Size()));
	return ret;
    }
}
#define GEN_INT_SELFOP_IMPL(OP) \
    template<typename T>\
    template<typename U>\
    IntegerT& IntegerT::operator OP##=(U o){ value OP##= GetValue(o);return *this;}
GEN_INT_SELFOP_IMPL(%)
GEN_INT_SELFOP_IMPL(<<)
GEN_INT_SELFOP_IMPL(>>)
GEN_INT_SELFOP_IMPL(&)
GEN_INT_SELFOP_IMPL(|)
GEN_INT_SELFOP_IMPL(^)
#undef GEN_INT_SELFOP_IMPL
#undef IntegerT

//============================implementation of float==================================
#define FloatTypeT Numeric<T,FloatTag>
template<typename T>
Int16 FloatTypeT::Exponent( void )const
{
    typedef FloatLayoutInfo<FloatTypeT> FractionT;

    const static uint16_t MASK = (((1<<15) - 1) / (1 << (15 - FractionT::ExpSize))) << ( 15 - FractionT::ExpSize);
    const static size_t INDEX = WordEndian::IsLittleEndian() ? (sizeof(T) / 2  - 1) : 0;
    int16_t nExponent = ((int16_t*)(&value))[INDEX] & MASK;

    return (nExponent >> (16 - FractionT::ExpSize - 1)) - ((1 << (FractionT::ExpSize - 1)) - 1);
}

template<typename T>
typename FloatLayoutInfo<FloatTypeT>::type FloatTypeT::Fraction( void )const
{
    typedef FloatLayoutInfo<FloatTypeT> FractionT;
    typename FractionT::type nFraction = *((typename FractionT::type*)(&value)) & (int64_t)FractionT::Mask;
    return nFraction;
}

