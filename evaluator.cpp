#include "header.h"
#include "evaluator.h"

Evaluator::Evaluator()
{
    alpha = 0;
    beta = 0;
    gamma = 0;
    lambda = 0;
    dis_co = 0;
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
    int GatePinCount = 0;
    while (getline(infile, line)) {
        string feature;
        string temp;

        feature = line.substr(0, line.find(" "));
        line = line.substr(line.find(" ") + 1);

        if (feature == "Alpha") alpha = stod(line);
        else if (feature == "Beta") beta = stod(line);
        else if (feature == "Gamma") gamma = stod(line);
        else if (feature == "Lambda") lambda = stod(line);
        else if (feature == "DisplacementDelay") dis_co = stod(line);
        //////////////////////////////////////////FlipFlop Data//////////////////////////////////
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
        /////////////////////////////////////////////FlipFlop Data///////////////////////////////
        /////////////////////////////////////////////Gate Data///////////////////////////////////
        else if (feature == "Gate") {
            Gate g;

            // Read gate name
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            g.setName(temp);

            // Read gate width
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            g.setWidth(stod(temp));

            // Read gate height
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            g.setHeight(stod(temp));

            // Set gate area
            g.setArea(g.getWidth(), g.getHeight());

            // Read gate pin count
            temp = line;
            g.setPinCount(stoi(temp));
            GatePinCount = stoi(temp);

            gate.push_back(g);
        }
        else if (feature == "Pin" && GatePinCount > 0) {
            Pin_g p_g;

            // Read gate pin name
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            p_g.pinName = temp;

            // Read gate pin X
            temp = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            p_g.pinX = stod(temp);

            // Read gate pin Y
            temp = line;
            p_g.pinY = stod(temp);
            gate[gate.size()-1].setGatePin(p_g);

            GatePinCount--;
        }
        ///////////////////////////////////////////Gate Data////////////////////////////////////////
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
        else if(feature == "GatePower"){
            Flipflop f;
            string ffName = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            double power = stod(line);
            for(auto& f : flipflop){
                if(f.getName() == ffName){
                    f.setPower(power);
                    break;
                }
            }
            for(auto& f : flipflop){
                for(auto& c : input_cells){
                    if(f.getName()==c.getFFType()){
                        c.setPower(f.getPower());
                        c.setArea(f.getArea());
                    }
                }
            }
        }
        ///////////////////////////////////////////QpinDelay///////////////////////////////////
        else if(feature == "QpinDelay"){
            Flipflop f;
            string ffName = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            double qpindelay = stod(line);
            for(auto& f : flipflop){
                if(f.getName() == ffName){
                    f.setQpinDelay(qpindelay);
                    break;
                }
            }
            for(auto& c : input_cells){
                for(auto& f : flipflop){
                    if(f.getName()==c.getFFType()){
                        c.setQpinDelay(f.getQpinDelay());
                    }
                }
            }
        }
        ///////////////////////////////////////////QpinDelay///////////////////////////////////
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

    for(auto& f : flipflop){
        for(auto& c : output_cells){
            if(f.getName()==c.getFFType()){
                c.setPower(f.getPower());
                c.setArea(f.getArea());
                c.setQpinDelay(f.getQpinDelay());
            }
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
    cout << "displacement coefficient is " << dis_co << endl;

    cout << endl << "--------------------FF_lib--------------------" << endl << endl;
    for(auto& FF: flipflop){
        FF.FFcout();
        FF.pinCout();
    }
    for(auto& Gate: gate){
        Gate.GateCout();
        Gate.pinCout();
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

float Evaluator::CostFunction(){
    float power_output=0, power_input=0;
    float area_output=0,  area_input=0;
    float QPinDelay_output=0, QPinDelay_input=0;
    float cost_function = 0;
    for(auto& c : input_cells){
        power_input = c.getPower() + power_input;
        area_input = c.getArea() + area_input;
        QPinDelay_input = c.getQpinDelay() + QPinDelay_input;
    }
    cout<<"------------------------------------input cells ------------------------------------"<<endl
        <<"total power: "<< power_input
        <<"        total area: "<< area_input
        <<"        total QPinDelay: "<< QPinDelay_input <<endl;

    for(auto& c : output_cells){
        power_output = c.getPower() + power_output;
        area_output = c.getArea() + area_output;
        QPinDelay_output = c.getQpinDelay() + QPinDelay_output;
    }
    cout<<"------------------------------------output cells ------------------------------------"<<endl
        <<"total power: "<< power_output
        <<"        total area: "<< area_output
        <<"        total QPinDelay: "<< QPinDelay_output <<endl;

    cost_function = alpha*(QPinDelay_output - QPinDelay_input + dis_co * Displacement()) + 
                    beta*(power_output)+
                    gamma*(area_output);
    return cost_function;
    
}

float Evaluator::Displacement(){
    float dis_total = 0;
    for (map<string, pair_data>::const_iterator it = match_data.begin(); it != match_data.end(); ++it) {
        string cell_input = it->first;
        string cell_output = it->second.new_ff;
        float input_x, input_y, output_x, output_y;
        float diff_x, diff_y;
        float diff_total = 0;
        for (map<string, string>::const_iterator sub_it = it->second.pair.begin(); sub_it != it->second.pair.end(); ++sub_it) {
            input_x = AbsCordinate(cell_input, sub_it->first, "input").first;
            input_y = AbsCordinate(cell_input, sub_it->first, "input").second;
            output_x = AbsCordinate(cell_output, sub_it->second, "output").first;
            output_y = AbsCordinate(cell_output, sub_it->second, "output").second;
            diff_x = output_x - input_x;
            diff_y = output_y - input_y;
            cout<<"-------------------------- one pin matching data --------------------------"<<endl;
            cout<<"origin pin : " << sub_it->first <<" in cell : "<<cell_input<< ", after mapping pin : " << sub_it->second <<" in cell : "<<cell_output<<endl;
            cout<<"input pin x: " << input_x <<" input pin y: " << input_y << " output pin x: " << output_x << " output pin y: " <<output_y<<endl;
            cout<<"-->  difference in x-axis: "<< std::fabs(diff_x) << "  difference in y-axis: "<<std::fabs(diff_y) <<endl;
            dis_total = fabs(diff_x) + fabs(diff_y) + dis_total;
        }
    }
    return dis_total;
}

//calculate the manhattan distance between origin and after
//obtain data from the input_cells(find out the ff types), output_cells, and ff library
//cell_type : input_cells or output_cells
pair<float, float> Evaluator::AbsCordinate(string cell_name, string pin_name, string cell_type){  
    float abs_x, abs_y;
    if(cell_type == "input"){
        for(auto& cell: input_cells){
            if(cell.getCellName() == cell_name){
                for(auto& FF:flipflop){
                    if(FF.getName() == cell.getFFType()){
                        pair<float, float> result = FF.getPinCor(cell.getFFType(), pin_name);
                        abs_x = cell.getPosX()+result.first;
                        abs_y = cell.getPosY()+result.second;
                    }
                      
                } 
            }
        }
    }
    else if(cell_type == "output"){
        for(auto& cell: output_cells){
            if(cell.getCellName() == cell_name){
                for(auto& FF:flipflop){
                    if(FF.getName() == cell.getFFType()){
                        pair<float, float> result = FF.getPinCor(cell.getFFType(), pin_name);
                        abs_x = cell.getPosX()+result.first;
                        abs_y = cell.getPosY()+result.second;
                    }
                } 
            }
        }
    }
    return make_pair(abs_x, abs_y);
}
