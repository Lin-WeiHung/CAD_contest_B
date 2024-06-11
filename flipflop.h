#include <iostream>
#include <string>
using namespace std;

class flipflop
{
public:
    flipflop();
    void setBits(int);
    void setName(string);
    void setWidth(float);
    void setHeight(float);
    void setArea(float, float);
    void setPinCount(int);
    float getWidth();
    float getHeight();
    void coutt();
    
private:
    int bits;
    string name;
    float width;
    float height;
    float area;
    int pinCount;
};