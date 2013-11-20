#ifndef BOOST_PP_IS_ITERATING 

#ifndef _UIFACTORY_H
#define _UIFACTORY_H

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define MAX_PARAMS 4

class Render;
class UIFactory
{
public:
    UIFactory( void ):
	m_pRender(nullptr)
    {}

#define BOOST_PP_ITERATION_LIMITS (0,MAX_PARAMS)
#define BOOST_PP_FILENAME_1 "Application/UIFactory.h"
#include BOOST_PP_ITERATE()

    void SetRender(Render* pRender) {m_pRender = pRender;}
private:
    Render *m_pRender;
};

#endif
#else

#define TYPE_VALUE(z,n,data) BOOST_PP_COMMA_IF(n) T##n v##n
#define n BOOST_PP_ITERATION()
    template<typename T BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)>
    T* Create(BOOST_PP_REPEAT(n,TYPE_VALUE,v))
    {
	T* pObj = new T(*m_pRender BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,v));
	if(nullptr != pObj)
	{
	    pObj->Init();
	}

	return pObj;
    }
#undef TYPE_VALUE
#undef n
#endif
 
