#ifndef _PROMOTIONS_HPP
#define _PROMOTIONS_HPP
#include <boost/cstdint.hpp>
#include "Promotion.h"
template<typename T,typename Tag>
struct Numeric;

struct NumericBaseTag;
struct IntTag;
struct FloatTag;

//#define GEN_INTEGER_TYPE(name,T) typedef Numeric<T,IntTag> name; 
#define GEN_INTEGER_TYPE(name,T) typedef T  name; 

GEN_INTEGER_TYPE(UInt8,uint8_t)
GEN_INTEGER_TYPE(UInt16,uint16_t)
GEN_INTEGER_TYPE(UInt32,uint32_t)
GEN_INTEGER_TYPE(UInt64,uint64_t)

GEN_INTEGER_TYPE(Int8,int8_t)
GEN_INTEGER_TYPE(Int16,int16_t)
GEN_INTEGER_TYPE(Int32,int32_t)
GEN_INTEGER_TYPE(Int64,int64_t)
GEN_INTEGER_TYPE(Int,int32_t)

//typedef Numeric<float,FloatTag> Float;
//typedef Numeric<double,FloatTag> Double;
typedef float Float;
typedef double Double;
typedef Double Real;


MK_PROMOTION(uint8_t,int8_t,int8_t)
MK_PROMOTION(uint32_t,int32_t,int32_t)
MK_PROMOTION(uint64_t,int64_t,int64_t)
MK_PROMOTION(int32_t,float,float)
MK_PROMOTION(uint32_t,float,float)
MK_PROMOTION(int64_t,double,double)
MK_PROMOTION(uint64_t,double,double)

//for UInt8
//MK_PROMOTION(uint8_t,UInt8,UInt8)
//MK_PROMOTION(uint16_t,UInt8,UInt16)
//MK_PROMOTION(uint32_t,UInt8,UInt32)
//MK_PROMOTION(uint64_t,UInt8,UInt64)
//MK_PROMOTION(int8_t,UInt8,UInt8)
//MK_PROMOTION(int16_t,UInt8,Int16)
//MK_PROMOTION(int32_t,UInt8,Int32)
//MK_PROMOTION(int64_t,UInt8,Int64)
//MK_PROMOTION(float,UInt8,Float)
//MK_PROMOTION(double,UInt8,Double)
//
////for Int8
//MK_PROMOTION(uint8_t,Int8,Int8)
//MK_PROMOTION(uint16_t,Int8,UInt16)
//MK_PROMOTION(uint32_t,Int8,UInt32)
//MK_PROMOTION(uint64_t,Int8,UInt64)
//MK_PROMOTION(int8_t,Int8,Int8)
//MK_PROMOTION(int16_t,Int8,Int16)
//MK_PROMOTION(int32_t,Int8,Int32)
//MK_PROMOTION(int64_t,Int8,Int64)
//MK_PROMOTION(float,Int8,Float)
//MK_PROMOTION(double,Int8,Double)
//MK_PROMOTION(UInt8,Int8,UInt8)
//
////for UInt16
//MK_PROMOTION(uint8_t,UInt16,UInt16)
//MK_PROMOTION(uint16_t,UInt16,UInt16)
//MK_PROMOTION(uint32_t,UInt16,UInt32)
//MK_PROMOTION(uint64_t,UInt16,UInt64)
//MK_PROMOTION(int8_t,UInt16,UInt16)
//MK_PROMOTION(int16_t,UInt16,UInt16)
//MK_PROMOTION(int32_t,UInt16,Int32)
//MK_PROMOTION(int64_t,UInt16,Int64)
//MK_PROMOTION(float,UInt16,Float)
//MK_PROMOTION(double,UInt16,Double)
//MK_PROMOTION(UInt8,UInt16,UInt16)
//MK_PROMOTION(Int8,UInt16,UInt16)
//
////for Int16
//MK_PROMOTION(uint8_t,Int16,Int16)
//MK_PROMOTION(uint16_t,Int16,Int16)
//MK_PROMOTION(uint32_t,Int16,UInt32)
//MK_PROMOTION(uint64_t,Int16,UInt64)
//MK_PROMOTION(int8_t,Int16,Int16)
//MK_PROMOTION(int16_t,Int16,Int16)
//MK_PROMOTION(int32_t,Int16,Int32)
//MK_PROMOTION(int64_t,Int16,Int64)
//MK_PROMOTION(float,Int16,Float)
//MK_PROMOTION(double,Int16,Double)
//MK_PROMOTION(UInt8,Int16,Int16)
//MK_PROMOTION(UInt16,Int16,UInt16)
//MK_PROMOTION(Int8,Int16,Int16)
//
////for UInt32
//MK_PROMOTION(uint8_t,UInt32,UInt32)
//MK_PROMOTION(uint16_t,UInt32,UInt32)
//MK_PROMOTION(uint32_t,UInt32,UInt32)
//MK_PROMOTION(uint64_t,UInt32,UInt64)
//MK_PROMOTION(int8_t,UInt32,UInt32)
//MK_PROMOTION(int16_t,UInt32,UInt32)
//MK_PROMOTION(int32_t,UInt32,UInt32)
//MK_PROMOTION(int64_t,UInt32,Int64)
//MK_PROMOTION(float,UInt32,Float)
//MK_PROMOTION(double,UInt32,Double)
//MK_PROMOTION(UInt8,UInt32,UInt32)
//MK_PROMOTION(UInt16,UInt32,UInt32)
//MK_PROMOTION(Int8,UInt32,UInt32)
//MK_PROMOTION(Int16,UInt32,UInt32)
//
////for Int32
//MK_PROMOTION(uint8_t,Int32,Int32)
//MK_PROMOTION(uint16_t,Int32,Int32)
//MK_PROMOTION(uint32_t,Int32,Int32)
//MK_PROMOTION(uint64_t,Int32,UInt64)
//MK_PROMOTION(int8_t,Int32,Int32)
//MK_PROMOTION(int16_t,Int32,Int32)
//MK_PROMOTION(int32_t,Int32,Int32)
//MK_PROMOTION(int64_t,Int32,Int64)
//MK_PROMOTION(float,Int32,Float)
//MK_PROMOTION(double,Int32,Double)
//MK_PROMOTION(UInt8,Int32,Int32)
//MK_PROMOTION(UInt16,Int32,UInt32)
//MK_PROMOTION(UInt32,Int32,Int32)
//MK_PROMOTION(Int8,Int32,Int32)
//MK_PROMOTION(Int16,Int32,Int32)
//
////for UInt64
//MK_PROMOTION(uint8_t,UInt64,UInt64)
//MK_PROMOTION(uint16_t,UInt64,UInt64)
//MK_PROMOTION(uint32_t,UInt64,UInt64)
//MK_PROMOTION(uint64_t,UInt64,UInt64)
//MK_PROMOTION(int8_t,UInt64,UInt64)
//MK_PROMOTION(int16_t,UInt64,UInt64)
//MK_PROMOTION(int32_t,UInt64,UInt64)
//MK_PROMOTION(int64_t,UInt64,UInt64)
//MK_PROMOTION(float,UInt64,Double)
//MK_PROMOTION(double,UInt64,Double)
//MK_PROMOTION(UInt8,UInt64,UInt64)
//MK_PROMOTION(UInt16,UInt64,UInt64)
//MK_PROMOTION(UInt32,UInt64,UInt64)
//MK_PROMOTION(Int8,UInt64,UInt64)
//MK_PROMOTION(Int16,UInt64,UInt64)
//MK_PROMOTION(Int32,UInt64,UInt64)
//
////for Int64
//MK_PROMOTION(uint8_t,Int64,Int64)
//MK_PROMOTION(uint16_t,Int64,Int64)
//MK_PROMOTION(uint32_t,Int64,Int64)
//MK_PROMOTION(uint64_t,Int64,Int64)
//MK_PROMOTION(int8_t,Int64,Int64)
//MK_PROMOTION(int16_t,Int64,Int64)
//MK_PROMOTION(int32_t,Int64,Int64)
//MK_PROMOTION(int64_t,Int64,Int64)
//MK_PROMOTION(float,Int64,Double)
//MK_PROMOTION(double,Int64,double)
//MK_PROMOTION(UInt8,Int64,Int64)
//MK_PROMOTION(UInt16,Int64,Int64)
//MK_PROMOTION(UInt32,Int64,Int64)
//MK_PROMOTION(UInt64,Int64,UInt64)
//MK_PROMOTION(Int8,Int64,Int64)
//MK_PROMOTION(Int16,Int64,Int64)
//MK_PROMOTION(Int32,Int64,Int64)
//
////for Float
//MK_PROMOTION(uint8_t,Float,Float)
//MK_PROMOTION(uint16_t,Float,Float)
//MK_PROMOTION(uint32_t,Float,Float)
//MK_PROMOTION(uint64_t,Float,Float)
//MK_PROMOTION(int8_t,Float,Float)
//MK_PROMOTION(int16_t,Float,Float)
//MK_PROMOTION(int32_t,Float,Float)
//MK_PROMOTION(int64_t,Float,Float)
//MK_PROMOTION(float,Float,Float)
//MK_PROMOTION(double,Float,Double)
//MK_PROMOTION(UInt8,Float,Float)
//MK_PROMOTION(UInt16,Float,Float)
//MK_PROMOTION(UInt32,Float,Float)
//MK_PROMOTION(UInt64,Float,Float)
//MK_PROMOTION(Int8,Float,Float)
//MK_PROMOTION(Int16,Float,Float)
//MK_PROMOTION(Int32,Float,Float)
//MK_PROMOTION(Int64,Float,Float)
//
////for Double 
//MK_PROMOTION(uint8_t,Double,Double)
//MK_PROMOTION(uint16_t,Double,Double)
//MK_PROMOTION(uint32_t,Double,Double)
//MK_PROMOTION(uint64_t,Double,Double)
//MK_PROMOTION(int8_t,Double,Double)
//MK_PROMOTION(int16_t,Double,Double)
//MK_PROMOTION(int32_t,Double,Double)
//MK_PROMOTION(int64_t,Double,Double)
//MK_PROMOTION(float,Double,Float)
//MK_PROMOTION(double,Double,Double)
//MK_PROMOTION(UInt8,Double,Double)
//MK_PROMOTION(UInt16,Double,Double)
//MK_PROMOTION(UInt32,Double,Double)
//MK_PROMOTION(UInt64,Double,Double)
//MK_PROMOTION(Int8,Double,Double)
//MK_PROMOTION(Int16,Double,Double)
//MK_PROMOTION(Int32,Double,Double)
//MK_PROMOTION(Int64,Double,Double)
//MK_PROMOTION(Float,Double,Float)

#endif

