#ifndef _GRAPHICEXCEPTION_H
#define _GRAPHICEXCEPTION_H
#include <string>
class FileException
{
public:
    FileException(const std::string& strMsg)
	:m_strErrMsg(strMsg)
    {}
private:
    std::string m_strErrMsg;
};

class RangeException
{};

class NoSuchAttribute
{};

class ObjectBeCulled
{};
#endif

