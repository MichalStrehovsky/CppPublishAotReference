#include <iostream>

extern "C" int ManagedAdd(int x, int y);

int main()
{
    std::cout << "2 + 2 = " << ManagedAdd(2, 2) << std::endl;
}
