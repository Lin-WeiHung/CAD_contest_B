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

public:
    Cell();
    void setCellName(const string& name);
    void setFFType(const string& type);
    void setPosX(float x);
    void setPosY(float y);
    void setTimingSlack(float slack);
    string getCellName() const;
    string getFFType() const;
    float getPosX() const;
    float getPosY() const;
    float getTimingSlack() const;
    void print() const;
};

#endif