// GameEngine.cpp : 定义控制台应用程序的入口点。
//

//#include "GL/gl.h"
#include "GL/glut.h"
#include <GL/glu.h>	/* Header File For The GLu Library  */
#include <stdio.h>      /* Header file for standard file i/o.  */
#include <stdlib.h>     /* Header file for malloc/free.  */
#include <math.h>       /* Header file for trigonometric functions.  */
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Graphic/Render.h"
#include "Graphic/Bitmap.h"
#include "Graphic/Canvas.h"
#include "Application/LoopDrawStrategy.h"
#include "Application/Application.h"
#include "Application/MouseEvent.h"
#include "Application/Service.h"
/*
* This Code Was Created By Christopher Aliotta & Jeff Molofee 2000
* A HUGE Thanks To Fredric Echols For Cleaning Up And Optimizing
* The Base Code, Making It More Flexible!  If You've Found This Code
* Useful, Please Let Me Know.  Visit My Site At nehe.gamedev.net
*
* Ported to IRIX/GLUT by Rob Fletcher
* (email me at R.Fletcher@york.ac.uk)
*/

int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 400;
const int WINPOS_X = 100;
const int WINPOS_Y = 100;
static bool IsLeftButtonEvent = true;
static LoopDrawStrategy* pStrage = nullptr;

void PaintThread( void )
{
    while(true)
    {
        glutPostRedisplay();
	
	boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        //xt.sec += 2;
        xt.nsec += 1600;		
        boost::thread::sleep(xt);
    }
}

void Init( void )
{
    //Initialize the gameengine
    //pStrage =  new LoopDrawStrategy(Service::Instance().GetIoService(),50);
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}


void Display( void )
{
    Application::Instance().Draw();
    //glClear(GL_COLOR_BUFFER_BIT);
    //glRasterPos2i(0,0);

    glDrawPixels(SCREEN_WIDTH,SCREEN_HEIGHT
                 ,GL_BGR,GL_UNSIGNED_BYTE
                 ,Application::Instance().GetRender().GetDestination()->GetData());

    //Bitmap bitmap("Crate.bmp");
    //glDrawPixels(GetValue(bitmap.GetWidth()),GetValue(bitmap.GetHeight())
    //             ,GL_BGR,GL_UNSIGNED_BYTE
    //             ,bitmap.GetData());

    glFlush();
}

void Mouse(int button,int state,int x,int y)
{
    switch(button)
    {
	case GLUT_LEFT_BUTTON:
            if(GLUT_UP == state)
            {
	        Application::Instance().OnMouseEvent(LButtonUp,x,y,0);
            }
            else
            {
                IsLeftButtonEvent = true;
                Application::Instance().OnMouseEvent(LButtonDown,x,y,0);
            }
	    break;
	case GLUT_MIDDLE_BUTTON:
	    if(state == GLUT_UP)
	    {
		exit(0);
	    }
	    break;
	case GLUT_RIGHT_BUTTON:
            if(GLUT_UP == state)
            {
	        Application::Instance().OnMouseEvent(RButtonUp,x,y,0);
            }
            else
            {
                IsLeftButtonEvent = false;
                Application::Instance().OnMouseEvent(RButtonDown,x,y,0);
            }
	default:
	    break;
    }
}

void Keyboard(unsigned char key,int x,int y)
{
    Application::Instance().OnKeyEvent(EKS_DOWN,CHAR_KEY,key);
}

void SpeciKey(int key,int x,int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            Application::Instance().OnKeyEvent(EKS_DOWN,LEFT_ARROW,0);
            break;
        case GLUT_KEY_RIGHT:
            Application::Instance().OnKeyEvent(EKS_DOWN,RIGHT_ARROW,0);
            break;
        case GLUT_KEY_UP:
            Application::Instance().OnKeyEvent(EKS_DOWN,UP_ARROW,0);
            break;
        case GLUT_KEY_DOWN:
            Application::Instance().OnKeyEvent(EKS_DOWN,DOWN_ARROW,0);
            break;
        default:
            break;
    }

}

void Motion(int x,int y)
{
    Application::Instance().OnMouseEvent(IsLeftButtonEvent ? LButtonMove : RButtonMove,x,y,0);
}

int main(int argc,char** argv)
{
    Application::Instance().Init();
    SCREEN_WIDTH = Application::Instance().GetWidth();
    SCREEN_HEIGHT = Application::Instance().GetHeight();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(WINPOS_X,WINPOS_Y);
    glutCreateWindow("shgli");
    
    Init();

    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpeciKey);

    boost::thread drawThread(PaintThread);
    Service::Instance().Run();
    glutMainLoop();
    return 0;
}

