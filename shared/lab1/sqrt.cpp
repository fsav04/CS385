/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Frank Savattere
 * Version : 1.0
 * Date    : September 1, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;
double sqrt(double num, double epsilon){
    double last_guess = num;
    double next_guess = (last_guess + num/last_guess) / 2;
    //list of exceptions
    if(num < 0){
        return numeric_limits<double>::quiet_NaN();
    }
    if(num == 0){
        return num;
    }
    if(num == 1){
        return num;
    }
    while(!(abs(last_guess - next_guess) <= epsilon)){
        last_guess = next_guess;
        next_guess = (last_guess + (num/last_guess)) / 2;     
    }
    return next_guess;
}
int main(int argc, char* argv[]){
    double num;
    double epsilon;
    istringstream iss; 
    if(argc > 3){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }
    if(argc < 2){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if(!(iss >> num)){
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }
    if(argc == 3){
    iss.clear();
    iss.str(argv[2]);
        if(!(iss >> epsilon) || (epsilon <=0)){
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    }
        else{
            epsilon = 1e-7;
        }
    
    cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;

    return 0;
}