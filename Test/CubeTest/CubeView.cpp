#include "Graphic/View/Frustum.h"
#include "Graphic/View/Camera.h"
#include "Application/Cube.h"
#include "CubeView.h"
CubeView::CubeView(Render& r)
    :View(r)
    ,m_pCube(nullptr)
    ,m_nCur(0)
    ,m_qFrom(Vec(0.0,1.0,0.0),0.0)
    ,m_qTo(Vec(0.0,1.0,0.0),1.0)
{
    std::cout<<"From q: "<<m_qFrom<<std::endl;
    std::cout<<"To   q: "<<m_qTo<<std::endl;
}

CubeView::~CubeView( void )
{
    delete m_pCube;
    m_pCube = nullptr;
}

void CubeView::Init( void )
{
    Super::Init();
    m_pCube = new Cube();
    Add2Container(*m_pCube);
}

void CubeView::BeforeDraw( void )
{
    m_pCamera->SetPosition(Position(0,0,1));
    Super::BeforeDraw();
}

static int ii = 0;
void CubeView::OnDraw( void )
{
    Rotate(Quater::Slerp(m_qFrom,m_qTo,m_nCur));
    Translate(Vec(0,0,-2));
    Super::OnDraw();        
}

bool CubeView::HandlerMoving(EvtState nState,Int16 x,UInt y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy)
{
    m_nCur += 0.1;
    if(m_nCur >= 1.0)
    {
        m_nCur = 0.1;
    }
    return true;
}
