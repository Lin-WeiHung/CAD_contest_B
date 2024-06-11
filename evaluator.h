#include <iostream>
#include <vector>
#include <fstream>
#include "flipflop.h"
using namespace std;


class evaluator
{
public:
    evaluator();
    void parser();

private:
    float alpha;
    float beta;
    float gamma;
    float lambda;
    vector<flipflop> FlipFlop;

    ifstream file;
};