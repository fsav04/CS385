#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;


long num_vertices;
long INF = numeric_limits<long>::max();
long** matrix;
long** intermediate;

int len(long vert){
    if(vert == 0){
        return 1;
    }
    int count = 0;
    while(vert != 0){
        vert = vert/10;
        count++;

    }
    return count;

}

void InitializeMatrix() {

	//Initialize matrix with original matrix
	matrix = new long*[num_vertices];
	for(int i = 0; i < num_vertices; i++) {
		matrix[i] = new long[num_vertices];
		/*for(int j = 0; j < num_vertices; j++) {
			matrix[i][j] = matrix[i][j];
		}*/
	}

	//Initialize intermediate with INF
	intermediate = new long*[num_vertices];
	for(int i = 0; i < num_vertices; i++) {
		intermediate[i] = new long[num_vertices];
		fill_n(intermediate[i], num_vertices, INF);
	}

}





void floyds(long** matrix) {
	for(int k = 0; k < num_vertices; k++) {
		for(int i = 0; i < num_vertices; i++) {
			for(int j = 0; j < num_vertices; j++) {
				if(matrix[i][k] != INF && matrix[k][j] != INF && matrix[i][j] > (matrix[i][k] + matrix[k][j])) {
					matrix[i][j] = matrix[i][k] + matrix[k][j];
					intermediate[i][j] = k;
				}
				if(i == j) {
					matrix[i][j] = 0;
					intermediate[i][j] = INF;
				}
			}
		}
	}
}


void diagnole(){
    matrix = new long*[num_vertices];
				for (int i = 0; i < num_vertices; ++i) {
					matrix[i] = new long[num_vertices];
					fill(matrix[i], matrix[i] + num_vertices, INF);
				}
				for (int i = 0; i < num_vertices; ++i) {
					matrix[i][i] = 0;

                }
}

/** 
 * Displays the matrix on the screen formatted as a table. 
 */ 
void display_table(long** const matrix, const string &label, const bool use_letters = false) { 
    cout << label << endl; 
    long max_val = 0; 
    for (int i = 0; i < num_vertices; i++) { 
        for (int j = 0; j < num_vertices; j++) { 
            long cell = matrix[i][j]; 
            if (cell < INF && cell > max_val) { 
                max_val = matrix[i][j]; 
            } 
        } 
    } 
 
    int max_cell_width = use_letters ? len(max_val) : 
            len(max(static_cast<long>(num_vertices), max_val)); 
    cout << ' '; 
    for (int j = 0; j < num_vertices; j++) { 
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A'); 
    } 
    cout << endl; 
    for (int i = 0; i < num_vertices; i++) { 
        cout << static_cast<char>(i + 'A'); 
        for (int j = 0; j < num_vertices; j++) { 
            cout << " " << setw(max_cell_width); 
            if (matrix[i][j] == INF) { 
                cout << "-"; 
            } else if (use_letters) { 
                cout << static_cast<char>(matrix[i][j] + 'A'); 
            } else { 
                cout << matrix[i][j]; 
            } 
        } 
        cout << endl; 
    } 
    cout << endl; 
} 



int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        istringstream iss;
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            
            if(line_number == 1){
                iss.str(line);
                if(!(iss >> num_vertices)|| num_vertices < 1 || num_vertices > 26){
                    cerr << "Error: Invalid number of vertices " <<"'" << line <<"'" << " on line 1" << "." << endl;
                    return 1;
                }
                
                iss.clear();
            
                //diagnole();
		}
            else{
                //iss.str(line[4]);
        istringstream ss(line);
        // Starting vertex
        string start_s;
        ss >> start_s;
        if (start_s.length() > 1){
            cerr << "Error: Starting vertex '" << start_s << "' on line " << line_number
                << " is not among valid values A-" << char('A' + num_vertices-1) << "."<< endl;
            return -1;
        }
        char start = start_s.at(0);
        if (start < 'A' || start >= 'A' + num_vertices) {
            cerr << "Error: Starting vertex '" << start << "' on line " << line_number
                << " is not among valid values A-" << char('A' + num_vertices-1) << "."<< endl;
            return -1;
        }   

        // Ending vertex
        string end_s;
        ss >> end_s;
        if (end_s.length() > 1){
            cerr << "Error: Ending vertex '" << end_s << "' on line " << line_number
                << " is not among valid values A-" << char('A' + num_vertices-1) << "."<< endl;
            return -1;
        }
        char end = end_s.at(0);
        if (end < 'A' || end >= 'A' + num_vertices || start == end){
            cerr << "Error: Ending vertex '" << end << "' on line " << line_number
                << " is not among valid values A-" << char('A' + num_vertices-1) << "."<< endl;
            return -1;
        }

        // Weight between Start and End Vertices
        string weight_s;
        ss >> weight_s;
        if (!ss){
            cerr << "Error: Invalid edge data '" << start << " "<< end << "' on line " << line_number << "."<< endl;
            return -1;
        }
        for (size_t i = 0; i < weight_s.length(); i++){
            if (weight_s.at(i) < '0' || weight_s.at(i) > '9'){
                cerr << "Error: Invalid edge weight '" << weight_s << "' on line " << line_number << "."<< endl;
                return -1;
            }
        }
        long weight = stol(weight_s);
        if (weight == 0){
            cerr << "Error: Invalid edge weight '" << weight << "' on line " << line_number << "."<< endl;
            return -1;
        }

        

            }

            

            





            
            /*istringstream iss;
            iss.str(line);*/
            
            

            /*if(num_vertices < 1 || num_vertices > 26){
                cerr << "Error: Invalid number of num_vertices " <<"'" << line <<"'" << " on line 1" << "." << endl;
                return 1;

            }*/
            //iss.clear();


            //cout << line_number << ":\t" << line << endl;
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    
    
    floyds(matrix);
    display_table(matrix, "Distance matrix");
    display_table(matrix, "Path length");
    display_table(intermediate, "Intermediate length", true);

    

    return 0;
}