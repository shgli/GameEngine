#ifndef _LIGHTMGR_H
#define _LIGHTMGR_H
#include "Common/Common.h"
#include "Math/Math.h"
#include "Graphic/Color.h"
#include "Graphic/VertexArray.h"
#include "Graphic/Material.h"

enum LightType
{
    LIGHT_NONE,
    LIGHT_GLOBAL_AMBIENT,
    LIGHT_INFINITE,
    LIGHT_POINT,
    LIGHT_SPOT,
};

struct VertexLightAttr
{
    Point *position;
    Vector *normal;
    Material *material;
    Vector viewDir;
    ColorEx clr;
};

class Light
{
public:
    bool IsOn( void ) const { return m_isOn;}
    void Enable(bool b) { m_isOn = b; }
    void Shading(VertexLightAttr& v);

    inline void SetType(LightType eType) { m_eType = eType; }

    inline void SetAmbient(const Color& clr) { m_clrAmbient = clr; }
    inline void SetDiffuse(const Color& clr) { m_clrDiffuse = clr; }
    inline void SetSpecular(const Color& clr) { m_clrSpecular = clr; }

    inline void SetSpot(const Vector& dirSpot,Double cutoff,Int32 nExp)
    {
        m_dirSpot = dirSpot;
        m_dCutOff = cutoff;
        m_nExponent = nExp;
    }

    inline void SetAttentation(Double constant,Double linear,Double quadric)
    {
        m_dConstant = constant;
        m_dLinear = linear;
        m_dQuadric = quadric;
    }

private:
    void CalculateAmbient(VertexLightAttr& v);
    void CalculateDiffuse(VertexLightAttr& v);
    void CalculateSpecular(VertexLightAttr& v);
    void CalcHelpVariables(VertexLightAttr& v);

    Point m_position;
    Vector m_dirSpot;

    Color m_clrAmbient;
    Color m_clrDiffuse;
    Color m_clrSpecular;

    Double m_dConstant,m_dLinear,m_dQuadric; //atten
    Double m_dCutOff;

    Int32 m_nExponent;

    bool m_isOn;
    LightType m_eType;

    //temp variable
    Vector m_vextex2Light;
    Double m_dist;

    friend class LightMgr;
};

class LightMgr
{
public:
    static LightMgr& Instance( void );

    void Shading(VertexIndex& v);

    Light& GetLight(Int32 nIdx) { return m_lights[nIdx]; }
private:
    void Shading(VertexLightAttr& v);

    static const Int32 MAX_LIGHTS = 8;
    Light m_lights[MAX_LIGHTS];
};
#endif

