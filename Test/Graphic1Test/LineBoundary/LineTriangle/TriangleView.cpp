#include "Graphic/Camera.h"
#include "Graphic/PLGLoader.h"
#include "Graphic/Triangle.h"
#include "TriangleView.h"
TriangleView::TriangleView(Render& r)
    :View(r)
    ,m_pTriangle(nullptr)
    ,m_yRot(0.0)
//    ,m_qFrom(Vec(0.0,1.0,0.0),0.0)
//    ,m_qTo(Vec(0.0,1.0,0.0),1.0)
{
//    std::cout<<"From q: "<<m_qFrom<<std::endl;
//    std::cout<<"To   q: "<<m_qTo<<std::endl;
}

TriangleView::~TriangleView( void )
{
    delete m_pTriangle;
    m_pTriangle = nullptr;
}

void TriangleView::Init( void )
{
    Super::Init();
    Attributes attris = VA_POSITION|VA_COLOR;
    VertexBuffer* pBuf = new VertexBuffer(attris,3);
    *pBuf = {{0,50,0,255.0,255.0,0.0}
            ,{-50,-50,0,255.0,255.0,0.0}
            ,{50,-50,0,255.0,255.0,0.0}};
    ObjectModel *pModel = new ObjectModel(pBuf);
    pModel->AddTriangle(new Triangle(0,1,2));
    m_pTriangle =  new Object("Triangle",ObjectModelPtr(pModel));
    m_pTriangle->SetCullMode(CM_NEVER);
    m_pTriangle->SetBaceFaceMode(BFC_NEVER);
   // m_pTriangle->SetBaceFaceMode(BFC_BACK);

    //设置相机
    m_pCamera->SetEulerCamera(0,0,50,0,0,0);
    m_pCamera->SetViewport(0,0,400,400);
    m_pCamera->Frustum(50,500,PI_DIV_2);
    Add2Container(m_pTriangle);
}

double zTrans = 0.0;
void TriangleView::BeforeDraw( void )
{
//    m_yRot = PI_DIV_4;
    Super::BeforeDraw();
    (*m_pTriangle)->LoadIdentity();
    //(*m_pTriangle)->Scale(0.5,0.5,0.5);
    //(*m_pTriangle)->Rotate(m_yRot,Vector(0,1,0));
    (*m_pTriangle)->Rotate(0,m_yRot,0);
    (*m_pTriangle)->Translate(0,0,zTrans);
    
    if(m_yRot > PI2)
    {
	m_yRot = 0.0;
    }

}

void TriangleView::OnDraw( void )
{
    Super::OnDraw();        
}

void TriangleView::OnKeyEvent(KeyState ks,int nKeyType,unsigned char key)
{
    switch(nKeyType)
    {
	case LEFT_ARROW:
            m_yRot += PI / 180;
	    break;
	case RIGHT_ARROW:
            m_yRot -= PI / 180;
	    break;
	case UP_ARROW:
	    //m_posCamera.x += tank_speed * Sin(m_angleCamera.y);
            zTrans += 5;
	    break;
	case DOWN_ARROW:
	    //m_posCamera.x -= tank_speed * Sin(m_angleCamera.y);
            zTrans -= 5;
	    break;
    }
}
bool TriangleView::HandlerMoving(EvtState nState,Int16 x,UInt16 y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy)
{
//    m_nCur += 0.1;
//    if(m_nCur >= 1.0)
//    {
//        m_nCur = 0.1;
//    }
    return true;
}
