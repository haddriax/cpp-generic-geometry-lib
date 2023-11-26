//
// Created by hadriax on 25/11/23.
//
#ifndef VECTOR_H
#define VECTOR_H

#include <type_traits>
#include <utility>

namespace Geometry {
    template<unsigned int Dim, typename T>
    class Vector {
    private:
        T _data[Dim];

    public:
        // Default constructor, initializes all elements to zero.
        Vector() = default;

        // N args constructor.
        template<typename... Args>
        requires (sizeof...(Args) == Dim) // C++20
        explicit Vector(Args&&... args) : _data{ std::forward<Args>(args)... }  {}

        /* ----- Recursive initialization, for C++ < 17 ----
        template<typename... Args>
        Vector(Args&&... args) {
            static_assert(sizeof...(args) == Dim,
                          "Number of arguments must match the vector dimension.");
            initialize(std::forward<Args>(args)...);
        }

        template<typename Arg, typename... Args>
        void initialize(Arg&&arg, Args&&... args) {
            _data[Dim - sizeof...(Args) - 1] = std::forward<Arg>(arg);
            initialize(std::forward<Args>(args)...);
        }

        // Base case when there is no more arguments. End of recursion.
        void initialize() {
        }
        */

        // Accessor to get the raw data array.
        inline const T* data() const {
            return _data;
        }

        // SFINAE (Substitution Failure Is Not An Error)
        template<unsigned int D = Dim>
        inline std::enable_if_t<D >= 1, Vector<1, T>> x() const {
            return Vector<1, T>(_data[0]);
        }

        template<unsigned int D = Dim>
        // inline typename std::enable_if<d >= 2, Vector<2, T>>::type xy() const; // <=> enable_if_t
        inline std::enable_if_t<D >= 2, Vector<2, T>> xy() const {
            return Vector<2, T>(_data[0], _data[1]);
        }

        template<unsigned int D = Dim>
        inline std::enable_if_t<D >= 3, Vector<2, T>> xyz() const {
            return Vector<3, T>(_data[0], _data[1], _data[2]);
        }
    };

    // Typedefs for common use cases.
    using Vec2f = Geometry::Vector<2, float>;
    using Vec3f = Geometry::Vector<3, float>;
} // namespace Geometry

#endif // VECTOR_H
