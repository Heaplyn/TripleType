# Custom C++ Number Type: `triple`

A custom C++ class designed to represent and compute numbers far larger than standard double-precision float limits (`1.79e308`). 

It represents numbers using normalized scientific notation:
$$\text{Value} = \text{mantissa} \times 10^{\text{exponent}}$$

Using a 64-bit integer for the exponent, this class supports numbers up to $10^{9,223,372,036,854,775,807}$.

---

## How to Compile & Run

To compile the project and link your source files, run the following commands in your PowerShell/CMD terminal inside this directory:

### 1. Compile the Files
Use `g++` to compile `main.cpp` and `triple.cpp` together:
```powershell
g++ main.cpp layer1/triple/triple.cpp -o main.exe
```

### 2. Run the Program
```powershell
.\main.exe
```

---

## Code Usage Example

Below is a simple example of how to initialize and use the `triple` class:

```cpp
#include "layer1/triple/triple.hpp"
#include <iostream>

using namespace std;

int main() {
    // Initialize triples (mantissa, exponent)
    triple a(1.5, 2.0); // 150
    triple b(2.5, 3.0); // 2500

    // Perform math (uses overloaded operators)
    triple sum = a + b;
    triple difference = a - b;

    // Output results (uses overloaded friend operator<<)
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << difference << endl;

    return 0;
}
```
