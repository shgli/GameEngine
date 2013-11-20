#ifndef _CINTTYPES_H_
#define _CINTTYPES_H_
#include <boost/cstdint.hpp>

using boost::uint8_t ;
using boost::uint16_t;
using boost::uint32_t;
using boost::uint64_t;
using boost::int8_t;
using boost::int16_t;
using boost::int32_t;
using boost::int64_t;

static const int32_t MAX_INT = 1 << 30;
static const double MAX_REAL = 100000.0;
const double EPSILON = 1.192092896e-06;

typedef int8_t  Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;

typedef uint8_t UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;

typedef double  Double;
typedef float   Float;

typedef Int32 Int;
typedef Double Real;
#ifdef WIN32
#define  DLLEXPORT __declspec(dllexport)
#else
#define  DLLEXPORT 
#endif
#endif

