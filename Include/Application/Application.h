#ifndef _APPLICATION_H
#define _APPLICATION_H
#include <stack>
#include <boost/asio.hpp>
#include "Common/Common.h"
#include "Application/UIFactory.h"
#include "Application/MouseEvent.h"
class View;
class Render;
class Canvas;

class Application
    :public MouseEventStrategy
{
public:
    static Application& Instance( void );
    static Application* CreateInstance( void );

    virtual ~Application();
protected:
    Application(boost::asio::io_service& io,Int32 nWidth,Int32 nHeight);

private:
    Application(const Application&);

public:
    virtual void Init( void );
    virtual void Draw( void );

    Render& GetRender( void ) { return *m_pRender; }

    void OnKeyEvent(KeyState ks,Int32 nKeyType,UInt8 key);

    View& TopView( void );

    void PushView(View& view);
    View& PopView( void );

    Int32 GetWidth( void ) const { return m_width; }
    Int32 GetHeight( void ) const { return m_height; }
protected:
    UIFactory m_oUIFactory;
    Canvas    *m_pCanvas;
    Render *m_pRender;
    Int32 m_width;
    Int32 m_height;

    std::stack<View*> m_views;

    static Application* g_pInstance;
};
#endif
 
