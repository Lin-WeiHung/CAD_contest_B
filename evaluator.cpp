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
    int FFPinCount = 0;
    while (getline(infile, line)) {
        string feature;
        string temp;

        feature = line.substr(0, line.find(" "));
        line = line.substr(line.find(" ") + 1);

        if (feature == "Alpha") alpha = stod(line);
        else if (feature == "Beta") beta = stod(line);
        else if (feature == "Gamma") gamma = stod(line);
        else if (feature == "Lambda") lambda = stod(line);
        else if (feature == "FlipFlop") {
            Flipflop f;

            // Read flipflop bits
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setBits(stoi(temp));

            // Read flipflop name
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setName(temp);

            // Read flipflop width
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setWidth(stod(temp));

            // Read flipflop height
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            f.setHeight(stod(temp));

            // Set flipflop area
            f.setArea(f.getWidth(), f.getHeight());

            // Read flipflop pin count
            temp = line;
            f.setPinCount(stoi(temp));
            FFPinCount = stoi(temp);

            FlipFlop.push_back(f);
        }
        else if (feature == "Pin" && FFPinCount > 0) {
            Pin p;

            // Read flipflop pin name
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            p.pinName = temp;

            // Read flipflop pin X
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            p.pinX = stod(temp);

            // Read flipflop pin Y
            temp = line;
            p.pinY = stod(temp);
            FlipFlop[FlipFlop.size()-1].setFFPin(p);

            FFPinCount--;
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
            c.setPosX(stod(temp));

            // Read posY
            temp = line;
            c.setPosY(stod(temp));

            cells.push_back(c);
        }
        else if (feature == "TimingSlack") {
            // TimingSlack C1 D 1.0
            string cellName = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            line = line.substr(line.find(" ") + 1);  // Skip the pin identifier
            double slack = stod(line);

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
        FF.FFcout();
        FF.pinCout();
    }
    for(auto& cell: cells){
        cell.print();
    }
}