#ifndef _MATCH_H_
#define _MATCH_H_
#include "header.h"
#include "cell.h"
struct pair_data{
    string new_ff;
    map<string, string>pair;
    pair_data() {};
};

class Match
{
public:
    Match();
    bool parser_outfile(char* output_file);
    void parser_outfile_test();
    vector<string>cut_tokens(string);
    void parser_test();

private:
    int cell_num;
    vector<Cell>newFF_list;
    map<string, pair_data>match_data;
};
#endif