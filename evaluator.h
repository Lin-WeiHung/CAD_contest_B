#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include "header.h"
#include "flipflop.h"
#include "cell.h"
#include "gate.h"

#define FEATURE_START 0

struct pair_data{
    string new_ff;
    map<string, string>pair;
    pair_data() {};
};

class Evaluator
{
public:
    Evaluator();
    //parser
    vector<string>cut_tokens(string);
    bool parser(char* input_file);
    bool parser_outfile(char* output_file);
    //test
    void parser_test(); 
    float CostFunction();
    float Displacement();
    pair<float, float> AbsCordinate(string, string, string);
    pair<float, float> PinCordinate(string, string);
    
private:
    double alpha;
    double beta;
    double gamma;
    double lambda;
    double dis_co; //displacement coefficient : catch from the input file 
    vector<Flipflop> flipflop;
    vector<Gate>gate;
    vector<Cell> input_cells;
    vector<Cell> output_cells;
    map<string, pair_data> match_data;
};

#endif