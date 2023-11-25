//
// Created by hadriax on 25/11/23.
//
#ifndef VECTOR_H
#define VECTOR_H

#include <type_traits>


namespace Geometry {

    template <unsigned int Dim, typename T>
    class Vector {
    private:
        T _data[Dim];

    public:
        // Default constructor initializes all elements to zero.
        Vector() = default;

        // Explicit constructor for providing initial values.
        explicit Vector(const T coords[Dim]);

        // Accessor to get the raw data array.
        inline const T* data() const {
            return _data;
        }

        // Create a 2D vector from the current vector.
        template <unsigned int d = Dim>
        inline std::enable_if_t<d == 2, Vector<2, T>> xy() const;
    };

    // Typedefs for common use cases.
    using Vec2f = Geometry::Vector<2, float>;
    using Vec3f = Geometry::Vector<3, float>;
} // namespace Geometry

#endif // VECTOR_H
