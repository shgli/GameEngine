#ifndef _HELPFUNCS_HPP
#define _HELPFUNCS_HPP

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

template<typename T>
T Max(T lhs,T rhs)
{
    return lhs < rhs ? rhs : lhs;
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

