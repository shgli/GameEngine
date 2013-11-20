#include "Application/Application.h"
#include "Application/Service.h"
#include "TankView.h"
class TankApplication
    :public Application
{
    typedef Application Super;
    TankView *m_pView;

public:
    TankApplication( void )
        :Application(Service::Instance().GetIoService(),400,400)
        ,m_pView(nullptr)
    {}

    virtual void Init()
    {
        Super::Init();
        m_pView = new TankView(*m_pRender);
	m_pView->Init();
	PushView(*m_pView);
    }
};


Application* Application::CreateInstance()
{
    static TankApplication instance;
    return &instance;
}
