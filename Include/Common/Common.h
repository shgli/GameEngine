#ifndef _COMMONTYPE_H
#define _COMMONTYPE_H
#ifdef _DEBUG
#include <iostream>
#endif
#include <initializer_list>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include "Common/Numeric/Numeric.h"
#include "Common/Numeric/Value.h"
#include "Common/Operators/ScaleOp.h"
#include "Common/Operators/TemplateOp.h"
#include "Common/Operators/TypeOp.h"
#include "Common/Utils/Empty.h"
#include "Common/Utils/WordEndian.h"
#include "Common/Utils/Indent.h"
#include "Common/Utils/StatusArray.h"
#include "Common/Numeric/FixNumber.h"

template<typename T>
void Swap(T& a,T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
inline void SwapEx(T& a,T& b,T& tmp)
{
    tmp = a;
    a = b;
    b = tmp;
}
//const
template<typename T>
const T& Const(T& t)
{
    return t;
}

template<typename T>
const T& Const(const T& t)
{
    return t;
}

template<typename T>
const T* Const(T* t)
{
    return t;
}

template<typename T>
const T* Const(const T* t)
{
    return t;
}

template<typename T>
T& NonConst(T& t)
{
    return t;
}

template<typename T>
T* NonConst(T* t)
{
    return t;
}

template<typename T>
T& NonConst(const T& t)
{
    return const_cast<T&>(t);
}

template<typename T>
T* NonConst(const T* t)
{
    return const_cast<T*>(t);
}

#define INVOKE_CONSTFUNC(fun) NonConst(Const(this)->fun)

//--------------- help macros ---------------------
#define if_null(p,macro) \
    if(nullptr == p)\
    {\
	macro; \
    }

#define if_not_null(p,macro) \
    if(nullptr != p)\
    {\
	macro; \
    }

#define if_then(pre,macro) \
    if( pre )\
    {\
	macro;\
    }
#define if_null_create(p,macro) if_null(p,p = macro)
#define foreach BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH
#endif

