#ifndef _FLIPFLOP_H_
#define _FLIPFLOP_H_

#include "header.h"

struct Pin
{
    string pinName;
    double pinX;
    double pinY;
    
    Pin() {}
};

class Flipflop
{
public:
    Flipflop();
    void setBits(int);
    void setName(string);
    void setWidth(double);
    void setHeight(double);
    void setArea(double, double);
    void setPower(double);
    void setPinCount(int);
    void setQpinDelay(float);
    double getWidth();
    double getHeight();
    double getArea();
    string getName();
    float getPower();
    float getQpinDelay();
    void setFFPin(Pin);
    void FFcout();
    void pinCout();
    pair<float, float> getPinCor(string, string);
    
private:
    int bits;
    string name;
    double width;
    double height;
    double area;
    double power;
    int pinCount;
    float QpinDelay;
    vector<Pin> pins;
    
};

#endif