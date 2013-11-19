#include "Graphic/Camera.h"
#include "Graphic/Transform.h"
#include "Math/Math.h"
Camera::Camera(Real screenWidth
    ,Real screenHeight)
    :m_rWidth(screenWidth)
    ,m_rHeight(screenHeight)
    ,m_matCamera(Matrix::Identity)
    ,m_matProject(Matrix::Identity)
    ,m_matScreen(Matrix::Identity)
{
}

void Camera::SetEulerCamera(Real xPos,Real yPos,Real zPos,Real xRot,Real yRot,Real zRot)
{
    Transform trans;
    trans.Translate(-xPos,-yPos,-zPos);
    trans.Rotate(-xRot,-yRot,-zRot);

    m_matCamera = trans;
}

void Camera::LookAt(Real xFrom,Real yFrom,Real zFrom,Real xTo,Real yTo,Real zTo)
{
    m_matCamera(2) = Vector(xTo - xFrom,yTo - yFrom,zTo - zFrom);       //z
    m_matCamera(1) = Vector(0.0,1.0,0.0);    //y
    m_matCamera(0) = m_matCamera(1).Cross(m_matCamera(2)); //x
    m_matCamera(1) = m_matCamera(2).Cross(m_matCamera(0));

    m_matCamera(0).Normalize();
    m_matCamera(1).Normalize();
    m_matCamera(2).Normalize();

    Transform trans;
    trans.Translate(-xFrom,-yFrom,-zFrom);
    m_matCamera *= trans;
}

void Camera::SetSphericalCamera(Real xPos,Real yPos,Real zPos, Real elevation,Real azimuth)
{
    Point target;
    Real SinEle = Sin(elevation);
    Real CosEle = Cos(elevation);
    Real SinAzi = Sin(azimuth);
    Real CosAzi = Cos(azimuth);

    target.x = - SinEle * SinAzi;
    target.y = CosAzi;
    target.z = SinEle * CosAzi;
    LookAt(xPos,yPos,zPos,target);
}

void Camera::Frustum(Real near,Real far,Real fov)
{
    m_near = near;
    m_far = far;
    m_fov = fov;
    m_viewDist = Cot(fov / 2);

    if(PI_DIV_2 == fov)
    {
	m_rightPlane = Plane(Point::ORIGION,Vector(-1,0,-1).Normalize());
	m_leftPlane = Plane(Point::ORIGION,Vector(1,0,-1).Normalize());
	m_topPlane = Plane(Point::ORIGION,Vector(0,1,-1).Normalize());
	m_bottomPlane = Plane(Point::ORIGION,Vector(0,-1,-1).Normalize());
    }
    else
    {
	m_rightPlane = Plane(Point::ORIGION,Vector(m_viewDist,0, -m_rWidth * 0.5));
	m_leftPlane = Plane(Point::ORIGION,Vector(-m_viewDist,0,-m_rWidth * 0.5));
	m_topPlane = Plane(Point::ORIGION,Vector(0,m_viewDist,-m_rHeight * 0.5));
	m_bottomPlane = Plane(Point::ORIGION,Vector(0,-m_viewDist,-m_rHeight * 0.5));
    }

    m_matProject(0,0) = m_matProject(1,1) = m_viewDist;
    m_matProject(2,2) = 0.0;
    m_matProject(2,3) = 1.0;
    m_matProject(3,2) = 1.0;
    m_matProject(3,3) = 0.0;
}

void Camera::SetViewport(Int32 nX,Int32 nY,Int32 nWidth,Int32 nHeight)
{
    m_rWidth = nWidth;
    m_rHeight = nHeight;

    Real halfW = m_rWidth * 0.5;
    Real halfH = m_rHeight * 0.5;
    m_matScreen(0,0) = halfW;
    m_matScreen(0,3) = halfW + nX;
    m_matScreen(1,1) = halfH;
    m_matScreen(1,3) = halfH + nY;
}


