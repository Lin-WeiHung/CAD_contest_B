#include "header.h"
#include "evaluator.h"

Evaluator::Evaluator()
{
    alpha = 0;
    beta = 0;
    gamma = 0;
    lambda = 0;
}

bool Evaluator::parser(char* input_file)
{
    cout << "Start reading " << input_file << endl;

    fstream infile(input_file, ios::in);

    if (!infile) {
        cout << "Input file " << input_file << " doesn't exist ..." << endl;
        return false;
    }

    string line;
    while (getline(infile, line)) {
        string feature;
        string temp;
        Flipflop f;

        //line == "FlipFlop 1 FF1 5.0 10.0 3"
        feature = line.substr(FEATURE_START, line.find(" "));
        line = line.substr(line.find(" ") + 1);

        if (feature == "Alpha") alpha = stof(line);
        else if (feature == "Beta") beta = stof(line);
        else if (feature == "Gamma") gamma = stof(line);
        else if (feature == "Lambda") lambda = stof(line);
        else if (feature == "FlipFlop") {
            
            //line == "1 FF1 5.0 10.0 3 "
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setBits(stoi(temp));

            //line == "FF1 5.0 10.0 3 "
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setName(temp);

            //line == "5.0 10.0 3 "
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setWidth(stof(temp));

            //line == "10.0 3 "
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setHeight(stof(temp));

            f.setArea(f.getWidth(), f.getHeight());

            //line == "3 "
            temp = line;
            f.setPinCount(stoi(temp));

            f.coutt();

            FlipFlop.push_back(f);
        }
    }

    return true;
}

void Evaluator::parser_test(){
    cout << "alpha is " << alpha << endl;
    cout << "beta is " << beta << endl;
    cout << "gamma is " << gamma << endl;
    cout << "lambda is " << lambda << endl;
}