#include "header.h"
#include "evaluator.h"

int main(int argc, char* argv[])
{
    Evaluator evaluator;
    if (!evaluator.parser(argv[ARGV_INPUT_INDEX])){
        return false;
    }
    evaluator.parser_test();
    return 0;
}