#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;

#define DEGBUG_LEVEL 10
#define INFO_LEVEL 1
#define WARNINT_LEVEL 2
#define ERROR_LEVEL 3
#define MAX_ADDR 190000
#define START_ADDR_OPEN 16
#define MEMORY_ADDR_LEN 15

int debug = 1;

void trace(int level,string text){
    if(debug){
        cout<<text<<endl;
    }
    return;
}

void trimSpace(string &s){
    if(!s.empty()){
        int pos1 = s.find_first_not_of(" ");
        if(pos1 != string::npos) s.erase(0,pos1);
        int pos2 = s.find_last_not_of(" ");
        if(pos2 != string::npos) s.erase(pos2+1);
    }
}

void trimComments(string &s){
    if(!s.empty()){
        int pos = s.find_first_of("//");
        if(pos != string::npos) s.erase(pos);
    }
}

bool isDigit(char c){
    return c >= '0' && c <= '9';
}

bool isUpper(char c){
    return c >= 'A' && c <= 'Z';
}

bool isNumber(string & s){
    long long sum = 0;

    if(s[0] == '0' && s.size() != 1) return false;
    for(int i = 0; i < s.size(); ++i){
        if(!isDigit(s[i])) return false;
        sum = sum*10 + s[i] - '0';
        if(sum > MAX_ADDR) return false;
    }

    return true;
}

bool checkMnemonics(string & s){
    for(char c : s){
        if(!isUpper(c)) return false;
    }

    return true;
}

string binaryCode(int x,int len){
    string ans;
    for(int i = 0; i < len; ++i){
        ans = to_string(x%2) + ans;
        x = x>>1;
    }

    return ans;
}

bool initPredefTable(map<string,int> & symbolTable){
    /*Predefined Symbols*/
    for(int i = 0; i < 16; ++i){
        symbolTable["R" + to_string(i)] = i;
    }
    
    symbolTable["SP"] = 0;
    symbolTable["LCL"] = 1;
    symbolTable["ARG"] = 2;
    symbolTable["THIS"] = 3;
    symbolTable["THAT"] = 4;
    symbolTable["SCREEN"] = 16384;
    symbolTable["KBD"] = 24576;

    return true;
}

bool initJumpTable(map<string,string> & jumpTable){
    jumpTable[""] = "000";
    jumpTable["JGT"] = "001";
    jumpTable["JEQ"] = "010";
    jumpTable["JGE"] = "011";
    jumpTable["JLT"] = "100";
    jumpTable["JNE"] = "101";
    jumpTable["JLE"] = "110";
    jumpTable["JMP"] = "111";
    return true;
}

bool initDestTable(map<string,string> & destTable){
    destTable[""] = "000";
    destTable["M"] = "001";
    destTable["D"] = "010";
    destTable["MD"] = "011";
    destTable["A"] = "100";
    destTable["AM"] = "101";
    destTable["AD"] = "110";
    destTable["AMD"] = "111";
    return true;
}

bool initCompTable(map<string,string> & compTable){
    compTable["0"]   = "0101010";
    compTable["1"]   = "0111111";
    compTable["-1"]  = "0111010";
    compTable["D"]   = "0001100";
    compTable["A"]   = "0110000";
    compTable["M"]   = "1110000";
    compTable["!D"]  = "0001101";
    compTable["!A"]  = "0110001";
    compTable["!M"]  = "1110001";
    compTable["-D"]  = "0001111";
    compTable["-A"]  = "0110011";
    compTable["-M"]  = "1110011";
    compTable["D+1"] = "0011111";
    compTable["A+1"] = "0110111";
    compTable["M+1"] = "1110111";
    compTable["D-1"] = "0001110";
    compTable["A-1"] = "0110010";
    compTable["M-1"] = "1110010";
    compTable["D+A"] = "0000010";
    compTable["D+M"] = "1000010";
    compTable["D-A"] = "0010011";
    compTable["D-M"] = "1010011";
    compTable["A-D"] = "0000111";
    compTable["M-D"] = "1000111";
    compTable["D&A"] = "0000000";
    compTable["D&M"] = "1000000";
    compTable["D|A"] = "0010101";
    compTable["D|M"] = "1010101";
    return true;
}

int main(int argc, char * argv[]){
    ifstream fin;
    ofstream fout;
    int currAddr = START_ADDR_OPEN;
    int currLine = 0;
    
    map<string,int>  symbolTable;
    map<string,int>   labelTable;
    map<string,string> jumpTable;
    map<string,string> destTable;
    map<string,string> compTable;

    /*initial symbol table*/
    initPredefTable(symbolTable);
    initJumpTable(jumpTable);
    initDestTable(destTable);
    initCompTable(compTable);
        
    if(argc != 3) {
        trace(ERROR_LEVEL,"Wrong File, Bad parameter.\n\r");
        return -1;
    }

    fin.open(argv[1],std::ifstream::in);
    fout.open(argv[2],std::ifstream::out);
    if(!fin||!fout){
        trace(ERROR_LEVEL,"Wrong File, Bad parameter.\n\r");
        return -1;
    }

    /*read assembler program from file*/
    /*parse label*/
    string assembler;
    vector<string> assemblerArr;
    while(getline(fin,assembler)){
        trimComments(assembler); // trim comments
        trimSpace(assembler); //trim space
        if(assembler.empty() || assembler.size() < 2) continue;

        if(assembler[0] == '('){
            /*parse Label*/
            if(assembler.back() != ')'){
                trace(ERROR_LEVEL,"Wrong Assembler, we need right ')'.\n\r");
                return -1;
            }
            if(assembler.size() <= 2){
                trace(ERROR_LEVEL,"Wrong Assembler, label can not be empty!\n\r");
                return -1;
            }
            string label = assembler.substr(1,assembler.size()-2);
            labelTable[label] = currLine;
        }else{
            assemblerArr.push_back(assembler);
            currLine++;
        }
    }
    
    for(auto v : assemblerArr){
        /*parse A instruction*/
        string instruction;

        if(v[0] == '@'){
            instruction = "0";
            string var = v.substr(1);
            int address = 0;

            if(isNumber(var)){
                address = stoi(var);
            }else{
                if(symbolTable.count(var)){
                    address = symbolTable[var];
                }else if(labelTable.count(var)){
                    address = labelTable[var];
                }else{
                    address = currAddr++;
                    symbolTable[var] = address;
                }
            }
            instruction += binaryCode(address,MEMORY_ADDR_LEN);
        }else{
            /*parse C instruction*/
            instruction = "111";
            string dest = "";
            string comp = "";
            string jump = "";

            int pos1 = v.find_first_of(";");
            int pos2 = v.find_first_of("=");

            if(pos1 == string::npos && pos2 == string::npos){
                trace(ERROR_LEVEL,"Wrong Assembler, we need the right command!\n\r");
                return -1;
            }

            if(pos1 == string::npos){
                jump = "";
                if(pos2 != string::npos){
                    dest = v.substr(0,pos2);
                    comp = v.substr(pos2+1);
                }
            }else{
                jump = v.substr(pos1+1);
                if(pos2 != string::npos){
                    dest = v.substr(0,pos2);
                    comp = v.substr(pos2+1,pos1-pos2-1);
                }else{
                    comp = v.substr(0,pos1);
                }
            }

            if(!jumpTable.count(jump)||
               !compTable.count(comp)||
               !destTable.count(dest)){
                   trace(ERROR_LEVEL,"Wrong Assembler, we need the right command!\n\r");
                   return -1;
            }

            instruction += compTable[comp] + destTable[dest] + jumpTable[jump];
        }
        fout<<instruction<<endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}