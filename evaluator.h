#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include "header.h"
#include "flipflop.h"

class Evaluator
{
public:
    Evaluator();
    void parser();

private:
    float alpha;
    float beta;
    float gamma;
    float lambda;
    vector<Flipflop> FlipFlop;

    ifstream file;
};

#endif