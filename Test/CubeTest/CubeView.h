#ifndef _CUBETEST_H
#define _CUBETEST_H
#include "Application/View.h"
class Cube;
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

    virtual bool HandlerMoving(EvtState nState,Int16 x,UInt y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy);

private:
    Cube* m_pCube;
    Int m_nCur;
    Quater m_qFrom;
    Quater m_qTo;
};
#endif
 
