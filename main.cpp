#include <iostream>

#include "source/Vector.h"

constexpr bool test_vector_access() {
    Geometry::Vector<3, int> v(10, 20, 30);
    return v[0] == 10 && v[1] == 20 && v[2] == 30;
}

constexpr auto mutability_test() {
    Geometry::Vector<3, int> v(1, 2, 3);
    v[0] = 42; // modify via non-const operator[]
    return v[0];
}

int main()
{
    static_assert(Geometry::Vector<3, double>::dim() == 3);
    static_assert(test_vector_access(), "Compile-time access test failed!");
    static_assert(mutability_test() == 42, "Compile-time mutability test failed!");

    const Geometry::Vector3 vec1(1.0, 2.0, 3.0);
    const Geometry::Vector3 vec2(1.0, 2.0, 3.0);
    const Geometry::Vector3 vec3(16.0, -4.0, 256.0);
    std::cout << vec1 << " and " << vec2 << " are " << ((vec1 == vec2) ? "equals" : "not equals") << std::endl;
    std::cout << vec1 << " and " << vec2 << " are " << ((vec1 != vec2) ? "not equals" : "equals") << std::endl;
    std::cout << vec1 << " and " << vec3 << " are " << ((vec1 == vec3) ? "equals" : "not equals") << std::endl;
    std::cout << vec1 << " and " << vec3 << " are " << ((vec1 != vec3) ? "not equals" : "equals") << std::endl;

    const Geometry::Vector3f vec4(1.0f, 1.0f, 1.0f);
    std::cout << vec4.xyz() << std::endl;
    std::cout << "magnitude of " << vec4 << ": " << vec4.magnitude() << std::endl;
    std::cout << "cross product " << vec1.cross(vec4) << std::endl;
    std::cout << vec1 + vec2 << std::endl;
    std::cout << vec1 * vec2 << std::endl;
    std::cout << vec1 - vec2 << std::endl;
    std::cout << vec1 - vec2 - vec2 << std::endl;

    const Geometry::Vector2f vec5(1.0f, 2.0f);
    const Geometry::Vector2 vec6(1.0, 2.0);

    // Init a vector at 1.Of for all 16 dimensions.
    const Geometry::Vector<16, float> vec_d_16(1.0f);
    std::cout << "Vec_d_16 : " << vec_d_16 << std::endl;

    // See if it works fine with dim 1 vector
    const Geometry::Vector<1, float> vec_d_1(42.0f);
    std::cout << "Vec_d_1 : " << vec_d_1 << std::endl;

    // Try a constexpr initialisation
    constexpr Geometry::Vector<4, int> vec_d_4(1, 2, 3, 4);
    static_assert(vec_d_4[0] == 1 && vec_d_4[1] == 2 && vec_d_4[2] == 3 && vec_d_4[3] == 4,
                  "Constexpr initialisation failed");
    std::cout << "Vec_d_4 : " << vec_d_4 << std::endl;


    const Geometry::Vector3 vec_proj1(-4.0, 2.0, 12.0);
    const Geometry::Vector3 vec_proj2(3.0, 1.0, 2.0);
    std::cout << "Vec_proj: : " << vec_proj1.project(vec_proj2) << std::endl;

    return 0;
}
