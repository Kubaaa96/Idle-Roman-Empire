#include <iostream>

#include "IRECore.h"

namespace ire {
void InitCore()
{
    std::cout << "Test Init Core\n";
}

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}
}
