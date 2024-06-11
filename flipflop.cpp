#include <iostream>
#include <string>
#include "flipflop.h"
using namespace std;

flipflop::flipflop()
{
    bits = 0;
    width = 0;
    height = 0;
    area = 0;
    pinCount = 0;
}

void flipflop::setBits(int bits) { this->bits = bits; }
void flipflop::setName(string name) { this->name = name; }
void flipflop::setWidth(float width) { this->width = width; }
void flipflop::setHeight(float height) { this->height = height; }
void flipflop::setArea(float width, float height) { this->area = width * height; }
void flipflop::setPinCount(int pinCount) { this->pinCount = pinCount; }
float flipflop::getWidth() { return width; }
float flipflop::getHeight() { return height; }
void flipflop::coutt()
{
    cout << bits << endl;
    cout << width << endl;
    cout << height << endl;
    cout << area << endl;
    cout << pinCount << endl;
}