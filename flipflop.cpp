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
void Flipflop::setWidth(float width) { this->width = width; }
void Flipflop::setHeight(float height) { this->height = height; }
void Flipflop::setArea(float width, float height) { this->area = width * height; }
void Flipflop::setPinCount(int pinCount) { this->pinCount = pinCount; }
float Flipflop::getWidth() { return width; }
float Flipflop::getHeight() { return height; }
void Flipflop::coutt()
{
    cout << bits << endl;
    cout << width << endl;
    cout << height << endl;
    cout << area << endl;
    cout << pinCount << endl;
}