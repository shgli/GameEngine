#include "Graphic/Camera.h"
#include "Graphic/PLGLoader.h"
#include "Graphic/Render.h"
#include "Graphic/Canvas.h"
#include "WalkTankView.h"
#include "Application/Application.h"
static double delta = PI / 180;
static double turning = 0.0;
static double tank_speed = 5.0;
const int WalkTankView::UNIVERSE_RADIUS = 1000;
const int WalkTankView::POINT_SIZE = 200;
const int WalkTankView::NUM_POINTS_X = (2 * UNIVERSE_RADIUS / POINT_SIZE);
const int WalkTankView::NUM_POINTS_Z =  (2 * UNIVERSE_RADIUS / POINT_SIZE);
const int WalkTankView::NUM_POINTS = (NUM_POINTS_X * NUM_POINTS_Z);

const int WalkTankView::NUM_TOWERS = 15;
const int WalkTankView::NUM_TANKS = 15;
const int WalkTankView::TANK_SPEED = 5;

WalkTankView::WalkTankView(Render& r)
    :View(r)
    ,m_pWalkTank(nullptr)
    ,m_pTower(nullptr)
    ,m_pPlayer(nullptr)
    ,m_pMarker(nullptr)
    ,m_xRot(0.0)
    ,m_yRot(0.0)
    ,m_zRot(0.0)
    ,m_posCamera(0,0,-100)
//    ,m_qFrom(Vec(0.0,1.0,0.0),0.0)
//    ,m_qTo(Vec(0.0,1.0,0.0),1.0)
{
//    std::cout<<"From q: "<<m_qFrom<<std::endl;
//    std::cout<<"To   q: "<<m_qTo<<std::endl;
}

WalkTankView::~WalkTankView( void )
{
    delete m_pWalkTank;
    m_pWalkTank = nullptr;
}

void WalkTankView::Init( void )
{
    Super::Init();
    PLGLoader loader;
    Attributes attris = VA_POSITION;

    //WalkTank
    m_pWalkTank = loader.Load("tank2.plg",LeftHanded);

    m_pWalkTank->SetBaceFaceMode(BFC_BACK);
    m_pWalkTank->SetCullMode(CM_NEVER);
    std::srand(time(0));
    for(int index = 0; index < NUM_TANKS; ++index)
    {
        Object *pTank = m_pWalkTank->Clone();
        Real x = RandRange(-UNIVERSE_RADIUS,UNIVERSE_RADIUS);
	Real y = 0;
	Real z = RandRange(-UNIVERSE_RADIUS,UNIVERSE_RADIUS);

	Real rot = RandRange(0,300);
	pTank->SetWorldPosition(x,y,z);
        //pTank->SetCullMode(CM_NEVER);
	(*pTank)->Rotate(0.0,rot * delta,0);
	Add2Container(pTank);
    }

    //Player
    m_pPlayer = loader.Load("tank3.plg",LeftHanded);
    m_pPlayer->SetName("player");
    m_pPlayer->SetWorldPosition(Point(0,0,15));
    m_pPlayer->SetBaceFaceMode(BFC_BACK);
    m_pPlayer->SetCullMode(CM_NEVER);
    Add2Container(m_pPlayer);

    //Tower
    m_pTower = loader.Load("tower1.plg",LeftHanded);
    m_pTower->SetWorldPosition(Point(0,0,15));
    m_pTower->SetBaceFaceMode(BFC_BACK);
    m_pTower->SetCullMode(CM_NEVER);
    //Add2Container(m_pTower);
    for(int index = 0; index < NUM_TOWERS; ++index)
    {
	Object *pTower = m_pTower->Clone();
        Real x = RandRange(-UNIVERSE_RADIUS,UNIVERSE_RADIUS);
	Real y = 0;
	Real z = RandRange(-UNIVERSE_RADIUS,UNIVERSE_RADIUS);

#ifdef _DEBUG
	std::cout<<"tower: ("<<x<<","<<y<<","<<z<<")"<<std::endl;
#endif
	pTower->SetWorldPosition(x,y,z);
//	pTower->SetCullMode(CM_NEVER);
	pTower->SetBaceFaceMode(BFC_NEVER);

	boost::format nameFmt("tower %d");
	nameFmt % index;
	pTower->SetName(nameFmt.str());
	Add2Container(pTower);
    }

    //Marker
    m_pMarker = loader.Load("marker1.plg",LeftHanded);
    m_pMarker->SetWorldPosition(Point(0,0,15));
    m_pMarker->SetBaceFaceMode(BFC_BACK);
 //   m_pMarker->SetCullMode(CM_NEVER);

    for(int index_x = 0; index_x < NUM_POINTS_X; ++index_x)
    {
        for(int index_z = 0; index_z < NUM_POINTS_Z; ++index_z)
	{
	    Real x = RandRange(-100,100) - UNIVERSE_RADIUS + index_x * POINT_SIZE;
	    Real y = m_pMarker->GetBound().radius;
	    Real z =  RandRange(-100,100) - UNIVERSE_RADIUS + index_z * POINT_SIZE;
            
	    Object *pMarker = m_pMarker->Clone();
            //pMarker->SetCullMode(CM_NEVER);
	    (*pMarker)->Translate(x,y,z);
	    Add2Container(pMarker);
	}
    }


    //设置相机
    m_pCamera->SetViewport(0,0,Application::Instance().GetWidth(),Application::Instance().GetHeight());
    m_pCamera->Frustum(90,10000,PI_DIV_2);
}

void WalkTankView::BeforeDraw( void )
{
#ifdef _DEBUG
//    std::cout<<__FUNCTION__<<std::endl;
    std::cout<<m_posCamera<<std::endl;
#endif
    Super::BeforeDraw();
    Real xPlayer = m_posCamera.x + 300 * Sin(m_angleCamera.y);
    Real yPlayer = m_posCamera.y - 70;
    Real zPlayer = m_posCamera.z + 300 * Cos(m_angleCamera.y);

    (*m_pPlayer)->Translate(xPlayer,yPlayer,zPlayer);
    //(*m_pPlayer)->Rotate(0,m_angleCamera.y + turning,0);

    m_pCamera->SetEulerCamera(m_posCamera,m_angleCamera);

    m_zRot += delta;

}

void WalkTankView::OnDraw( void )
{
    int nWidth = m_pCamera->GetScreenWidth();
    int nHeight = m_pCamera->GetScreenHeight();
    r_render.GetCanvas()->SetColor(Color(30,120,192));
    r_render.GetCanvas()->FillRect(0,0,nWidth,nHeight / 2);
    r_render.GetCanvas()->SetColor(Color(103,62,63));
    r_render.GetCanvas()->FillRect(0,nHeight / 2,nWidth,nHeight);
    Super::OnDraw();        
}

void WalkTankView::OnKeyEvent(KeyState ks,int nKeyType,unsigned char key)
{
    switch(nKeyType)
    {
	case LEFT_ARROW:
	    m_angleCamera.y -= 3 * delta;

	    if((turning -= 2) < -15)
	    {
		turning = -15;
	    }
	    break;
	case RIGHT_ARROW:
	    m_angleCamera.y += 3 * delta;

	    if((turning += 2) > 15)
	    {
		turning = 15;
	    }
	    break;
	case UP_ARROW:
	    //m_posCamera.x += tank_speed * Sin(m_angleCamera.y);
	    m_posCamera.z += tank_speed * Cos(m_angleCamera.y);
	    break;
	case DOWN_ARROW:
	    //m_posCamera.x -= tank_speed * Sin(m_angleCamera.y);
	    m_posCamera.z -= tank_speed * Cos(m_angleCamera.y);
	    break;
    }
}

bool WalkTankView::HandlerMoving(EvtState nState,Int16 x,UInt16 y,Int16 nDx,Int16 nDy,Int16 nTotalDx,Int16 nTotalDy)
{
//    m_nCur += 0.1;
//    if(m_nCur >= 1.0)
//    {
//        m_nCur = 0.1;
//    }
    return true;
}
