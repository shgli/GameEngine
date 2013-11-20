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
        :Application(Service::Instance().GetIoService())
        ,m_pView(nullptr)
    {}

    virtual void Init(Int32 nWidth,Int32 nHeight,IDrawStrategy *pDrawStrategy)
    {
        Super::Init(nWidth,nHeight,pDrawStrategy);
        m_pView = new CubeView(*m_pRender);
	m_pView->Init();
	PushView(*m_pView);
    }
};


Application& Application::Instance()
{
    static CubeApplication instance;
    return instance;
}
