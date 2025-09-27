//
// Created by Gael on 25/11/23.
//
#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <ostream>
#include <type_traits>
#include <utility>
#include <array>
#include <cmath>

namespace Geometry {
    template<
        unsigned int Dim,
        typename T
    > requires std::is_arithmetic_v<T>
    class Vector {
    private:
        std::array<T, Dim> _data;

    public:
        // Default constructor, initializes all elements to zero.
        Vector() {
            for (auto i = 0; i < Dim; ++i) {
                _data[i] = 0;
            }
        }

        // Copy constructor.
        Vector(const Vector& other) {
            _data = std::copy(other.data());
        }

        // Move constructor.
        Vector(const Vector&& other) noexcept : _data(std::move(other._data)) {
        }

        // N args constructor.
        template<typename... Args>
            requires (sizeof...(Args) == Dim) // C++20
        explicit Vector(Args&&... args) : _data{std::forward<Args>(args)...} {
        }

        virtual ~Vector() = default;

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
        const std::array<T,Dim >& data() const {
            return _data;
        }

        // SFINAE (Substitution Failure Is Not An Error)
        // Get x element.
        template<unsigned int D = Dim>
        auto x() const requires (Dim >= 1) {
            return _data[0];
        }

        // Get Vector from x and y elements.
        template<unsigned int D = Dim>
        auto xy() const requires (Dim >= 2) {
            return Vector<2, T>(_data[0], _data[1]);
        }

        // Get Vector from x, y and z elements.
        template<unsigned int D = Dim>
        auto xyz() const requires (Dim >= 3) {
            return Vector<3, T>(_data[0], _data[1], _data[2]);
        }

        // Operators overload
        /**
         * \brief Access the vector dimensions.
         * \param index dim index.
         * \return vector coordinate.
         */
        const T& operator[](std::size_t index) const {
            return _data[index];
        }

        // Access a Vector element.
        T& operator[](std::size_t index) {
            return _data[index];
        }

        // Copy assignement
        Vector& operator=(const Vector& other) {
            *this = Vector(other);
            return (*this);
        }

        // Move assignement
        Vector& operator=(Vector&& other) noexcept {
            *this = Vector(other);
            return (*this);
        }

        /**
         * \brief + operator, add two vectors dim by dim.
         * \param other vector to add.
         * \return new vector from (this + other), matching first vector type and dim.
         */
        template<unsigned int Dim2, typename T2>
        auto operator+(const Vector<Dim2, T2>&other) const -> Vector<Dim, T> {
            Vector<Dim, T> result;
            static_assert(Dim == Dim2, "Cannot add vectors of different dimensions.");
            for (auto i = 0; i < Dim; ++i) {
                result[i] = _data[i] + other[i];
            }
            return result;
        }

        /**
         * \brief - operator, substract two vectors dim by dim.
         * \param other vector to add.
         * \return new vector from (this - other), matching first vector type and dim.
        */
        template<unsigned int Dim2, typename T2>
        auto operator-(const Vector<Dim2, T2>&other) const -> Vector<Dim, T> {
            Vector<Dim, T> result;
            static_assert(Dim == Dim2, "Cannot substract vectors of different dimensions.");
            for (auto i = 0; i < Dim; ++i) {
                result[i] = _data[i] - other[i];
            }
            return result;
        }

        /**
         * \brief * operator, multiply two vectors dim by dim.
         * \param other vector to add.
         * \return new vector from (this * other), matching first vector type and dim.
         */
        template<unsigned int Dim2, typename T2>
        auto operator*(const Vector<Dim2, T2>&other) const -> Vector<Dim, T> {
            Vector<Dim, T> result;
            if (Dim < Dim2) {
                for (auto i = 0; i < Dim; ++i) {
                    result[i] = _data[i] * other[i];
                }
            }
            else {
                for (auto i = 0; i < Dim2; ++i) {
                    result[i] = _data[i] * other[i];
                }
            }
            return result;
        }

        /**
         * Compare two vectors by their data.
         * \param other
         * \return true if the vector have the same values.
         */
        bool operator==(const Vector &other) const {
            return _data == other._data;
        }

        /**
        * Compare two vectors by their data.
        * \param other
        * \return true if the vector have different values.
        */
        bool operator!=(const Vector &other) const {
            return !(*this == other);
        }

        /**
         * \brief Log Vector coordinates in line.
         * \param os ostream
         * \param v Logged vector
         * \return ostream
         */
        friend std::ostream &operator<<(std::ostream& os, const Vector<Dim, T>& v) {
            os << "Vector" << Dim << '[';
            for(auto i = 0; i < v._data.size() - 1; ++i)
                os << v._data[i] << ';';
            os << v._data[v._data.size()-1] << ']';

            return os;
        }

        /**
         * \brief Return the dimension of this Vector type.
         * \return dimension of the Vector
         */
        static constexpr auto dim()
        {
            return Dim;
        }

        /**
         * \brief Compute the dot product of this . other
         * \tparam T2 Type of the other vector.
         * \param other Other vector.
         * \return Dot produt of this with other.
         */
        template<typename T2>
        auto dot(const Vector<Dim, T2>& other) {
            auto r = 0;
            for (auto i = 0; i < Dim; ++i) {
                r += (_data[i] *  other[i]);
            }
            return r;
        }

        /**
         * \brief Compute the squared magnitude of this vector
         * \return squared magnitude of this vector.
         */
        auto squared_mag() const {
            T result;
            for (auto i : _data) {
                result += i * i;
            }
            return result;
        }

        auto magnitude() const {
            return std::sqrt(squared_mag());
        }

        auto normalized() const {
            auto vect_mag = magnitude();
            Vector<Dim, T> normalized;
            for (auto i = 0; i < Dim; ++i) {
                normalized[i] = _data[i] / vect_mag;
            }
            return normalized;
        }

        auto normalize() const {
            auto vect_mag = magnitude();
            for (auto& d : _data) {
                d /= vect_mag;
            }
            return &this;
        }

        template<typename T2 = T>
        auto cross(const Vector<Dim, T2>&other) const
            requires (Dim == 3) {
            // Even though requires should do the work, intellisense might still show the method.
            static_assert(Dim == 3, "Cannot cross vectors that are not 3D.");
            return Vector<3, T>(
                _data[1] * other[2] - _data[2] * other[1],
                _data[2] * other[0] - _data[0] * other[2],
                _data[0] * other[1] - _data[1] * other[0]
            );
        }
    };

    // Typedefs for common use cases.
    using Vector2 = Vector<2, double>;
    using Vector3  = Vector<3, double>;
    using Vector2f = Vector<2, float>;
    using Vector3f = Vector<3, float>;
    using Vector2i = Vector<2, int>;
    using Vector3i = Vector<3, int>;
} // namespace Geometry

#endif // VECTOR_H
