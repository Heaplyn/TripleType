#include "layer1/triple/triple.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "--- Program Started ---" << endl; 
    //cout << fixed << setprecision(0); // Set precision for floating-point output
    triple a(3.6, 4.0);
    triple b(1.5, 3.0);
    triple c = 400.0;

    triple sum = a + b;
    triple difference = a - b;
    triple product = a * b;
    cout << "c: " << c << endl;
    cout << "Sum: Mantissa = " << sum << endl; 
    cout << "Difference: Mantissa = " << difference << endl;
    cout << "Product: Mantissa = " << product << endl; 

    return 0;
}