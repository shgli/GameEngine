#include <iostream>
#include <stdexcept>
#include "Graphic/Camera.h"
#include "Graphic/Render.h"
#include "Graphic/Canvas.h"
#include "Graphic/Bitmap.h"
#include "Application/Application.h"
#include "Application/View.h"
Application* Application::g_pInstance = nullptr;
Application::Application(boost::asio::io_service& io,Int32 nWidth,Int32 nHeight)
    :MouseEventStrategy(io)
    ,m_oUIFactory()
    ,m_pCanvas(nullptr)
    ,m_pRender(nullptr)
    ,m_width(nWidth)
    ,m_height(nHeight)
{}

Application::~Application()
{
    delete m_pCanvas;
}

void Application::Init( void )
{
    if_null_create(m_pCanvas,new Canvas(new Bitmap(m_width,m_height)));
    if_null_create(m_pRender,new Render(m_pCanvas));
    m_pRender->Init();
    m_oUIFactory.SetRender(m_pRender);
}

View& Application::TopView( void )
{
    View* pTopView = m_views.top();
    if(nullptr == pTopView)
    {
	throw std::logic_error("there is 0 view!");
    }

    return *pTopView;
}

void Application::PushView(View& view)
{
    SetEventHandler(&view);
    view.OnActive();
    m_views.push(&view);
}

View& Application::PopView( void )
{
    View* pTopView = m_views.top();
    if(nullptr == pTopView)
    {
	throw std::logic_error("there is 0 view!");
    }


    m_views.pop();
    SetEventHandler(&TopView());
    pTopView->OnDeactive();
    return *pTopView;
}

void Application::Draw( void )
{
    try
    {
#ifdef _DEBUG
	static int nLoop = 1;
	std::cout<<"Start Draw Loop : "<<nLoop<<std::endl;
#endif
        m_pCanvas->Clear(Color::Black); 
	View& view = TopView();
	view.BeforeDraw();
	view.OnDraw();
	view.AfterDraw();

#ifdef _DEBUG
	std::cout<<"End Draw Loop : "<<nLoop<<std::endl;
	++nLoop;
#endif
    }
    catch(std::exception& ex)
    {
	std::cout<<ex.what()<<std::endl;
    }
}

void Application::OnKeyEvent(KeyState ks,Int32 nKeyType,UInt8 key)
{
    View& view = TopView();
    view.OnKeyEvent(ks,nKeyType,key);
}

Application& Application::Instance( void )
{
    if(nullptr == g_pInstance)
    {
	g_pInstance = CreateInstance();
    }

    return *g_pInstance;
}
