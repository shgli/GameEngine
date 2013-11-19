#include "Application/Application.h"
#include "Application/Service.h"
#include "CubeView.h"
class CubeApplication
    :public Application
{
    typedef Application Super;
    CubeView *m_pView;

public:
    CubeApplication( void )
        :Application(Service::Instance().GetIoService(),400,400)
        ,m_pView(nullptr)
    {}

    virtual void Init( void )
    {
        Super::Init();
        m_pView = new CubeView(*m_pRender);
	m_pView->Init();
	PushView(*m_pView);
    }
};


Application* Application::CreateInstance()
{
    static CubeApplication instance;
    return &instance;
}
