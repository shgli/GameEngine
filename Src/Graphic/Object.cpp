#include "Math/Math.h"
#include "Graphic/Object.h"
#include "Graphic/Triangle.h"
Object::Object(const std::string& strName,const ObjectModelPtr& pModel,ObjectAttribute attri)
    :m_attribute(attri)
    ,m_state(0)
    ,m_strName(strName)
    ,m_pObjectModel(pModel)
{
}

Object::~Object( void )
{
}

void Object::Update(const Matrix& mat)
{
    m_transform.Translate(m_worldPos.x,m_worldPos.y,m_worldPos.z);
    Matrix mTrans = mat * m_transform;

    m_pObjectModel->Copy2(m_aActiveTriangles.GetVertices(),m_aActiveTriangles.GetTriangles());

    VertexArray& aVertices = m_aActiveTriangles.GetVertices();

    for(int i = 0; i < aVertices.GetPositionSize(); ++i)
    {
	aVertices.GetPosition(i) = mat * aVertices.GetPosition(i);
    }

}

void Object::Update( void )
{
    Update(m_transform);
}

void Object::Accept(Step* visitor)
{
    visitor->Visit(*this);
}

void Object::CalculateBound( void )
{
    VertexArray& aVertices = m_aActiveTriangles.GetVertices();
    if(0 == aVertices.GetPositionSize())
    {
	m_bound = Sphere();
    }

    Vector sum = Vector::Zero;
    for(int i = 0; i < aVertices.GetPositionSize(); ++i)
    {
	sum += aVertices.GetPosition(i);
    }

    m_bound.center = sum / aVertices.GetPositionSize();

    m_bound.radius = 0.0;
    for(int i = 0; i < aVertices.GetPositionSize(); ++i)
    {
	Vector diff = aVertices.GetPosition(i) - m_bound.center;
	Real tmp = diff.NormSqure();
	if(tmp > m_bound.radius)
	{
	    m_bound.radius = tmp;
	}
    }

    m_bound.radius = Sqrt(m_bound.radius);

}

std::ostream& operator<< (std::ostream& os,const Object& obj)
{
//    SAVE_INDENT(cindent);
//    os<<"Object "<<obj.GetName()<<std::endl;
//    os<<cindent.Shift(1)<<"# of triangles: "<<obj.GetTriangleCount()<<std::endl;
//
//    cindent.Shift(1);
//    Triangle tri;
//    for(Int32 nTri = 0; nTri < obj.GetTriangleCount(); ++nTri)
//    {
//	obj.GetTriangle(nTri,tri);
//        os<<cindent.Shift(0)<<nTri<<" "<<tri<<std::endl;
//    }
//
//    os<<cindent.Shift(-1)<<"Bound: "<<std::endl;
//    os<<cindent.Shift(1)<<obj.GetBound()<<std::endl;
//
//    os<<cindent.Shift(-1)<<"Transform: "<<obj.m_transform<<std::endl;
//
//    os<<cindent.Shift(-1)<<"status: ";
//    if(obj.IsActive())
//    {
//	os<< "actived : ";
//    }
//    else
//    {
//	os<< "not actived :";
//    }
//
//    if(obj.IsCulled())
//    {
//	os << "been culled .";
//    }
//    else
//    {
//	os << "not culled .";
//    }
//
    return os;
}

Object* Object::Clone( void )
{
    return new Object(GetName(),m_pObjectModel);
}

//Attributes Object::SelectBuffer()
//{
//
//}
