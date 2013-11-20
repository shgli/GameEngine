#include "Graphic/LightStep.h"
#include "Graphic/Object.h"
#include "Graphic/Types.h"
#include "Graphic/LightMgr.h"
#include "Graphic/Triangle.h"

void LightStep::Visit(Object& obj)
{
    if(!obj.IsVisible() || !obj.NeedShading())
    {
	return ;
    }

    auto& aTriangles = obj.GetActiveTriangles();
    auto& aVertices = aTriangles.GetVertices();

    VertexLightAttr vLAttr;
    if(SM_FLAT == obj.GetShadingMode())
    {
	for(Int32 iTriangle = 0; iTriangle < aTriangles.GetSize(); ++iTriangle)
	{
	    LightMgr::Instance().Shading(aTriangles[iTriangle].GetIndex0());
	}
    }
    else
    {
	for(Int32 iTriangle = 0; iTriangle < aTriangles.GetSize(); ++iTriangle)
	{

	    LightMgr::Instance().Shading(aTriangles[iTriangle].GetIndex0());
	    LightMgr::Instance().Shading(aTriangles[iTriangle].GetIndex1());
	    LightMgr::Instance().Shading(aTriangles[iTriangle].GetIndex2());
	}
    }
}


