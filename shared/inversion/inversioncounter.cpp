/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Frank Savattere
 * Version     : 1.0
 * Date        : 10/30/2021
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for (int i = 0; i < length - 1; i++){
        for (int j = i + 1; j < length; j++){
            if(array[i] > array[j]){
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int* scratch = new int[length];
	long inversions = mergesort(array, scratch, 0, length - 1);
	return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long count = 0;
    
    if (low < high){
        int mid = low + (high - low) / 2;
    
    count += mergesort(array, scratch, low, mid);
    count += mergesort(array, scratch, mid + 1, high);
        int L = low;
        int H = mid + 1;
    for (int i = low; i <= high; i++){
        if (L <= mid && (H > high || array[L] <= array[H])) {
            scratch[i] = array[L];
            L++;
        }
        else{
            scratch[i] = array[H];
            H++;
            count += (mid - L + 1);
        }
    }
    for (int i = low; i <= high; i++){
        array[i] = scratch[i];
    }
    
}
return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc >= 2){
        if (argc > 2){
            cerr << "Usage: ./inversioncounter [slow]" << endl;
            return 1;
        }
        string arg;
        if ((arg = argv[1]).compare("slow") != 0){
            cerr << "Error: Unrecognized option '" << arg << "'." << endl;
            return 1;
        }
    }


    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

if (values.size() > 0) {
		if (argc == 2){
			cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
		}
		else {
			cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
		}
}
	else{
		cout << "Error: Sequence of integers not received." << endl;
	return 0;
	}
}
