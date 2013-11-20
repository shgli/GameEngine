#ifndef _IDRAWSTRATEGY_H
#define _IDRAWSTRATEGY_H

class IDrawStrategy
{
public:
    virtual void Start( void ) = 0;
    virtual void Stop( void ) = 0;

    virtual void Set(class Application* ) = 0;
};
#endif
 
