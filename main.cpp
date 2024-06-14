#include "header.h"
#include "evaluator.h"
#include "match.h"

int main(int argc, char* argv[])
{
    Evaluator evaluator;
    if (!evaluator.parser(argv[ARGV_INPUT_INDEX])){
        return false;
    }
    evaluator.parser_test();

    Match match;
    if (!match.parser_outfile(argv[ARGV_OUTPUT_INDEX])){
        return false;
    }
    match.parser_test();
    return 0;
}