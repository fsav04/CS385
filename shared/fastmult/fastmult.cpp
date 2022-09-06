#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int toint(char a){
    int ia = a - '0';
    return ia;
}

string add(const string& a, const string& b){
    int value = 0;
    int carry = 0;
    string result = "";
    for (size_t i = a.length(); i > 0; i--){
        value = toint(a[i - 1]) + toint(b[i - 1]) + carry;
        carry = value / 10;
        if(value > 9){
            value = value - 10;
        }
        result += to_string(value);
    }
    if(carry != 0){
        result += to_string(carry);
    }
    reverse(result.begin(), result.end());
    return result;
}

string subtract(const string& a, const string& b){
    int value = 0;
    int carry = 0;
    string result = "";
    for (size_t i = a.length(); i > 0; i--){
        value = toint(a[i - 1]) - toint(b[i - 1]) - carry;
        if(value < 0){
            carry = 1 ;
            value += 10;
        }
        else{
            carry = 0;
        }
        result += to_string(value);
    }
    /*if(carry != 0){
        result += to_string(carry);
    }*/
    reverse(result.begin(), result.end());
    return result;
}

string multiply(const string& a, const string& b){
    int counta = 0;
    int countb = 0;
    int total = 0;
    //int countb = 0;
    for(size_t i = 0; i < a.length(); i++){
        counta += toint(a[i]) * 10 * i;
        countb += toint(b[i]) * 10 * i;
        total = counta * countb;
        return to_string(total);
    }
    return "";
}

int main(int argc, char *argv[]){
    string a = argv[1];
    string b = argv[2];
    if(argv[1] < argv[2]){
        int temp = strlen(argv[2]) - strlen(argv[1]);
        a.insert(0, temp, '0');
    }
    if(argv[1] > argv[2]){
        int temp = strlen(argv[1]) - strlen(argv[2]);
        b.insert(0, temp, '0');
    }
    
    return 0;
}