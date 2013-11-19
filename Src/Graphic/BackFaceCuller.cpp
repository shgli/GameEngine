#include "Math/Math.h"
#include "Graphic/BackFaceCuller.h"
#include "Graphic/Object.h"
#include "Graphic/GraphicException.h"
#include "Graphic/GraphicTypes.h"
#include "Graphic/Triangle.h"

void BackFaceCuller::Visit(Object& obj) 
{
    if(obj.IsCulled() || BFC_ALWAYS == obj.GetBackFaceMode())
    {
	throw ObjectBeCulled();
    }

    CalculateNormals(obj);
    VertexBuffer& buf = obj.GetVertexBuffer();
    for(auto tri : obj.GetTriangles())
    {
	if(BFC_NEVER != obj.GetBackFaceMode() && tri->HasAttribute(FT_SINGLE))
	{
            Point& viewD = buf.GetPosition(tri->GetIndexOfP0());
	    Real dotValue = tri->GetNormal().Dot(viewD);	

	    if(dotValue <= 0)
	    {
		tri->AddState(FS_BACKFACE);
	    }
	    else
	    {
		tri->AddState(FS_FRONTFACE);
	    }

	    if(BFC_BACK == obj.GetBackFaceMode())
	    {
		if(tri->HasState(FS_BACKFACE))
		{
		    tri->AddState(TS_CULLED);
		}
	    }
	    else
	    {
		if(tri->HasState(FS_FRONTFACE))
		{
		    tri->AddState(TS_CULLED);
		}
	    }
	}
    }
}

void BackFaceCuller::CalculateNormals(Object& obj) const
{
    static int aNormalCnt[MAX_VERTEX_PEROBJECT]; 
    std::memset(aNormalCnt,0,sizeof(aNormalCnt));
    
    VertexBuffer& buf = obj.GetVertexBuffer();
    for(auto tri : obj.GetTriangles())
    {
	tri->CalculateNormal(buf);

	if(obj.NeedShading())
	{
	    UInt32 idxP0 = tri->GetIndexOfP0();
	    UInt32 idxP1 = tri->GetIndexOfP1();
	    UInt32 idxP2 = tri->GetIndexOfP2();

	    buf.GetNormal(idxP0) += tri->GetNormal();
	    buf.GetNormal(idxP1) += tri->GetNormal();
	    buf.GetNormal(idxP2) += tri->GetNormal();

	    ++aNormalCnt[idxP0];
	    ++aNormalCnt[idxP1];
	    ++aNormalCnt[idxP2];
	}
    }

    if(obj.NeedShading())
    {
	for(int idx = 0; idx < buf.GetSize(); ++idx)
	{
	    if(aNormalCnt[idx] > 0)
	    {
		buf.GetNormal(idx) /= aNormalCnt[idx];
		buf.GetNormal(idx).Normalize();
	    }
	}
    }
}
