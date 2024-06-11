#include "header.h"
#include "cell.h"

// Cell class implementation
Cell::Cell() : posX(0), posY(0), timingSlack(0) {}

void Cell::setCellName(const string& name) {
    cellName = name;
}

void Cell::setFFType(const string& type) {
    ffType = type;
}

void Cell::setPosX(float x) {
    posX = x;
}

void Cell::setPosY(float y) {
    posY = y;
}

void Cell::setTimingSlack(float slack) {
    timingSlack = slack;
}

string Cell::getCellName() const {
    return cellName;
}

string Cell::getFFType() const {
    return ffType;
}

float Cell::getPosX() const {
    return posX;
}

float Cell::getPosY() const {
    return posY;
}

float Cell::getTimingSlack() const {
    return timingSlack;
}

void Cell::print() const {
    cout << "Cell Name: " << cellName << ", FF Type: " << ffType
         << ", PosX: " << posX << ", PosY: " << posY
         << ", Timing Slack: " << timingSlack << endl;
}