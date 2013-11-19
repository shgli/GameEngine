#include "Math/Math.h"
#include "Graphic/Render.h"
#include "Graphic/Canvas.h"
#include "Graphic/Triangle.h"
#include "Graphic/RenderTri.h"
#include "Graphic/PipeLine.h"
Render::Render(Canvas* pCanvas)
    :m_pCanvas(pCanvas)
    ,m_pPipeLine(nullptr)
{}

void Render::Init( void )
{
    m_pPipeLine = new PipeLine(r_pCamera);
    m_pPipeLine->Init();

    m_pTriRender = new RenderTri();
}

void Render::SetCamera(Camera* pCamera)
{
    m_pPipeLine->SetCamera(pCamera);
}

void Render::Draw(ObjectList& objs)
{
    assert(nullptr != m_pPipeLine);
    m_pPipeLine->Reset();
    m_pPipeLine->Do(objs);

    Draw(m_pPipeLine->GetRenderList());
}

#if 1 
void Render::Draw(RenderList& rendList)
{
    m_pCanvas->ClearZBuffer();
    for(auto& rendItem : rendList )
    {
	//m_pTriRender->SetShadingMode(SM_CONST);
        m_pTriRender->SetTexture(rendItem.m_pTexture);
	VertexBuffer* pBuf = rendItem.m_pBuffer;
	for(auto tri : *rendItem.m_vTriangles)
	{
            if(tri->IsVisible())
            {
                Int32 nP0 = tri->GetIndexOfP0();
                Int32 nP1 = tri->GetIndexOfP1();
                Int32 nP2 = tri->GetIndexOfP2();
                m_pTriRender->SetVertices(Vertex(VertexBuffer::SelectBuffer(*pBuf,nP0),Abs(nP0))
                                       ,Vertex(VertexBuffer::SelectBuffer(*pBuf,nP1),Abs(nP1))
                                       ,Vertex(VertexBuffer::SelectBuffer(*pBuf,nP2),Abs(nP2)));
                m_pTriRender->Render(*m_pCanvas);
            }
	}
    }
}
#else
void Render::Draw(RenderList& rendList)
{
    for(auto& rendItem : rendList )
    {
        m_pTriRender->SetTexture(rendItem.m_pTexture);
	VertexBuffer* pBuf = rendItem.m_pBuffer;
	for(auto tri : *rendItem.m_vTriangles)
	{
            if(tri->IsVisible())
            {
                Point &p0 = pBuf->GetPosition(tri->GetIndexOfP0());
                Point &p1 = pBuf->GetPosition(tri->GetIndexOfP1());
                Point &p2 = pBuf->GetPosition(tri->GetIndexOfP2());
		m_pCanvas->SetColor(tri->GetColor());
		//if(tri->IsSolid())
		//{
                //    m_pCanvas->FillTriangle(p0.x,p0.y,p1.x,p1.y,p2.x,p2.y); 
		//}
		//else
		{
       	            m_pCanvas->DrawTriangle(p0.x,p0.y,p1.x,p1.y,p2.x,p2.y); 
		}
            }
	}
    }
}
#endif
//void Render::Draw(const std::vector<TriangleF*>& vTriangles)
//{
//    assert(nullptr != m_pCanvas);
//
//    for(auto tri : vTriangles)
//    {
//        m_pCanvas->SetColor(tri->GetColor());
//
//	if(!tri->IsSolid())
//	{
//	     m_pCanvas->DrawTriangle(tri->GetPosition0().x,tri->GetPosition0().y
//		,tri->GetPosition1().x,tri->GetPosition1().y
//		,tri->GetPosition2().x,tri->GetPosition2().y);
//	}
//	else
//	{
//	     m_pCanvas->FillTriangle(tri->GetPosition0().x,tri->GetPosition0().y
//		,tri->GetPosition1().x,tri->GetPosition1().y
//		,tri->GetPosition2().x,tri->GetPosition2().y);
//	}
//    }
//}

Bitmap* Render::GetDestination( void )
{
    return m_pCanvas->GetDestination();
}
