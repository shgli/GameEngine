#include "Graphic/Camera.h"
#include "Graphic/PLGLoader.h"
#include "CubeView.h"
CubeView::CubeView(Render& r)
    :View(r)
    ,m_pTriangle(nullptr)
    ,m_yRot(0.0)
//    ,m_qFrom(Vec(0.0,1.0,0.0),0.0)
//    ,m_qTo(Vec(0.0,1.0,0.0),1.0)
{
//    std::cout<<"From q: "<<m_qFrom<<std::endl;
//    std::cout<<"To   q: "<<m_qTo<<std::endl;
}

CubeView::~CubeView( void )
{
    delete m_pTriangle;
    m_pTriangle = nullptr;
}

void CubeView::Init( void )
{
    Super::Init();
    PLGLoader loader;
    Attributes attris = VA_POSITION;
    m_pTriangle = loader.Load("cube1.plg",LeftHanded);

    //m_pTriangle->SetWorldPosition(Point(0,0,15));
    m_pTriangle->SetBaceFaceMode(BFC_NEVER);
    m_pTriangle->SetCullMode(CM_NEVER);

    //设置相机
    m_pCamera->SetEulerCamera(0,0,-100,0,0,0);
    m_pCamera->SetViewport(0,0,400,400);
    m_pCamera->Frustum(10,500,PI_DIV_2);
    Add2Container(m_pTriangle);
}

void CubeView::BeforeDraw( void )
{
//    m_yRot = PI;
    (*m_pTriangle)->LoadIdentity();
    (*m_pTriangle)->Scale(3.5,3.5,3.5);
    (*m_pTriangle)->Rotate(m_yRot,Vector(0,1,0));
    //(*m_pTriangle)->Rotate(0.0,m_yRot,0.0);
    m_yRot += PI / 90;
    
    if(m_yRot > PI2)
    {
	m_yRot = 0.0;
    }

    Super::BeforeDraw();
}

void CubeView::OnDraw( void )
{
    Super::OnDraw();        
}

bool CubeView::HandlerMoving(EvtState nState,Int16 x,UInt16 y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy)
{
//    m_nCur += 0.1;
//    if(m_nCur >= 1.0)
//    {
//        m_nCur = 0.1;
//    }
    return true;
}
