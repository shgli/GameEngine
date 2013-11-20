#ifndef _CUBETEST_H
#define _CUBETEST_H
#include "Application/View.h"
#include "Graphic/Object.h"
class Triangle;
class TriangleView
    :public View
{
public:
    typedef View Super;
    TriangleView(Render&);

    virtual ~TriangleView( void );
    virtual void Init( void ); 
    virtual void BeforeDraw( void );
    virtual void OnDraw( void );

};
#endif
 
