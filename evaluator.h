#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include "header.h"
#include "flipflop.h"

class Evaluator
{
public:
    Evaluator();
    bool parser(char* input_file);

private:
    double alpha;
    double beta;
    double gamma;
    double lambda;
    vector<Flipflop> FlipFlop;
};

#endif