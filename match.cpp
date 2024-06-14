#include "header.h"
#include "match.h"
Match match;
Match::Match( ){ }

bool Match::parser_outfile(char* output_file)
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
    Cell c1; 
    string line;
    while (getline(outfile, line)) 
    {
        vector<string>tempt;
        tempt=Match::cut_tokens(line);
        for(int i=0; i<tempt.size();i++){cout<<tempt[i]<<"  ";}
        cout<<endl;
        if(tempt[0]=="CellInst" && tempt.size()==2)
        {
            cell_num=stoi(tempt[1]);
            cout<<" cell instance num : "<<cell_num<<endl;  
        }
        
        if(tempt[0]=="Inst" && tempt.size()==5)
        {
            c1.setCellName(tempt[1]);
            c1.setFFType(tempt[2]);
            c1.setPosX(stof(tempt[3]));
            c1.setPosY(stof(tempt[4]));
            newFF_list.push_back(c1);
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

void Match::parser_test()
{
    cout<<"total inst num : "<<cell_num<<endl;
    for(auto& cell: newFF_list){
        cell.print();
    }
    for (map<string, pair_data>::const_iterator it = match_data.begin(); it != match_data.end(); ++it) {
        cout << "origin ff : " << it->first << ", new ff: " << it->second.new_ff << endl;
        for (map<string, string>::const_iterator sub_it = it->second.pair.begin(); sub_it != it->second.pair.end(); ++sub_it) {
            cout << "\t origin pin : " << sub_it->first << ", after mapping pin : " << sub_it->second << endl;
        }
    }
}

vector<string> Match::cut_tokens(string line)
{
    istringstream iss(line);
    string word;
    vector<string> words;
    while(iss >> word) words.push_back(word);
    return words;
}