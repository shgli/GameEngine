#ifndef _CUBETEST_H
#define _CUBETEST_H
#include "Application/View.h"
#include "Graphic/Object.h"
class Triangle;
class CubeView
    :public View
{
public:
    typedef View Super;
    CubeView(Render&);

    virtual ~CubeView( void );
    virtual void Init( void ); 
    virtual void BeforeDraw( void );
    virtual void OnDraw( void );

    virtual bool HandlerMoving(EvtState nState,Int16 x,UInt16 y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy);

private:
    Object* m_pTriangle;
    Real  m_yRot;
//    Quater m_qFrom;
//    Quater m_qTo;
};
#endif
 
