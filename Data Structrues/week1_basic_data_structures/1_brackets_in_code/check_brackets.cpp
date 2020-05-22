#include <iostream>
#include <stack>
#include <string>
#include <iostream>

using namespace std;
struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(Bracket(next,position+1));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.empty()||!opening_brackets_stack.top().Matchc(next)){
                cout<<position+1<<endl;
                return 0;
            }
            opening_brackets_stack.pop();
        }
    }

    // Printing answer, write your code here
    if(opening_brackets_stack.empty()){
        cout<<"Success"<<endl;
    }else{
        cout<<opening_brackets_stack.top().position;
    }
    
    return 0;
}
