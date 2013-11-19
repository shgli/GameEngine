#ifndef _LIGHTMGR_H
#define _LIGHTMGR_H
#include "Common/Common.h"
#include "Math/Math.h"
#include "Graphic/Color.h"
#include "Graphic/VertexBuffer.h"

enum LightType
{
    LIGHT_AMBIENT,
    LIGHT_INFINITE,
    LIGHT_POINT,
    LIGHT_SPOT,
    LIGHT_SPOT1
};
class Light
{
public:
    LightType GetType( void ) const { return m_type; }
    bool IsOn( void ) const { return m_isOn;}
    void Enable(bool b) { m_isOn = b; }
private:
    LightType m_type;
    Color ambient,diffuse;
    Point position;
    Vector dir;
    Double cons,linear,quadric;
    Int32 exponent;

    bool m_isOn;

    friend class LightMgr;
};
class LightMgr
{
public:
    static LightMgr& Instance( void );

    void Shading(const Vertex& vertex,Color& clrBase);

    void SetAmbientLight(Int32 nLight,Color ambient)
    {
        if(nLight < MAX_LIGHTS)
        {
            m_lights[nLight].m_type = LIGHT_AMBIENT;
            m_lights[nLight].ambient = ambient;
        }
    }

    void SetInfiniteLight(Int32 nLight,Color diffuse)
    {
        if(nLight < MAX_LIGHTS)
        {
            m_lights[nLight].m_type = LIGHT_INFINITE;
            m_lights[nLight].diffuse = diffuse;
        }
    }


    void SetPointLight(Int32 nLight,Point& pos,Color diffuse)
    {
        if(nLight < MAX_LIGHTS)
        {
            m_lights[nLight].m_type = LIGHT_POINT;
            m_lights[nLight].position = pos;
            m_lights[nLight].diffuse = diffuse;
        }
    }

    void SetSpotLight(Int32 nLight,Vector& dir,Color diffuse)
    {
        if(nLight < MAX_LIGHTS)
        {
            m_lights[nLight].m_type = LIGHT_SPOT;
            m_lights[nLight].dir = dir;
            m_lights[nLight].diffuse = diffuse;
        }
    }

    void SetSpot1Light(Int32 nLight,Vector& dir,Color diffuse
                      ,Double cons = 1.0,Double linear = 10,Double quadric = 0.0,Int32 exp = 150)
    {
        if(nLight < MAX_LIGHTS)
        {
            m_lights[nLight].m_type = LIGHT_SPOT1;
            m_lights[nLight].dir = dir;
            m_lights[nLight].diffuse = diffuse;
            m_lights[nLight].cons = cons;
            m_lights[nLight].linear = linear;
            m_lights[nLight].quadric = quadric;
            m_lights[nLight].exponent = exp;
        }
    }

    inline void Enable(Int32 nLight,bool enable)
    {
        if(nLight < MAX_LIGHTS)
        {
           m_lights[nLight].Enable(enable);
        }
    }
private:
    void CalculateDiffuse(const Light& light,const Vertex& vertex,const Vector& vertex2light,Color clrBase,ColorEx& clrSum);

    static const Int32 MAX_LIGHTS = 8;
    Light m_lights[MAX_LIGHTS];
};
#endif

