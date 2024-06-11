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

        feature = line.substr(0, line.find(" "));
        line = line.substr(line.find(" ") + 1);

        if (feature == "Alpha") alpha = stof(line);
        else if (feature == "Beta") beta = stof(line);
        else if (feature == "Gamma") gamma = stof(line);
        else if (feature == "Lambda") lambda = stof(line);
        else if (feature == "FlipFlop") {
            Flipflop f;

            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setBits(stoi(temp));

            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setName(temp);

            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setWidth(stof(temp));

            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setHeight(stof(temp));

            f.setArea(f.getWidth(), f.getHeight());

            temp = line;
            f.setPinCount(stoi(temp));

            f.coutt();

            FlipFlop.push_back(f);
        }
        else if (feature == "Inst") {
            Cell c;

            // Read cell name
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            c.setCellName(temp);

            // Read FF type
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            c.setFFType(temp);

            // Read posX
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            c.setPosX(stof(temp));

            // Read posY
            temp = line;
            c.setPosY(stof(temp));

            cells.push_back(c);
        }
        else if (feature == "TimingSlack") {
            // TimingSlack C1 D 1.0
            string cellName = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            line = line.substr(line.find(" ") + 1);  // Skip the pin identifier
            float slack = stof(line);

            for (auto& c : cells) {
                if (c.getCellName() == cellName) {
                    c.setTimingSlack(slack);
                    break;
                }
            }
        }
        // Handle other features here
    }

    return true;
}

void Evaluator::parser_test(){
    cout << "alpha is " << alpha << endl;
    cout << "beta is " << beta << endl;
    cout << "gamma is " << gamma << endl;
    cout << "lambda is " << lambda << endl;

    for(auto& FF: FlipFlop){
        FF.coutt();
    }
    for(auto& cell: cells){
        cell.print();
    }
}