#ifndef _VIEW_H
#define _VIEW_H
#include "Common/Common.h"
#include "Graphic/PipeLine.h"
#include "Application/MouseEvent.h"
class Object;
typedef Object Shape;

class Render;
class View
    :public MouseEventHandler
{
public:
    View(Render& render);

    void Add2Container(Object* shape); 

public:
    virtual ~View( void );
    virtual void Init( void );
    virtual void BeforeDraw( void );
    virtual void OnDraw( void );
    virtual void AfterDraw( void );


    virtual void OnDeactive( void );
    virtual void OnActive( void );

    enum RenderCompType
    {
	ERootContainer
        ,ECamera
        ,EFrustum
    };

    virtual void Create(RenderCompType e);

    virtual void OnKeyEvent(KeyState ks,int nKeyType,unsigned char key) {}

protected:

    Render& r_render;
    Camera* m_pCamera;
    ObjectList m_vObjectList;
};
#endif

