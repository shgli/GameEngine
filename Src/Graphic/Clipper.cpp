#include "Graphic/Object.h"
#include "Graphic/Clipper.h"
#include "Graphic/Camera.h"
#include "Graphic/Triangle.h"
void Clipper::Visit(Object& obj)
{
    auto &aActiveTriangles = obj.GetActiveTriangles();
    auto &aVertices = aActiveTriangles.GetVertices();
    Int32 nSize = aActiveTriangles.GetSize();

    Triangle *tri = nullptr;
    while(nullptr != (tri = aActiveTriangles.Dequeue()))
    {
	//判断三点相对于视景体的位置
	VertexIndex* i0 = &tri->GetIndex0();
	VertexIndex* i1 = &tri->GetIndex1();
	VertexIndex* i2 = &tri->GetIndex2();

        Vertex v0(aVertices,*i0);	
        Vertex v1(aVertices,*i1);	
        Vertex v2(aVertices,*i2);	

	Int32 nStatus0 = DeterminateStatus(v0);
	Int32 nStatus1 = DeterminateStatus(v1);
	Int32 nStatus2 = DeterminateStatus(v2);

	//根据不同的状态作不同的操作:
	//1. 若nStatus0,nStatus1,nStatus2都为0x00 则clip掉
	//2. 若三个顶点的状态是除了0x01外的两种状态，则通过了clipper
	//3. 若三个顶点的状态是除了0x02外的两种状态，则被clip掉了
	//否则需要进行裁剪
	switch(nStatus0 | nStatus1 | nStatus2)
	{
	    case 0:
	    case 1:
		//clipped
		break;
	    case 2:
		//pass
		aActiveTriangles.Enqueue(tri);
		break;
	    case 3:
		{
		    Vertex* ppos0(&v0),*ppos1(&v1),*ppos2(&v2);
		    //可分为三种情况
		    //1. 只有一个点在near平面上
		    //2. 只有一个点在near后面
		    //3. 只有一个点在near前面
		    if(0 == nStatus0 || 0 == nStatus1 || 0 == nStatus2)
		    {
			//情况1: 只有一个点在near平面上 处理步骤:
			//1. 将在near平面上的点变为第0个点
			if(0 == nStatus1)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,1);
			}
			else if(0 == nStatus2)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,2);
			}

			//2. 求线段ppos1->ppos2与平面near的交点
			VertexIndex nNewIdx = IntersectAndInterpolateAttr(ppos1,ppos2,aVertices);

			if(ppos1->GetPosition().z < r_pCamera->GetNear())
			{
			    aActiveTriangles.Enqueue(*i0,nNewIdx,*i2,tri->GetMaterialID());
			}
			else
			{
			    aActiveTriangles.Enqueue(*i0,*i1,nNewIdx,tri->GetMaterialID());
			}
		    }
		    else if(5 == (nStatus0 + nStatus1 + nStatus2)) //1 2 2
		    {
			//情况2:只有一个在near后面 处理步骤:
			//1. 将在near后的点变为第0个点
			if(0x01 == nStatus1)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,1);
			}
			else if(0x01 == nStatus2)
			{
                            AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,2);
			}

			//求出p0->p1以及p0->p2与near的交点
			VertexIndex nIntersect1 = IntersectAndInterpolateAttr(ppos0,ppos1,aVertices);
			VertexIndex nIntersect2 = IntersectAndInterpolateAttr(ppos0,ppos2,aVertices);
			
			//将新生成的三角形加入到三角形列表中
			aActiveTriangles.Enqueue(nIntersect1,*i1,*i2,tri->GetMaterialID());
			aActiveTriangles.Enqueue(nIntersect2,nIntersect1,*i2,tri->GetMaterialID());
		    }
		    else
		    {
			//情况2:只有一个在near前面 处理步骤:
			//1. 将在near前的点变为第0个点
			if(0x02 == nStatus1)
			{
			    AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,1);
			}
			else if(0x02 == nStatus2)
			{
                            AdjustSequence(ppos0,ppos1,ppos2,i0,i1,i2,2);
			}
			//求出p0->p1以及p0->p2与near的交点
			VertexIndex&& nIntersect1 = IntersectAndInterpolateAttr(ppos0,ppos1,aVertices);
			VertexIndex&& nIntersect2 = IntersectAndInterpolateAttr(ppos0,ppos2,aVertices);
			
			//将新生成的三角形加入到三角形列表中
                        aActiveTriangles.Enqueue(*i0,nIntersect1,nIntersect2,tri->GetMaterialID());
		    }
		}
		break;
	    default:
		assert(false);
	}
    }
}

VertexIndex Clipper::IntersectAndInterpolateAttr(Vertex* p0,Vertex* p1,VertexArray& aVertices)
{
    VertexIndex iV;
    Double t = (r_pCamera->GetNear() - p0->GetPosition().z) / (p1->GetPosition().z - p0->GetPosition().z);

    //插值属性
    auto& aPositions = aVertices.GetPositions();
    auto& aTextCoords = aVertices.GetTextCoords();
    auto& aNormals = aVertices.GetNormals();
    auto& aColors = aVertices.GetColors();

    aPositions.Append(p0->GetPosition() + t * (p1->GetPosition() - p0->GetPosition()));
    iV.SetPositionIndex(aPositions.LastIndex());

    if(p0->HasAttribute(VA_COLOR))
    {
	aColors.Append(p0->GetColor() + t * (p1->GetColor() - p0->GetColor()));
	iV.SetColorIndex(aColors.LastIndex());
    }

    if(p0->HasAttribute(VA_TEXTCOOR))
    {
	aTextCoords.Append(p0->GetTextCoord() + t * (p1->GetTextCoord() - p0->GetTextCoord()));
	iV.SetTextCoordIndex(aTextCoords.LastIndex());
    }

    if(p0->HasAttribute(VA_TEXTCOOR1))
    {
	aTextCoords.Append(p0->GetTextCoord() + t * (p1->GetTextCoord() - p0->GetTextCoord()));
	iV.SetTextCoordIndex(aTextCoords.LastIndex());
    }

    if(p0->HasAttribute(VA_NORMAL))
    {
        aNormals.Append(p0->GetNormal() + t * (p1->GetNormal() - p0->GetNormal()));
	iV.SetNormalIndex(aNormals.LastIndex());
    }
   
    return iV;
}

Int32 Clipper::DeterminateStatus(Vertex& v)
{
    if(v.GetPosition().z < r_pCamera->GetNear())
    {
	return 0x01; //在near后面
    }
    else if(v.GetPosition().z > r_pCamera->GetNear())
    {
	return 0x02; //在near前面
    }
    else
    {
	return 0x00; //在平面之上
    }
}

void Clipper::AdjustSequence(Vertex*& pp0,Vertex*& pp1,Vertex*& pp2
	,VertexIndex*& i0,VertexIndex*& i1,VertexIndex*& i2,Int32 nFirstIdx)
{
    if(1 == nFirstIdx)
    {
	Swap(pp0,pp1);
	Swap(pp1,pp2);
	Swap(i0,i1);
	Swap(i1,i2);
    }
    else if(2 == nFirstIdx)
    {
	Swap(pp0,pp1);
	Swap(pp0,pp2);
	Swap(i0,i1);
	Swap(i0,i2);
    }
}

