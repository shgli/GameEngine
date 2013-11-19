#include "Graphic/LightPass.h"
#include "Graphic/Object.h"
#include "Graphic/GraphicTypes.h"
#include "Graphic/LightMgr.h"
#include "Graphic/Triangle.h"

void LightPass::Visit(Object& obj)
{
    if(!obj.IsVisible() || !obj.NeedShading())
    {
	return ;
    }

    VertexBuffer& buf = obj.GetVertexBuffer();
#define SelectBuffer(idx) (idx > 0 ? buf : VertexBuffer::GetGlobalBuffer())
#define AdjustP(idx) (idx > 0 ? idx : -idx)
    if(SM_FLAT == obj.GetShadingMode())
    {
	for(auto tri : obj.GetTriangles())
	{
	    if(!tri->IsVisible())
	    {
		continue;
	    }

	    Int32 nIdx = tri->GetIndexOfP0();
	    LightMgr::Instance().Shading(Vertex(SelectBuffer(nIdx),AdjustP(nIdx)),tri->GetColor());
	}
    }
    else
    {
	static StatusArray AlreadShading(MAX_VERTEX_PEROBJECT,MAX_VERTEX_PEROBJECT / 4);
	AlreadShading.Reset();
	for(auto tri : obj.GetTriangles())
	{
	    if(!tri->IsVisible())
	    {
		continue;
	    }

	    Int32 nP0  = tri->GetIndexOfP0();
	    Int32 nP1  = tri->GetIndexOfP1();
	    Int32 nP2  = tri->GetIndexOfP2();
	    if(!AlreadShading.TestAndSet(nP0,obj.GetStartIndex()))
	    {
		Vertex v(SelectBuffer(nP0),AdjustP(nP0));
	        LightMgr::Instance().Shading(v,v.GetColor());
	    }
	    if(!AlreadShading.TestAndSet(nP1,obj.GetStartIndex()))
	    {
		Vertex v(SelectBuffer(nP1),AdjustP(nP1));
	        LightMgr::Instance().Shading(v,v.GetColor());
	    }
	    if(!AlreadShading.TestAndSet(nP2,obj.GetStartIndex()))
	    {
		Vertex v(SelectBuffer(nP2),AdjustP(nP2));
	        LightMgr::Instance().Shading(v,v.GetColor());
	    }
	}
    }
#undef SelectBuffer
#undef AdjustP

}


