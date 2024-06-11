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
    float getWidth();
    float getHeight();
    void coutt();
    
private:
    int bits;
    string name;
    float width;
    float height;
    float area;
    int pinCount;
};

#endif