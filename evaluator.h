#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include "header.h"
#include "flipflop.h"

#define FEATURE_START 0

class Evaluator
{
public:
    Evaluator();
    bool parser(char* input_file);
    //test
    void parser_test();

private:
    double alpha;
    double beta;
    double gamma;
    double lambda;
    vector<Flipflop> FlipFlop;
};

#endif