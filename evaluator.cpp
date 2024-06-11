#include "header.h"
#include "evaluator.h"

Evaluator::Evaluator()
{
    alpha = 0;
    beta = 0;
    gamma = 0;
    lambda = 0;
}

void Evaluator::parser()
{
    string line;

    file.open("testcase1.txt");

    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
    }

    while (getline(file, line)) {
        string feature;
        string temp;
        Flipflop f;

        //line == "FlipFlop 1 FF1 5.0 10.0 3"
        feature = line.substr(0, line.find(" "));
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
}
