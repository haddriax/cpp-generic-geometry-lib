#include <iostream>

#include "source/Vector.h"

int main()
{
    const Geometry::Vec3f vec1(1.0f, 2.0f, 3.0f);
    std::cout << vec1.xyz() << std::endl;
    std::cout << vec1.xy() << std::endl;
    std::cout << vec1.x() << std::endl;

    return 0;
}
