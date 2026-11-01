#include <iostream>
#include "array.h"
using namespace std;

bool isMatch(Array& str, Array& pattern){
    int s = 0;
    int p = 0;
    int starIdx = -1;
    int match = 0;

    int strLen = str.getSize();
    int patLen = pattern.getSize();

    while(s < strLen){
        if(p < patLen && (pattern.getString(p) == "?" || pattern.getString(p) == str.getString(s))){
            s++;
            p++;
        }
        else if(p < patLen && pattern.getString(p) == "*"){
            starIdx = p;
            match = s;
            p++;
        }
        else if(starIdx != -1){
            p = starIdx + 1;
            match++;
            s = match;
        }
        else{
            return false;
        }
    }

    while(p < patLen && pattern.getString(p) == "*"){
        p++;
    }
    return p == patLen;
}

int main(){
    string strInput, patInput;
    cout << "Enter string: ";
    cin >> strInput;
    cout << "Enter pattern: ";
    cin >> patInput;

    Array str;
    for(char c : strInput){
        str.pushBack(string(1, c));
    }
    Array pattern;
    for(char c : patInput){
        pattern.pushBack(string(1, c));
    }
     if (isMatch(str, pattern)) {
        cout << "Соответствует" << endl;
    } else {
        cout << "Не соответствует" << endl;
    }
    return 0;
}