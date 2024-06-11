#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "evaluator.h"
using namespace std;


evaluator::evaluator()
{
    alpha = 0;
    beta = 0;
    gamma = 0;
    lambda = 0;
}

void evaluator::parser()
{
    string line;

    file.open("testcase1.txt");

    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
    }

    while (getline(file, line)) {
        string feature;
        string temp;
        flipflop f;

        //line == "FlipFlop 1 FF1 5.0 10.0 3"
        feature = line.substr(0, line.find(" "));
        line = line.substr(line.find(" ") + 1);

        if (feature == "Alpha") alpha = stof(feature);
        else if (feature == "Beta") beta = stof(feature);
        else if (feature == "Gamma") gamma = stof(feature);
        else if (feature == "Lambda") lambda = stof(feature);
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
}