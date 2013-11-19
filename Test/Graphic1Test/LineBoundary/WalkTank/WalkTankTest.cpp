#include "Application/Application.h"
#include "Application/Service.h"
#include "WalkTankView.h"
class WalkTankApplication
    :public Application
{
    typedef Application Super;
    WalkTankView *m_pView;

public:
    WalkTankApplication( void )
        :Application(Service::Instance().GetIoService(),800,600)
        ,m_pView(nullptr)
    {}

    virtual void Init()
    {
        Super::Init();
        m_pView = new WalkTankView(*m_pRender);
	m_pView->Init();
	PushView(*m_pView);
    }
};


Application* Application::CreateInstance()
{
    static WalkTankApplication instance;
    return &instance;
}
