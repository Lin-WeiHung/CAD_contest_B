#include "header.h"
#include "flipflop.h"

Flipflop::Flipflop()
{
    bits = 0;
    width = 0;
    height = 0;
    area = 0;
    pinCount = 0;
    power = 0;
}

void Flipflop::setBits(int bits) { this->bits = bits; }
void Flipflop::setName(string name) { this->name = name; }
void Flipflop::setWidth(double width) { this->width = width; }
void Flipflop::setHeight(double height) { this->height = height; }
void Flipflop::setArea(double width, double height) { this->area = width * height; }
void Flipflop::setPinCount(int pinCount) { this->pinCount = pinCount; }
void Flipflop::setPower(double power){this->power = power;}
void Flipflop::setQpinDelay(float Qpin){ this->QpinDelay = Qpin;}
double Flipflop::getWidth() { return width; }
double Flipflop::getHeight() { return height; }
double Flipflop::getArea() { return area; }
string Flipflop::getName() { return name; }
float Flipflop::getPower() { return power;}
float Flipflop::getQpinDelay() { return QpinDelay; }
void Flipflop::setFFPin(Pin p) { pins.push_back(p); }
void Flipflop::FFcout()
{
    cout << name << ": " << "bit: " << bits << "; width: " << width << "; height: " << height << "; area: " << area << "; pincount: " << pinCount <<"; gatePower: "<< power<< endl;
}
void Flipflop::pinCout()
{
    for(size_t i = 0; i < pins.size(); i++){
        cout << "Pin: " << pins[i].pinName << " X: " << pins[i].pinX << " Y: " << pins[i].pinY << endl;
    }
}
pair<float, float> Flipflop::getPinCor(string FF_type, string pin_name){
    if(name == FF_type){
        for(size_t i = 0; i < pins.size(); i++){
            if(pins[i].pinName == pin_name) return make_pair(pins[i].pinX, pins[i].pinY);
        }
    }
}
