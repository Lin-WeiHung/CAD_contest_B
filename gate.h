#ifndef _GATE_H_
#define _GATE_H_

#include "header.h"
struct Pin_g
{
    string pinName;
    double pinX;
    double pinY;
    
    Pin_g() {}
};



class Gate
{
public:
    Gate();
    void setBits(int);
    void setName(string);
    void setWidth(double);
    void setHeight(double);
    void setArea(double, double);
    void setPower(double);
    void setPinCount(int);
    double getWidth();
    double getHeight();
    double getArea();
    string getName();
    float getPower();
    void setGatePin(Pin_g);
    void GateCout();
    void pinCout();
private:
    int bits;
    string name;
    double width;
    double height;
    double area;
    double power;
    int pinCount;
    vector<Pin_g> pins;
};
#endif