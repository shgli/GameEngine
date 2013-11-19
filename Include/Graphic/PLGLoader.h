#ifndef _PLGLOADER_H
#define _PLGLOADER_H

enum CoordinateSystem
{
    RightHanded
    ,LeftHanded
};
class Object;
class PLGLoader
{
public:
    Object* Load(const std::string & strFile,CoordinateSystem cs = RightHanded);

private:
    void GetLine(std::ifstream& file,std::stringstream& strStream) const;
};
#endif

