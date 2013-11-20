#include "Common/Common.h"
#include "Graphic/ProjectStep.h"
#include "Graphic/Object.h"
#include "Graphic/Camera.h"
#include "Graphic/Triangle.h"
#include "Graphic/RenderTri.h"

void ProjectStep::ProcessPosition(const VertexIndex& idx,VertexArray& buf)
{
    Vertex v(buf,idx);
    Point& pt = v.GetPosition();
    pt = r_pCamera->GetProjectMatrix() * pt;
    pt.ProjectDiv();
    pt = r_pCamera->GetScreenMatrix() * pt;

    if(buf.HasAttribute(VA_TEXTCOOR))
    {
	TextCoord& coor = v.GetTextCoord();
	coor.t *= pt.z;
	coor.s *= pt.z;
        TextFix::Double2Fix(coor.t);
        TextFix::Double2Fix(coor.s);
    }

    if(buf.HasAttribute(VA_TEXTCOOR1))
    {
    	TextCoord& coor = v.GetTextCoord1();
	coor.t *= pt.z;
	coor.s *= pt.z;
        TextFix::Double2Fix(coor.t);
        TextFix::Double2Fix(coor.s);
    }
}

void ProjectStep::Visit(Object& obj)
{
    static const Int32 NEGATIVE_SIZE = MAX_VERTEX_PEROBJECT / 4;
    static StatusArray IsProcessed(MAX_VERTEX_PEROBJECT,NEGATIVE_SIZE);
    IsProcessed.Reset();
    auto& aTriangles = obj.GetActiveTriangles();
    auto& aVertexArray = aTriangles.GetVertices();
    for(Int32 iTri = 0; iTri < aTriangles.GetSize(); ++iTri)
    {
	Triangle& triangle = aTriangles[iTri];
	VertexIndex& idx0 = triangle.GetIndex0();
	VertexIndex& idx1 = triangle.GetIndex1();
	VertexIndex& idx2 = triangle.GetIndex2();

	if(!IsProcessed.TestAndSet(idx0.GetPositionIndex(),NEGATIVE_SIZE))
	{
	    ProcessPosition(idx0,aVertexArray);
	}

	if(!IsProcessed.TestAndSet(idx1.GetPositionIndex(),NEGATIVE_SIZE))
	{
	    ProcessPosition(idx1,aVertexArray);
	}

	if(!IsProcessed.TestAndSet(idx2.GetPositionIndex(),NEGATIVE_SIZE))
	{
	    ProcessPosition(idx2,aVertexArray);
	}
    } 
}

