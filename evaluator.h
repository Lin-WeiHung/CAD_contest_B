#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include "header.h"
#include "flipflop.h"
#include "cell.h"

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

private:
    double alpha;
    double beta;
    double gamma;
    double lambda;
    vector<Flipflop> flipflop;
    vector<Cell> input_cells;
    vector<Cell> output_cells;
    map<string, pair_data> match_data;
};

#endif