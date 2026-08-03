#include "triple.hpp"

const int MULT_NUM = 1;

static void come_correct(double& val) {
    double tempVal = floor(val * MULT_NUM);

   if (abs(val * MULT_NUM - tempVal) < 0.0001) {
        val =  tempVal / MULT_NUM   ;
        return;
    }
    tempVal = ceil(val);
    if (abs(val * MULT_NUM - tempVal) < 0.0001) {
        val =  tempVal / MULT_NUM;
        return;
    }
    
}

static void parse_triple(triple* object) {
    double currentMantissa = object->getMantissa();
    double newExponent = log10(currentMantissa);
    if (currentMantissa == 0.0) {
        object->mantissa = 0.0;
        object->exponent = 0.0;
        return;
    }
    object->exponent += floor(newExponent);
    object->mantissa = fmod(currentMantissa, 10.0);
}

triple operation( triple& a, triple& b, function<double(double, double)>& op) {
    double newMantissa = op(a.getMantissa(), b.getMantissa());
    double newExponent = a.getExponent() + b.getExponent();
    triple result(newMantissa, newExponent);
    parse_triple(&result);
    return result;
}


ostream& operator<<(ostream& os, triple& obj) {
    os << obj.toString();
    return os;
}

triple triple::operator+(triple& other) {
    double newExponent = max(this->getExponent(), other.getExponent());  
    double newMantissa;
         if (this->getExponent() < other.getExponent()) {
        double exponentDifference = other.getExponent() - this->getExponent();
        double adjustedMantissa = this->getMantissa() * pow(10, -exponentDifference);
        newMantissa = adjustedMantissa + other.getMantissa();
    } else if (this->getExponent() > other.getExponent()) {
        double exponentDifference = this->getExponent() - other.getExponent();

        double adjustedMantissa = other.getMantissa() * pow(10, -exponentDifference);
        newMantissa = this->getMantissa() + adjustedMantissa;
    } else {
        newMantissa = this->getMantissa() + other.getMantissa();
    }
    triple result(newMantissa, newExponent);
        return result;
    //return operation(*this, other, [](double a, double b) { return a + b; });
}
triple triple::operator*(triple& other) {
    double newExponent = this->getExponent() + other.getExponent();
    double newMantissa = this->getMantissa() * other.getMantissa();

    triple result(newMantissa, newExponent);
    return result;
    //return operation(*this, other, [](double a, double b) { return a + b; });
}
triple triple::operator-(triple& other) {
    double newExponent = max(this->getExponent(), other.getExponent());
        double newMantissa;
         if (this->getExponent() < other.getExponent()) {
        double exponentDifference = other.getExponent() - this->getExponent();
        double adjustedMantissa = this->getMantissa() * pow(10, -exponentDifference);
        newMantissa = adjustedMantissa - other.getMantissa();
    } else if (this->getExponent() > other.getExponent()) {
        double exponentDifference = this->getExponent() - other.getExponent();
        double adjustedMantissa = other.getMantissa() * pow(10, -exponentDifference);
        newMantissa = this->getMantissa() - adjustedMantissa;
    }
    triple result(newMantissa, newExponent);
        return result;
    //return operation(*this, other, [](double a, double b) { return a - b; });
}


string triple::toString() {
    parse_triple(this);
    double mantissa = getMantissa();
    double exponent = getExponent();
    // 1. Scale the mantissa using modulo 3 (for engineering notation grouping)
    long long remainingExponent = 0;
    if (exponent > 0) {
        long long shift = static_cast<long long>(fmod(exponent, 3.0));
        mantissa *= pow(10, shift);
        remainingExponent = static_cast<long long>(exponent) - shift;
    } else if (exponent < 0) {
        long long shift = static_cast<long long>(fmod(-exponent, 3.0));
        mantissa /= pow(10, shift);
        remainingExponent = static_cast<long long>(exponent) + shift; // Keep it negative
    }
    // 2. Convert mantissa to string cleanly (no trailing extra zeroes!)
    std::ostringstream oss;
    oss << mantissa;
    string newNum = oss.str();
    // 3. Handle the remaining exponent padding
    if (remainingExponent > 0) {
        size_t dotPlace = newNum.find('.');
        if (dotPlace != string::npos) {
            // E.g., if newNum is "123.45" and remainingExponent is 3:
            // Remove the dot -> "12345"
            newNum.erase(dotPlace, 1);
            
            // Calculate how many decimals we just "absorbed" (2 decimals: '4' and '5')
            long long absorbedDecimals = newNum.length() - dotPlace;
            long long zerosNeeded = remainingExponent - absorbedDecimals;
            
            // Append the remaining zeros needed
            for (long long i = 0; i < zerosNeeded; ++i) {
                newNum += '0';
            }
        } else {
            // No decimal point (e.g. "150"), just append all the zeros
            for (long long i = 0; i < remainingExponent; ++i) {
                newNum += '0';
            }
        }
    }
    // 4. Insert commas going backwards
    int counter = 0;
    for (int i = newNum.length() - 1; i >= 0; --i) {
        counter++; 
        if (counter == 3 && i != 0) { // 👈 Prevent leading comma
            newNum.insert(i, ",");
            counter = 0;
        }
    }
    return newNum;
}

triple::triple(double num) {
    mantissa = num;
    exponent = 0.0;
    parse_triple(this);
}