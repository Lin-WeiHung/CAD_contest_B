#ifndef _FLIPFLOP_H_
#define _FLIPFLOP_H_

#include "header.h"

class Flipflop
{
public:
    Flipflop();
    void setBits(int);
    void setName(string);
    void setWidth(float);
    void setHeight(float);
    void setArea(float, float);
    void setPinCount(int);
    double getWidth();
    double getHeight();
    double getArea();
    void coutt();
    
private:
    int bits;
    string name;
    double width;
    double height;
    double area;
    int pinCount;
};

#endif