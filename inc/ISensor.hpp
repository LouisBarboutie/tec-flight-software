#ifndef __ISENSOR_HPP__
#define __ISENSOR_HPP__

class ISensor
{
  public:
    virtual void InjectFailure() = 0;
    virtual void ClearFailure() = 0;
    virtual void ReadData() = 0;
};

#endif
