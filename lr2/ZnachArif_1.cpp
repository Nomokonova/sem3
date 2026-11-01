#include <iostream>
#include <string>
#include <cctype>
#include "Stack.h"
using namespace std;

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0;
}

int runOp(int a, int b, char op){
    if (op =='+') return a + b;
    if( op == '-') return a - b;
    if (op == '*') return a * b;
    return 0;
}

int main(){
    string str;
    getline(cin, str);
    Stack<int> value;
    Stack<char> ops;

    bool error = false;
    bool waitOperand = true;

    for(int i=0; i<str.length(); i++){
        char ch =str[i];
        if (ch == ' ') continue;

        if(isdigit(ch)){
            int val = 0;
            while(i < str.length() && isdigit(str[i])){
                val = val*10 + (str[i] - '0');
                i++;
            }
            i--;
            value.push(val);
            waitOperand = false;
        }
        else if(ch == '('){
            ops.push(ch);
            waitOperand = true;
        }
        else if(ch == ')'){
            if(waitOperand){
                error = true;
                break;
            }
            while(ops.empty()== false && ops.peek()!= '('){
                if(value.empty()){error = true; break;}
                int b = value.pop();
                int a = value.pop();
                char op = ops.pop();
                value.push(runOp(a,b,op));
            }
            if(ops.empty()){error = true; break;}
            ops.pop();
            waitOperand = false;
        }
        else if(ch == '+' || ch == '-' || ch == '*'){
            if(waitOperand){
                error = true;
                break;
            }
            while(ops.empty() == false && getPriority(ops.peek()) >= getPriority(ch)){
                if(value.empty()){error = true; break;}
                int b = value.pop();
                int a = value.pop();
                char op = ops.pop();
                value.push(runOp(a,b,op));
            }
            ops.push(ch);
            waitOperand = true;
        }
        else{
            error = true;
            break;
        }
    }
    while(!error && !ops.empty()){
        if(value.empty()){error = true; break;}
        if(ops.peek() == '('){error = true; break;}

        int b = value.pop();
        int a = value.pop();
        char op = ops.pop();
        value.push(runOp(a,b,op));
    }
    if(error || value.empty()){
        cout << "error" << endl;
    }
    else{
        cout << value.peek() << endl;
    }
    return 0;
}
