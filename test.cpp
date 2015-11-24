#include "t2Vector.hpp"
#include <iostream>

int main()
{
    t2Vector<int> v(2, 2);
    t2Vector<float> u(v);

    std::cout << u.getX() << " " << u.getY() << std::endl;
    u *= 0.7;
    std::cout << u.getX() << " " << u.getY() << std::endl;

    return (0);
}