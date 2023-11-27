#include <iostream>

#include "source/Vector.h"

int main()
{

    Geometry::Vec3f vec1(1.0f, 2.0f, 3.0f);
    Geometry::Vec2f vec2 = vec1.xy();
    auto vec3 = (vec1 + vec2);

    Geometry::Vector<3, double> v_3_d(3.2, 6, 9.6);
    Geometry::Vector<2, int> v_2_i(7, 4);
    auto c_vec = v_3_d - v_2_i;
    auto c_vec2 = v_2_i + v_3_d;
    std::cout << "vec3f: (" << c_vec.data()[0] << ", " << c_vec.data()[1] << ", " << c_vec.data()[2] << ')' << std::endl;

    // std::cout << "vec3f: (" << vec1.data()[0] << ", " << vec1.data()[1] << ", " << vec1.data()[2] << ')' << std::endl;
    // std::cout << "vec2f: (" << vec2.data()[0] << ", " << vec2.data()[1] << ')' << std::endl;
    // std::cout << "vec3f: (" << vec3.data()[0] << ", " << vec3.data()[1] << ", " << vec3.data()[2] << ')' << std::endl;

    return 0;
}
