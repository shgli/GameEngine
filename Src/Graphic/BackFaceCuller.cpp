#include "Math/Math.h"
#include "Graphic/BackFaceCuller.h"
#include "Graphic/Object.h"
#include "Graphic/GraphicException.h"
#include "Graphic/Types.h"
#include "Graphic/Triangle.h"

void BackFaceCuller::Visit(Object& obj) 
{
    if(obj.IsCulled() || BFC_ALWAYS == obj.GetBackFaceMode())
    {
	throw ObjectBeCulled();
    }

    CalculateNormals(obj);
    auto& aActiveTriangles = obj.GetActiveTriangles();
    auto& aPositions = aActiveTriangles.GetVertices().GetPositions();

    Triangle *pTriangle = nullptr;
    while(nullptr != (pTriangle = aActiveTriangles.Dequeue()))
    {
	if(BFC_NEVER != obj.GetBackFaceMode() && pTriangle->HasState(FT_SINGLE))
	{
            Point& viewD = aPositions[pTriangle->GetPositionIndex(0)];
	    Real dotValue = pTriangle->GetNormal().Dot(viewD);	

	    if(BFC_BACK == obj.GetBackFaceMode())
	    {
		if(dotValue >= 0)
		{
		    aActiveTriangles.Enqueue(pTriangle);
		}
	    }
	    else
	    {
		if(dotValue <= 0)
		{
		    aActiveTriangles.Enqueue(pTriangle);
		}
	    }
	}
	else
	{
	    aActiveTriangles.Enqueue(pTriangle);
	}
    }
}

void BackFaceCuller::CalculateNormals(Object& obj) const
{
    static int aNormalCnt[MAX_VERTEX_PEROBJECT]; 
    std::memset(aNormalCnt,0,sizeof(aNormalCnt));
    
    auto &aActiveTriangles = obj.GetActiveTriangles();
    auto &aNormals = aActiveTriangles.GetVertices().GetNormals();
    auto &aTriangles = aActiveTriangles.GetTriangles();
    for(Int32 iTriangle = 0; iTriangle < aTriangles.GetSize(); ++iTriangle)
    {
	auto tri = aTriangles[iTriangle];
	tri->CalculateNormal(aActiveTriangles.GetVertices());

	if(obj.NeedShading())
	{
	    UInt32 idxP0 = tri->GetPositionIndex(0);
	    UInt32 idxP1 = tri->GetPositionIndex(1);
	    UInt32 idxP2 = tri->GetPositionIndex(2);

	    aNormals[idxP0] += tri->GetNormal();
	    aNormals[idxP1] += tri->GetNormal();
	    aNormals[idxP2] += tri->GetNormal();

	    ++aNormalCnt[idxP0];
	    ++aNormalCnt[idxP1];
	    ++aNormalCnt[idxP2];
	}
    }

    if(obj.NeedShading())
    {
	for(int idx = 0; idx < aNormals.GetSize(); ++idx)
	{
	    if(aNormalCnt[idx] > 0)
	    {
		aNormals[idx] /= aNormalCnt[idx];
		aNormals[idx].Normalize();
	    }
	}
    }
}
