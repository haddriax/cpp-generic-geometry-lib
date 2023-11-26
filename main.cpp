#include <iostream>

#include "source/Vector.h"

int main()
{

    Geometry::Vec3f vec1(1.0f, 2.0f, 3.0f);
    Geometry::Vec2f vec2 = vec1.xy();
    Geometry::Vec2f vec3;

    std::cout << "vec3f: (" << vec1.data()[0] << ", " << vec1.data()[1] << ", " << vec1.data()[2] << ')' << std::endl;
    std::cout << "vec2f: (" << vec2.data()[0] << ", " << vec2.data()[1] << ')' << std::endl;
    std::cout << "vec3f: (" << vec3.data()[0] << ", " << vec3.data()[1] << ", " << vec3.data()[2] << ')' << std::endl;

    return 0;
}
