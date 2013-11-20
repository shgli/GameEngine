#ifndef _CAMERA_H
#define _CAMERA_H
#include "Math/Math.h"
enum RotateSeq
{
    RS_XYZ,
    RS_YZX,
    RS_ZXY,
    RS_XZY,
    RS_YXZ,
    MS_ZYX
};

class Camera
{
private:
    Point m_position;

    EulerAngle m_angle;

    Real m_fov;
    Real m_near;
    Real m_far;

    Plane m_leftPlane;
    Plane m_rightPlane;
    Plane m_topPlane;
    Plane m_bottomPlane;

    Real m_rWidth;
    Real m_rHeight;

    Real m_viewDist;

    Matrix m_matCamera;
    Matrix m_matProject;
    Matrix m_matScreen;

public:
    Camera(Real screenWidth
	  ,Real screenHeight);

    //for Euler camera
    void SetEulerCamera(const Point& pos,const EulerAngle& angle) { SetEulerCamera(pos.x,pos.y,pos.z,angle.x,angle.y,angle.z); }
    void SetEulerCamera(const Point& pos,Real xRot,Real yRot,Real zRot) { SetEulerCamera(pos.x,pos.y,pos.z,xRot,yRot,zRot); }
    void SetEulerCamera(Real xPos,Real yPos,Real zPos,EulerAngle& angle) { SetEulerCamera(xPos,yPos,zPos,angle.x,angle.y,angle.z); }
    void SetEulerCamera(Real xPos,Real yPos,Real zPos,Real xRot,Real yRot,Real zRot);

    //for UVN camera
    void LookAt(const Point& pos,const Point& target) { LookAt(pos.x,pos.y,pos.z,target.x,target.y,target.z);}
    void LookAt(Real xFrom,Real yFrom,Real zFrom,const Point& target) { LookAt(xFrom,yFrom,zFrom,target.x,target.y,target.z);}
    void LookAt(const Point& pos,Real xTo,Real yTo,Real zTo) { LookAt(pos.x,pos.y,pos.z,xTo,yTo,zTo);}
    void LookAt(Real xFrom,Real yFrom,Real zFrom,Real xTo,Real yTo,Real zTo);

    //for spherical camera
    void SetSphericalCamera(const Point& pos,Real elevation,Real azimuth) { SetSphericalCamera(pos.x,pos.y,pos.z,elevation,azimuth);}
    void SetSphericalCamera(Real xPos,Real yPos,Real zPos, Real elevation,Real szimuth);

    //for 
    void Frustum(Real near,Real far,Real fov);


    const Matrix& GetCameraMatrix( void ) const { return m_matCamera; }
    const Matrix& GetProjectMatrix( void ) const { return m_matProject; }
    const Matrix& GetScreenMatrix( void ) const { return m_matScreen; }

    //set screen with/height
    void SetViewport(Int32 nX,Int32 nY,Int32 nWidth,Int32 nHeight);

    Int32 GetScreenWidth( void ) const { return m_rWidth; }
    Int32 GetScreenHeight( void ) const { return m_rHeight; }


    //Get clip plane
    Real GetNear( void ) const { return m_near; }
    Real GetFar( void ) const { return m_far; }
    const Plane& GetLeftPlane( void ) const { return m_leftPlane; }
    const Plane& GetRightPlane( void ) const { return m_rightPlane; }
    const Plane& GetTopPlane( void ) const { return m_topPlane; }
    const Plane& GetBottomPlane( void ) const { return m_bottomPlane; }

};
#endif

