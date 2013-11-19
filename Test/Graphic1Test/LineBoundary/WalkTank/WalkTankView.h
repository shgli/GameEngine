#ifndef _CUBETEST_H
#define _CUBETEST_H
#include "Application/View.h"
#include "Graphic/Object.h"
class Triangle;
class WalkTankView
    :public View
{
public:
    typedef View Super;
    WalkTankView(Render&);

    virtual ~WalkTankView( void );
    virtual void Init( void ); 
    virtual void BeforeDraw( void );
    virtual void OnDraw( void );

    virtual bool HandlerMoving(EvtState nState,Int16 x,UInt16 y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy);
    virtual void OnKeyEvent(KeyState ks,int nKeyType,unsigned char key);

private:
    Object* m_pWalkTank;
    Object* m_pPlayer;
    Object* m_pTower;
    Object* m_pMarker;

    static const int UNIVERSE_RADIUS;
    static const int POINT_SIZE;
    static const int NUM_POINTS_X; 
    static const int NUM_POINTS_Z;
    static const int NUM_POINTS;

    static const int NUM_TOWERS;
    static const int NUM_TANKS;
    static const int TANK_SPEED;

    Point m_posCamera;
    EulerAngle m_angleCamera;
    Real  m_xRot;
    Real  m_yRot;
    Real  m_zRot;
//    Quater m_qFrom;
//    Quater m_qTo;
};
#endif
 
