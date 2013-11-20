#ifndef _OBJECTSTATE_H
#define _OBJECTSTATE_H
#include "Common/Common.h"
typedef Int32 ObjectState;
static const Int32 OS_ACTIVE = 0x0001;
static const Int32 OS_CULLED = 0x0002;

//========= Object Attributes ======//
typedef Int32 ObjectAttribute;
enum ObjectStyle
{
    EOS_LINEB = 0x0000,
    EOS_SOLID = 0x0001,
    EOS_MASK  = 0x0001
};

enum CullMode
{
    CM_NEVER  = 0x0000,
    CM_NEAR   = 0x0010,
    CM_FAR    = 0x0020,
    CM_LEFT   = 0x0040,
    CM_RIGHT  = 0x0080,
    CM_TOP    = 0x0100,
    CM_BOTTOM = 0x0200,
    CM_ALAWYS = 0x0400,
    CM_ALL    = CM_FAR | CM_LEFT | CM_RIGHT | CM_TOP | CM_BOTTOM,
    CM_MASK   = CM_ALL | CM_ALAWYS,
};


enum BackFaceCullerMode
{
    BFC_NEVER  = 0x0000,
    BFC_BACK   = 0x1000,
    BFC_FRONT  = 0x2000,
    BFC_ALWAYS = 0x4000,
    BFC_MASK   = 0x7000
};

enum ShadingMode
{
    SM_NEVER = 0x00000000,
    SM_CONST = 0x00010000,
    SM_PURE  = SM_CONST,
    SM_EMISSIVE = SM_CONST,

    SM_FLAT  = 0x00020000,
    SM_GOURAUD = 0x00040000,
    SM_PHONG = 0x00080000,
    SM_MASK  = 0x000f0000
};
#endif

