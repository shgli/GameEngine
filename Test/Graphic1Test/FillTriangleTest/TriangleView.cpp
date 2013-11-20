#include "Graphic/Camera.h"
#include "Graphic/PLGLoader.h"
#include "TriangleView.h"
#include "Graphic/Render.h"
#include "Graphic/Canvas.h"
TriangleView::TriangleView(Render& r)
    :View(r)
{
}

TriangleView::~TriangleView( void )
{
}

void TriangleView::Init( void )
{
    Super::Init();
}

double zTrans = 100.0;
void TriangleView::BeforeDraw( void )
{
    Super::BeforeDraw();
}

void TriangleView::OnDraw( void )
{
#ifdef _DEBUG
    std::cout<<"Begin----------------------"<<std::endl;
#endif
    //r_render.GetCanvas()->FillTriangle(256,199,229,255,185,199);
    //r_render.GetCanvas()->FillTriangle(256,199,185,199,227,143);
    r_render.GetCanvas()->FillTriangle(177,156,185,199,137,200);
    //r_render.GetCanvas()->FillTriangle(177,156,227,143,185,199);
    //r_render.GetCanvas()->FillTriangle(178,244,185,199,229,255);
    r_render.GetCanvas()->FillTriangle(178,244,137,200,185,199);
#ifdef _DEBUG
    std::cout<<"End------------------------"<<std::endl;
#endif
    Super::OnDraw();        
}

