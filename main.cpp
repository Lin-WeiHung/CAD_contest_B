#include "header.h"
#include "evaluator.h"

int main(int argc, char* argv[])
{
    Evaluator evaluator;
    if (!evaluator.parser(argv[ARGV_INPUT_INDEX])){
        return false;
    }

    if (!evaluator.parser_outfile(argv[ARGV_OUTPUT_INDEX])){
        return false;
    }

    evaluator.parser_test();
    evaluator.CostFunction();
    return 0;
}