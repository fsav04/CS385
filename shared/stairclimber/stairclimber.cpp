/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Frank Savattere
 * Date        : 10/1/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> steps;

    int max = 3;

    if(num_stairs == 0){

        vector<vector<int>> zero = {{}};

        return zero;
    }

    for(int i = 1; i <= max; i++){

        if(num_stairs >= i){

            vector<vector<int>> current = get_ways(num_stairs - i);

            for(auto step = current.begin(); step != current.end(); step++){

                (*step).insert((*step).begin(), i);

                steps.push_back((*step));
            }
        }
    }
    return steps;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    string numlim = to_string(ways.size() - 1);

    int wsize = numlim.length();

    for (unsigned int i = 0; i < ways.size(); i++){
        cout << setw(wsize) << (i+1) << ". " << setw(1);

        cout << "[";

        vector<int> current = ways[i];

        for (unsigned int j = 0; j < current.size(); j++){

            if (j != current.size() - 1){

                cout << current[j] << ", ";

            }else{

                cout << current[j];
            }
        }
        cout << "]" << endl; 
    }
}

int main(int argc, char * const argv[]) {
    int limit;

    istringstream iss;

    if (argc < 2 || argc > 2){
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }

    else{
        iss.str(argv[1]);
        if(!(iss >> limit) || limit <= 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
        }
    
        else{

            iss.clear();

            get_ways(limit);

            if (limit == 1){
                cout << "1 way to climb " << limit << " stair." << endl;
                display_ways(get_ways(limit));
            }
            else{
                cout << get_ways(limit).size() << " ways to climb " << limit << " stairs." << endl;

                display_ways(get_ways(limit));

            }
        }
    }
    return 0;
}
