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

#ifdef WIN32
#define  DLLEXPORT __declspec(dllexport)
#else
#define  DLLEXPORT 
#endif
#endif

