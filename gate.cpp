#include "header.h"
#include "gate.h"

Gate::Gate()
{
    bits = 0;
    width = 0;
    height = 0;
    area = 0;
    pinCount = 0;
    power = 0;
}

void Gate::setBits(int bits) { this->bits = bits; }
void Gate::setName(string name) { this->name = name; }
void Gate::setWidth(double width) { this->width = width; }
void Gate::setHeight(double height) { this->height = height; }
void Gate::setArea(double width, double height) { this->area = width * height; }
void Gate::setPinCount(int pinCount) { this->pinCount = pinCount; }
void Gate::setPower(double power){this->power = power;};
double Gate::getWidth() { return width; }
double Gate::getHeight() { return height; }
double Gate::getArea() { return area; }
string Gate::getName() { return name; }
float Gate::getPower() { return power;}
void Gate::setGatePin(Pin_g p) { pins.push_back(p); }
void Gate::GateCout()
{
    cout << name << ": " << "bit: " << bits << "; width: " << width << "; height: " << height << "; area: " << area << "; pincount: " << pinCount <<"; gatePower: "<< power<< endl;
}
void Gate::pinCout()
{
    for(size_t i = 0; i < pins.size(); i++){
        cout << "Pin: " << pins[i].pinName << " X: " << pins[i].pinX << " Y: " << pins[i].pinY << endl;
    }
}
