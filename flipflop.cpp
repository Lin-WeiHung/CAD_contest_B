#include "header.h"
#include "flipflop.h"

Flipflop::Flipflop()
{
    bits = 0;
    width = 0;
    height = 0;
    area = 0;
    pinCount = 0;
}

void Flipflop::setBits(int bits) { this->bits = bits; }
void Flipflop::setName(string name) { this->name = name; }
void Flipflop::setWidth(double width) { this->width = width; }
void Flipflop::setHeight(double height) { this->height = height; }
void Flipflop::setArea(double width, double height) { this->area = width * height; }
void Flipflop::setPinCount(int pinCount) { this->pinCount = pinCount; }
double Flipflop::getWidth() { return width; }
double Flipflop::getHeight() { return height; }
double Flipflop::getArea() { return area; }
void Flipflop::setFFPin(Pin p) { pins.push_back(p); }
void Flipflop::FFcout()
{
    cout << name << ": " << "bit: " << bits << "; width: " << width << "; height: " << height << "; area: " << area << "; pincount: " << pinCount << endl;
}
void Flipflop::pinCout()
{
    for(size_t i = 0; i < pins.size(); i++){
        cout << "Pin: " << pins[i].pinName << " X: " << pins[i].pinX << " Y: " << pins[i].pinY << endl;
    }
}
