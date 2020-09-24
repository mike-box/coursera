#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include "vmTranslator.hpp"

using namespace std;

/*global variable*/
int g_debug = 1;
int g_jump_flag = 0;
int g_return_flag = 0;
string g_file_name;
string g_function_name;


void trace(int level,std::string text){
    if(level >= g_debug){
        cout<<text<<endl;
    }
    return;
}

void debugEnable(int level){
    g_debug = level;
}

void trimSpace(std::string &s){
    if(!s.empty()){
        int pos1 = s.find_first_not_of(" ");
        if(pos1 != string::npos) s.erase(0,pos1);
        int pos2 = s.find_last_not_of(" ");
        if(pos2 != string::npos) s.erase(pos2+1);
    }
}

void trimComments(std::string &s){
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

bool checkMnemonics(std::string & s){
    for(char c : s){
        if(!isUpper(c)) return false;
    }

    return true;
}

vector<string> split(const string & str,const char c){
    vector<string> ans;
    int n = str.size();

    for(int i = 0; i < n;){
        string curr;
        while(i < n && str[i] == c) i++;
        while(i < n && str[i] != c) curr.push_back(str[i++]);
        if(!curr.empty()) ans.push_back(curr);
    }
    
    return ans;
}

std::string binaryCode(int x,int len){
    std::string ans;
    for(int i = 0; i < len; ++i){
        ans = to_string(x%2) + ans;
        x = x>>1;
    }

    return ans;
}

int getCommandType(const std::string & command){
    int ctype = 0;
    
    if(command == "add" || command == "sub" || command == "neg" ||
       command == "eq"  || command == "gt"  || command == "lt"  ||
       command == "and" || command == "or"  || command == "not" )
       { ctype = C_ARITHMETIC;}
    else if(command == "pop")     {ctype = C_POP;}
    else if(command == "push")    {ctype = C_PUSH;}
    else if(command == "label")   {ctype = C_LABEL;}
    else if(command == "goto")    {ctype = C_GOTO;}
    else if(command == "if-goto") {ctype = C_IF;}
    else if(command == "function"){ctype = C_FUNCTION;}
    else if(command == "call")    {ctype = C_CALL;}
    else if(command == "return")  {ctype = C_RETURN;}
    else if(command == "label")   {ctype = C_LABEL;}
    else {ctype = -1;}

    return ctype;
} 

int getSegType(const std::string & command){
    int stype = 0;
    
    if(command == "argument")      {stype = SEG_ARGUMENT; }
    else if(command == "local")    {stype = SEG_LOCAL;}
    else if(command == "static")   {stype = SEG_STATIC;}
    else if(command == "constant") {stype = SEG_CONSTANT;}
    else if(command == "this")     {stype = SEG_THIS;}
    else if(command == "that")     {stype = SEG_THAT;}
    else if(command == "pointer")  {stype = SEG_POINTER;}
    else if(command == "temp")     {stype = SEG_TMP;}
    else {stype = -1;}

    return stype;
}


std::string parseCommandArithmetic(const std::string & command){
    std::string ans;
    string label;
    vector<string> arr = split(command,' ');

    /*initial*/
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "A=A-1\n";
    ans += "D=M\n";
    
    if(arr[0] == "add"){
        ans += "A=A-1\n";
        ans += "M=M+D\n";
        ans += "@SP\n";
        ans += "M=M-1\n";
    }else if(arr[0] == "sub"){
        ans += "A=A-1\n";
        ans += "M=M-D\n";
        ans += "@SP\n";
        ans += "M=M-1\n";
    }else if(arr[0] == "neg"){
        ans += "M=-D\n";
    }else if(arr[0] == "eq"){
        label = g_file_name + "." + to_string(g_jump_flag) + ".TRUE";
        ans += "A=A-1\n";
        ans += "MD=M-D\n";
        ans += "M=-1\n";
        ans += "@" + label + "\n";
        ans += "D;JEQ\n";
        ans += "@SP\n";
        ans += "A=M\n";
        ans += "A=A-1\n";
        ans += "A=A-1\n";
        ans += "M=0\n";
        ans += "("+ label + ")\n";
        ans += "@SP\n";
        ans += "M=M-1\n";
        g_jump_flag++;
    }else if(arr[0] == "gt"){
        label = g_file_name + "." + to_string(g_jump_flag) + ".TRUE";
        ans += "A=A-1\n";
        ans += "MD=M-D\n";
        ans += "M=-1\n";
        ans += "@" + label + "\n";
        ans += "D;JGT\n";
        ans += "@SP\n";
        ans += "A=M\n";
        ans += "A=A-1\n";
        ans += "A=A-1\n";
        ans += "M=0\n";
        ans += "("+ label + ")\n";
        ans += "@SP\n";
        ans += "M=M-1\n";
        g_jump_flag++;
    }else if(arr[0] == "lt"){
        label = g_file_name + "." + to_string(g_jump_flag) + ".TRUE";
        ans += "A=A-1\n";
        ans += "MD=M-D\n";
        ans += "M=-1\n";
        ans += "@" + label + "\n";
        ans += "D;JLT\n";
        ans += "@SP\n";
        ans += "A=M\n";
        ans += "A=A-1\n";
        ans += "A=A-1\n";
        ans += "M=0\n";
        ans += "("+ label + ")\n";
        ans += "@SP\n";
        ans += "M=M-1\n";
        g_jump_flag++;
    }else if(arr[0] == "and"){
        ans += "A=A-1\n";
        ans += "M=D&M\n";
        ans += "@SP\n";
        ans += "M=M-1\n";
    }else if(arr[0] == "or"){
        ans += "A=A-1\n";
        ans += "M=D|M\n";
        ans += "@SP\n";
        ans += "M=M-1\n";
    }else if(arr[0] == "not"){
        ans += "M=!D\n";
    }else return ans;
    
    return ans;
}


std::string parseCommandPush(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');
    int stype = getSegType(arr[1]);
    int pos = stoi(arr[2]);

    switch(stype){
        case SEG_ARGUMENT:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@ARG\n";
                ans += "A=M+D\n";
                ans += "D=M\n";
            }
            break;
        case SEG_LOCAL:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@LCL\n";
                ans += "A=M+D\n";
                ans += "D=M\n";
            }
            break;
        case SEG_STATIC:
            {
                ans += "@" + g_file_name + "." + to_string(pos) + "\n";
                ans += "D=M\n";
            }
            break;
        case SEG_CONSTANT:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
            }
            break;
        case SEG_THIS:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@THIS\n";
                ans += "A=M+D\n";
                ans += "D=M\n";
            }
            break;
        case SEG_THAT:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@THAT\n";
                ans += "A=M+D\n";
                ans += "D=M\n";
            }
            break;
        case SEG_POINTER:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@3\n";
                ans += "A=A+D\n";
                ans += "D=M\n";
            }
            break;
        case SEG_TMP:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@5\n";
                ans += "A=A+D\n";
                ans += "D=M\n";
            }
            break;
        default:
            break;
    }

    /*stack push add by 1*/
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "M=D\n";
    ans += "@SP\n";
    ans += "M=M+1\n";

    return ans;
}

std::string parseCommandPop(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');
    int stype = getSegType(arr[1]);
    int pos = stoi(arr[2]);

    switch(stype){
        case SEG_ARGUMENT:
            {   
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@ARG\n";
                ans += "AD=M+D\n";
            }
            break;
        case SEG_LOCAL:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@LCL\n";
                ans += "AD=M+D\n";
            }
            break;
        case SEG_STATIC:
            {
                ans += "@" + g_file_name + "." + to_string(pos) + "\n";
                ans += "D=A\n";
            }
            break;
        case SEG_THIS:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@THIS\n";
                ans += "AD=M+D\n";
            }
            break;
        case SEG_THAT:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@THAT\n";
                ans += "AD=M+D\n";
            }
            break;
        case SEG_POINTER:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@3\n";
                ans += "D=A+D\n";
            }
            break;
        case SEG_TMP:
            {
                ans += "@" + to_string(pos) + "\n";
                ans += "D=A\n";
                ans += "@5\n";
                ans += "D=A+D\n";
            }
            break;
        default:
            break;
    }

    /*stack pop add by 1*/
    ans += "@R13\n";
    ans += "M=D\n";
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "A=A-1\n";
    ans += "D=M\n";
    ans += "@R13\n"; 
    ans += "A=M\n";
    ans += "M=D\n";

    /*stack pop*/
    ans += "@SP\n";
    ans += "M=M-1\n";

    return ans;
}

std::string parseCommandLabel(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');
    string label = arr[1];
    ans += "(" + g_function_name + "$" + label +")\n";

    return ans;
}

std::string parseCommandGoto(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');
    string label = arr[1];
    ans += "@" + g_function_name + "$" + label + "\n";
    ans += "0;JMP\n";

    return ans;
}

std::string parseCommandIf(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');
    string label = arr[1];

    ans += "@SP\n";
    ans += "A=M\n";
    ans += "A=A-1\n";
    ans += "D=M\n";
    ans += "@SP\n";
    ans += "M=M-1\n";
    ans += "@" + g_function_name + "$" + label + "\n";
    ans += "D;JNE\n";

    return ans;
}

std::string parseCommandFunction(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');
    string func = arr[1];
    int pos = stoi(arr[2]);
    string label  = func;
    string repeat_start = func + ".LOCAL.start";
    string repeat_end = func + ".LOCAL.end";

    ans += "(" + label + ")\n";
    ans += "@" + to_string(pos) + "\n";
    ans += "D=A\n";
    ans += "@" + repeat_end + "\n";
    ans += "D;JMP\n";
    ans += "(" + repeat_start + ")\n";
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "M=0\n";
    ans += "@SP\n";
    ans += "M=M+1\n";
    ans += "D=D-1\n";
    ans += "@" + repeat_start + "\n";
    ans += "D;JMP\n";
    ans += "(" + repeat_end + ")\n";
    
    return ans;
}


std::string parseCommandCall(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');
    string func = arr[1];
    int pos = stoi(arr[2]);
    string label = func + ".RETURN." + to_string(g_return_flag);
    g_return_flag++;

    /*push return address*/
    ans += "@" + label + "\n";
    ans += "D=A\n";
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "M=D\n";
    ans += "@SP\n";
    ans += "M=M+1\n";

    /*push LCL*/
    ans += "@LCL\n";
    ans += "D=M\n";
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "M=D\n";
    ans += "@SP\n";
    ans += "M=M+1\n";

    /*push ARG*/
    ans += "@ARG\n";
    ans += "D=M\n";
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "M=D\n";
    ans += "@SP\n";
    ans += "M=M+1\n";

    /*push THIS*/
    ans += "@THIS\n";
    ans += "D=M\n";
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "M=D\n";
    ans += "@SP\n";
    ans += "M=M+1\n";

    /*push THAT*/
    ans += "@THAT\n";
    ans += "D=M\n";
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "M=D\n";
    ans += "@SP\n";
    ans += "M=M+1\n";

    /*ARG = SP-n-5*/
    ans += "@SP\n";
    ans += "D=M\n";
    ans += "@5\n";
    ans += "D=D-A\n";
    ans += "@" + to_string(pos) + "\n";
    ans += "D=D-A\n";
    ans += "@ARG\n";
    ans += "M=D\n";

    /*LCL = SP*/
    ans += "@SP\n";
    ans += "D=M\n";
    ans += "@LCL\n";
    ans += "M=D\n";

    /*goto f*/
    ans += "@" + func + "\n";
    ans += "0;JMP\n";

    /*return address*/
    ans += "(" + label + ")\n";

    return ans;
}

std::string parseCommandReturn(const std::string & command){
    std::string ans;
    vector<string> arr = split(command,' ');

    /*FRAME = LCL*/
    ans += "@LCL\n";
    ans += "D=M\n";
    ans += "@R6\n";
    ans += "M=D\n";

    /*RET = *(FRAME-5)*/
    ans += "@5\n";
    ans += "D=D-A\n";
    ans += "A=D\n";
    ans += "D=M\n";
    ans += "@R5\n";
    ans += "M=D\n";

    /*(*ARG) = pop()*/
    ans += "@SP\n";
    ans += "A=M\n";
    ans += "A=A-1\n";
    ans += "D=M\n";
    ans += "@SP\n";
    ans += "M=M-1\n";
    ans += "@ARG\n";
    ans += "A=M\n";
    ans += "M=D\n";
    
    /*SP = ARG+1*/
    ans += "@ARG\n";
    ans += "D=M\n";
    ans += "D=D+1\n";
    ans += "@SP\n";
    ans += "M=D\n";

    /*THAT = *(FRAME-1)*/
    ans += "@LCL\n";
    ans += "D=M\n";
    ans += "@1\n";
    ans += "D=D-A\n";
    ans += "A=D\n";
    ans += "D=M\n";
    ans += "@THAT\n";
    ans += "M=D\n";

    /*THIS = *(FRAME-2)*/
    ans += "@LCL\n";
    ans += "D=M\n";
    ans += "@2\n";
    ans += "D=D-A\n";
    ans += "A=D\n";
    ans += "D=M\n";
    ans += "@THIS\n";
    ans += "M=D\n";

    /*ARG = *(FRAME-3)*/
    ans += "@LCL\n";
    ans += "D=M\n";
    ans += "@3\n";
    ans += "D=D-A\n";
    ans += "A=D\n";
    ans += "D=M\n";
    ans += "@ARG\n";
    ans += "M=D\n";

    /*LCL = *(FRAME-4)*/
    ans += "@LCL\n";
    ans += "D=M\n";
    ans += "@4\n";
    ans += "D=D-A\n";
    ans += "A=D\n";
    ans += "D=M\n";
    ans += "@LCL\n";
    ans += "M=D\n";

    /*goto RET*/
    ans += "@R5\n";
    ans += "A=M\n";
    ans += "0;JMP\n";

    return ans;
}

string parseCommand(string & command){
    std::string assembler;
    vector<string> decode = split(command,' ');
    int ctype = getCommandType(decode[0]);

    switch(ctype){
        case C_ARITHMETIC: 
            assembler = parseCommandArithmetic(command);
            break;
        case C_PUSH:       
            assembler = parseCommandPush(command);
            break;
        case C_POP: 
            assembler = parseCommandPop(command);
            break;
        case C_LABEL: 
            assembler = parseCommandLabel(command);
            break;
        case C_GOTO: 
            assembler = parseCommandGoto(command);
            break;
        case C_IF: 
            assembler = parseCommandIf(command);
            break;
        case C_FUNCTION: 
            assembler = parseCommandFunction(command);
            break;
        case C_CALL: 
            assembler = parseCommandCall(command);
            break;
        case C_RETURN: 
            assembler = parseCommandReturn(command);
            break;
        default: 
            break;
    }

    return assembler;
}

int main(int argc, char * argv[]){
    ifstream fin;
    ofstream fout;
    int labelNum = 0;

    /*check parameter*/
    if(argc != 3) {
        trace(LEVEL_DEGBUG,"Wrong File, Bad parameter.\n\r");
        return -1;
    }

    /*initial symbol table*/
    fin.open(argv[1],std::ifstream::in);
    fout.open(argv[2],std::ifstream::out);
    if(!fin||!fout){
        trace(LEVEL_DEGBUG,"Wrong File, Bad parameter.\n\r");
        return -1;
    }

    /*parese file name*/
    vector<string> arr = split(string(argv[1]),'.');
    g_file_name = arr[0];

    /*read vm program from file*/
    string command;
    vector<string> commandSeq;
    while(getline(fin,command)){
        trimComments(command); // trim comments
        trimSpace(command); //trim space
        if(command.empty() || command.size() < 2) continue;

        /*parse each line*/
        fout<<"// "<<command<<endl;
        fout<<parseCommand(command)<<endl;
    }
        
    fin.close();
    fout.close();
    return 0;
}