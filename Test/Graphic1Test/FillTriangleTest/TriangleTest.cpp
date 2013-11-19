#include "Application/Application.h"
#include "Application/Service.h"
#include "TriangleView.h"
class TriangleApplication
    :public Application
{
    typedef Application Super;
    TriangleView *m_pView;

public:
    TriangleApplication( void )
        :Application(Service::Instance().GetIoService(),400,400)
        ,m_pView(nullptr)
    {}

    virtual void Init( void )
    {
        Super::Init();
        m_pView = new TriangleView(*m_pRender);
	m_pView->Init();
	PushView(*m_pView);
    }
};


Application* Application::CreateInstance()
{
    static TriangleApplication instance;
    return &instance;
}
