#ifndef _CELL_H_
#define _CELL_H_

#include "header.h"

class Cell {
private:
    string cellName;
    string ffType;
    float posX;
    float posY;
    float timingSlack;
    float power;
    float area_c;
    float QpinDelay;

public:
    Cell();
    void setCellName(const string& name);
    void setFFType(const string& type);
    void setPosX(float x);
    void setPosY(float y);
    void setTimingSlack(float slack);
    void setPower(float gatePower);
    void setArea(float area);
    void setQpinDelay(float Qpin);
    string getCellName() const;
    string getFFType() const;
    float getPosX() const;
    float getPosY() const;
    float getTimingSlack() const;
    float getPower() const;
    float getArea() const;
    float getQpinDelay() const;
    void print() const;
};

#endif