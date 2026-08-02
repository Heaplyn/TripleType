#include <algorithm>
#include <functional>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;




    class triple {
        public:
            double mantissa = 0.0;
            double exponent = 0.0;
            triple(double mantissa,double exponent): mantissa(mantissa), exponent(exponent) {}
            triple operator+( triple& other);   
            triple operator-( triple& other);
            triple operator*(triple& other);
            friend ostream& operator<<(ostream& os, triple& obj);
            double getMantissa()  ;
            double getExponent()  ;
            string toString();

    };
