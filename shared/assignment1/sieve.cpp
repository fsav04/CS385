/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Frank Savattere
 * Date        : 9/13/21
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    num_primes_ = count_num_primes();
}

void PrimesSieve::display_primes() const {
    int n = limit_;
    while(!(is_prime_[n] == true)){
        n = n - 1;
    }
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(n), primes_per_row = 80 / (max_prime_width + 1);
		int count2 = 0; //given

        //if the number of primes in num_primes_ is under 80 characters
		if (num_primes_ <= primes_per_row) {
			for (int i = 2; i <= limit_; i++) {
				if (is_prime_[i] == true && i  != n) {
					cout << i << " ";
				} else if(i == n){
                    cout << i;
                }
			}
		} else {  //when num_primes_ has too many characters to fit on one single line
			
            for (int i = 2; i <= limit_; i++) {
                if(is_prime_[i] == true){
                cout << setw(max_prime_width);
                    cout << i;
                    count2++;
                    if (count2 == primes_per_row) { 
					cout << "\n"; 
					count2 = 0; 
                    
				}
                if (count2 != 0 && i != n) { 
						cout << " ";
					}
                
                
                }
					
		
			}
		}

	}


int PrimesSieve::count_num_primes() const {
    int count = 0;
    // TODO: write code to count the number of primes found
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i] == true){
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    is_prime_[0] = false;
    is_prime_[1] = false;
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i] == false){
            is_prime_[i] = true;
        }
    }
    for(int i = 2; i <= sqrt(limit_); i++){
        if(is_prime_[i] == true){
            for(int j = i * i; j <= limit_; j += i){
                is_prime_[j] = false;
            }
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.

    int count1 = 0;
    while(num >= 1){
        num /= 10;
        count1++;
    }
    return count1;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    cout << endl;
    PrimesSieve test = PrimesSieve(limit);
    cout << "Number of primes found: " << test.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    test.display_primes();


    return 0;
}
