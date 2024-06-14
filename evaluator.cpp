#include "header.h"
#include "evaluator.h"

Evaluator::Evaluator()
{
    alpha = 0;
    beta = 0;
    gamma = 0;
    lambda = 0;
}

vector<string> Evaluator::cut_tokens(string line)
{
    istringstream iss(line);
    string word;
    vector<string> words;
    while(iss >> word) words.push_back(word);
    return words;
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

            flipflop.push_back(f);
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
            flipflop[flipflop.size()-1].setFFPin(p);

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

            input_cells.push_back(c);
        }
        else if (feature == "TimingSlack") {
            // TimingSlack C1 D 1.0
            string cellName = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            line = line.substr(line.find(" ") + 1);  // Skip the pin identifier
            double slack = stod(line);

            for (auto& c : input_cells) {
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

bool Evaluator::parser_outfile(char* output_file)
{
    string temp1, temp2;
    string line_vec1, line_vec2;

    cout << "Start reading " << output_file << endl;
    fstream outfile(output_file, ios::in); 
    if (!outfile) 
    {
        cout << "Input file " << output_file << " doesn't exist ..." << endl;
        return false;
    }
    Cell cell; 
    string line;
    while (getline(outfile, line)) 
    {
        vector<string>tempt;
        tempt=cut_tokens(line);
        
        if(tempt[0]=="Inst" && tempt.size()==5)
        {
            cell.setCellName(tempt[1]);
            cell.setFFType(tempt[2]);
            cell.setPosX(stof(tempt[3]));
            cell.setPosY(stof(tempt[4]));
            output_cells.push_back(cell);
        } 
        else if(tempt.size()==3)
        {   
            line_vec1 = tempt[0];
            temp1 = line_vec1.substr(0, line.find("/"));  //temp1:origin ff name 
            line_vec1 = line_vec1.substr(line.find("/") + 1); //line_vec1:origin ff pin
            
            line_vec2 = tempt[2];
            temp2 = line_vec2.substr(0, line.find("/"));  //temp2:new match ff name 
            line_vec2 = line_vec2.substr(line.find("/") + 1); //line_vec2:new match ff pin
            
            match_data[temp1].new_ff=temp2;
            match_data[temp1].pair[line_vec1]=line_vec2;
        }
    }

    return true;
}

void Evaluator::parser_test(){
    cout << "Start printing data for test: " << endl << endl;

    cout << "alpha is " << alpha << endl;
    cout << "beta is " << beta << endl;
    cout << "gamma is " << gamma << endl;
    cout << "lambda is " << lambda << endl;

    cout << endl << "--------------------FF_lib--------------------" << endl << endl;
    for(auto& FF: flipflop){
        FF.FFcout();
        FF.pinCout();
    }
    cout << endl << "--------------------input_cells--------------------" << endl << endl;
    for(auto& cell: input_cells){
        cell.print();
    }
    cout << endl << "--------------------output_cells--------------------" << endl << endl;
    for(auto& cell: output_cells){
        cell.print();
    }
    for (map<string, pair_data>::const_iterator it = match_data.begin(); it != match_data.end(); ++it) {
        cout << "origin ff : " << it->first << ", new ff: " << it->second.new_ff << endl;
        for (map<string, string>::const_iterator sub_it = it->second.pair.begin(); sub_it != it->second.pair.end(); ++sub_it) {
            cout << "\t origin pin : " << sub_it->first << ", after mapping pin : " << sub_it->second << endl;
        }
    }
}

