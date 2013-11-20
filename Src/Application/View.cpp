#include <cassert>
#include "Common/Common.h"
#include "Graphic/Object.h"
#include "Graphic/Render.h"
#include "Graphic/Camera.h"
#include "Graphic/BackFaceCuller.h"
#include "Application/View.h"
View::View(Render& render)
    :r_render(render)
    ,m_pCamera(nullptr)
{}

View::~View()
{
    delete m_pCamera;
    m_pCamera = nullptr;
}

void View::Init( void )
{
    Create(ECamera);
    r_render.SetCamera(m_pCamera);
}

void View::BeforeDraw( void )
{
    for(auto obj : m_vObjectList)
    {
	(*obj)->LoadIdentity();
    }
}

void View::OnDraw( void )
{
    r_render.Draw(m_vObjectList);
}

void View::AfterDraw( void )
{
}

void View::OnDeactive( void )
{
}

void View::OnActive( void )
{
}


void View::Create(RenderCompType eType)
{
    switch(eType)
    {
	case ECamera:
	    m_pCamera = new Camera(0,0);
	    break;
	default:
	    break;
    }
}

void View::Add2Container(Shape* shape)
{ 
    m_vObjectList.push_back(shape);
}

