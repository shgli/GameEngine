#include "Graphic/Camera.h"
#include "Graphic/PLGLoader.h"
#include "TankView.h"
TankView::TankView(Render& r)
    :View(r)
    ,m_pTank(nullptr)
    ,m_xRot(0.0)
    ,m_yRot(0.0)
    ,m_zRot(0.0)
//    ,m_qFrom(Vec(0.0,1.0,0.0),0.0)
//    ,m_qTo(Vec(0.0,1.0,0.0),1.0)
{
//    std::cout<<"From q: "<<m_qFrom<<std::endl;
//    std::cout<<"To   q: "<<m_qTo<<std::endl;
}

TankView::~TankView( void )
{
    delete m_pTank;
    m_pTank = nullptr;
}

void TankView::Init( void )
{
    Super::Init();
    PLGLoader loader;
    Attributes attris = VA_POSITION;
    m_pTank = loader.Load("tank1.plg",LeftHanded);

    m_pTank->SetWorldPosition(Point(0,0,15));
    m_pTank->SetBaceFaceMode(BFC_BACK);
    m_pTank->SetCullMode(CM_NEVER);

    //设置相机
    m_pCamera->SetEulerCamera(0,200,0.0,0,0,0);
    m_pCamera->SetViewport(0,0,400,400);
    m_pCamera->Frustum(90,1000,PI_DIV_2);
    Add2Container(m_pTank);
}

static double delta = PI / 180;
void TankView::BeforeDraw( void )
{
    (*m_pTank)->LoadIdentity();
    (*m_pTank)->Scale(3.0,3.0,3.0);
    (*m_pTank)->Rotate(m_zRot,Vector(0.0,1.0,0.0));
    (*m_pTank)->Translate(0.0,0.0,400);
    m_pCamera->SetEulerCamera(0,100,0.0,m_xRot,m_yRot,0);

    m_zRot += delta;


    Super::BeforeDraw();
}

void TankView::OnDraw( void )
{
    Super::OnDraw();        
}

void TankView::OnKeyEvent(KeyState ks,int nKeyType,unsigned char key)
{
    switch(nKeyType)
    {
	case LEFT_ARROW:
	    m_xRot += delta;
	    break;
	case RIGHT_ARROW:
	    m_xRot -= delta;
	case UP_ARROW:
	    m_yRot += delta;
	    break;
	case DOWN_ARROW:
	    m_yRot -= delta;
	    break;
    }
}

bool TankView::HandlerMoving(EvtState nState,Int16 x,UInt16 y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy)
{
//    m_nCur += 0.1;
//    if(m_nCur >= 1.0)
//    {
//        m_nCur = 0.1;
//    }
    return true;
}
