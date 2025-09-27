/**
* @file Vector.h
 * @brief Generic N-dimensional arithmetic vector template class.
 *
 * This header defines a templated N-dimensional vector class for arithmetic types,
 * supporting mathematical operations such as addition, subtraction, scalar and
 * component-wise multiplication, normalization, dot and cross products.
 * Requires C++20
 * @author Gael
 * @date 27/09/2025
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <ostream>
#include <type_traits>
#include <utility>
#include <array>
#include <cmath>

namespace Geometry {
    /**
     * @class Vector
     * @brief A generic N-dimensional mathematical vector class.
     *
     * @tparam Dim The dimension of the vector (e.g., 2 for 2D, 3 for 3D).
     * @tparam T The scalar type (e.g., float, double, int). Must be arithmetic.
     */
    template<
        unsigned int Dim,
        typename T
    > requires std::is_arithmetic_v<T>
    class Vector {
    private:
        std::array<T, Dim> _data;

    public:
        /// @brief Default constructor initializes all components to 0.
        constexpr Vector() {
            for (auto i = 0; i < Dim; ++i) {
                _data[i] = 0;
            }
        }

        /// @brief Copy constructor.
        constexpr Vector(const Vector &other) : _data(other._data) {
        }

        /// @brief Move constructor.
        constexpr Vector(Vector &&other) noexcept : _data(std::move(other._data)) {
        }

        /// @brief Constructor with Dim number of arguments.
        /// @note Each argument becomes a coordinate component.
        template<typename... Args>
            requires (sizeof...(Args) == Dim) // C++20
        constexpr explicit Vector(Args &&... args) : _data{std::forward<Args>(args)...} {
        }

        virtual ~Vector() = default;

        /// @brief Access the internal data.
        constexpr const std::array<T, Dim> &data() const {
            return _data;
        }

        // SFINAE (Substitution Failure Is Not An Error)
        /// @brief Returns the first coordinate (x) if Dim >= 1.
        template<unsigned int D = Dim>
        [[nodiscard]] auto x() const requires (Dim >= 1) {
            return _data[0];
        }

        /// @brief Returns the first two coordinates as a 2D vector if Dim >= 2.
        template<unsigned int D = Dim>
        [[nodiscard]] auto xy() const requires (Dim >= 2) {
            return Vector<2, T>(_data[0], _data[1]);
        }

        /// @brief Returns the first three coordinates as a 3D vector if Dim >= 3.
        template<unsigned int D = Dim>
        [[nodiscard]] auto xyz() const requires (Dim >= 3) {
            return Vector<3, T>(_data[0], _data[1], _data[2]);
        }

        // Operators overload
        /// @brief Const element access by index.
        constexpr const T &operator[](std::size_t index) const {
            return _data[index];
        }

        /// @brief Mutable element access by index.
        constexpr T &operator[](std::size_t index) {
            return _data[index];
        }

        /// @brief Copy assignment.
        Vector& operator=(const Vector &other) {
            if (this != &other) {
                _data = other._data;
            }
            return *this;
        }

        /// @brief Move assignment.
        Vector& operator=(Vector&&other) noexcept {
            if (this != &other) {
                _data = std::move(other._data);
            }
            return *this;
        }

        /**
         * @brief Adds two vectors component-wise.
         * @note Only vectors of the same dimension are allowed.
         * @return Resulting vector: vec{c} = vec{a} + vec{b}
         */
        template<unsigned int Dim2, typename T2>
        [[nodiscard]] constexpr auto operator+(const Vector<Dim2, T2> &other) const {
            Vector<Dim, T> result;
            static_assert(Dim == Dim2, "Cannot add vectors of different dimensions.");
            for (auto i = 0; i < Dim; ++i) {
                result[i] = _data[i] + other[i];
            }
            return result;
        }

        /**
         * @brief Subtracts two vectors component-wise.
         * @note Only vectors of the same dimension are allowed.
         * @return Resulting vector: vec{c} = vec{a} - vec{b}
         */
        template<unsigned int Dim2, typename T2>
        [[nodiscard]] constexpr auto operator-(const Vector<Dim2, T2> &other) const {
            Vector<Dim, T> result;
            static_assert(Dim == Dim2, "Cannot subtract vectors of different dimensions.");
            for (auto i = 0; i < Dim; ++i) {
                result[i] = _data[i] - other[i];
            }
            return result;
        }

        /**
         * @brief Component-wise multiplication (Hadamard product).
         * @return Resulting vector: vec{c}_i = vec{a}_i * vec{b}_i
         */
        template<unsigned int Dim2, typename T2>
        [[nodiscard]] constexpr auto operator*(const Vector<Dim2, T2> &other) const {
            Vector<Dim, T> result;
            static_assert(Dim == Dim2, "Cannot subtract vectors of different dimensions.");
            for (auto i = 0; i < Dim; ++i) {
                result[i] = _data[i] * other[i];
            }
            return result;
        }

        /**
        * @brief Component-wise multiplication with scalar.
        * @return Resulting vector: vec{v}_i = vec{v}_i * scalar
        */
        [[nodiscard]] constexpr Vector operator*(T scalar) const {
            using ScalarType = decltype(_data[0] * scalar);
            Vector<Dim, ScalarType> result;
            for (auto i = 0; i < Dim; ++i)
                result[i] = _data[i] * scalar;
            return result;
        }

        [[nodiscard]] friend Vector operator*(T scalar, const Vector &v) {
            return v * scalar;
        }

        /// @brief Equality operator (component-wise).
        constexpr bool operator==(const Vector &other) const {
            return _data == other._data;
        }

        /// @brief Inequality operator (component-wise).
        constexpr bool operator!=(const Vector &other) const {
            return !(*this == other);
        }

        /// @brief Pretty print a vector.
        friend std::ostream &operator<<(std::ostream &os, const Vector<Dim, T> &v) {
            os << "Vector" << Dim << '[';
            for (auto i = 0; i < v._data.size() - 1; ++i)
                os << v._data[i] << ';';
            os << v._data[v._data.size()-1] << ']';

            return os;
        }

        /// @brief Get the static dimension of the vector type.
        static constexpr auto dim()
        {
            return Dim;
        }

        /**
         * @brief Compute the dot product (scalar product) of two vectors.
         * @return Scalar value: vec{a} dot vec{b} = sum a_i b_i
         */
        template<typename T2>
        [[nodiscard]] auto dot(const Vector<Dim, T2> &other) const {
            decltype(_data[0] * other[0]) r = 0;
            for (auto i = 0; i < Dim; ++i) {
                r += (_data[i] * other[i]);
            }
            return r;
        }

        /**
         * @brief Compute the squared magnitude (length) of the vector.
         * @return  |vec{v}|^2 = sum v_i^2
         */
        [[nodiscard]] constexpr auto squared_mag() const {
            T result = 0;
            for (auto i = 0; i < Dim; ++i) {
                result += _data[i] * _data[i];
            }
            return result;
        }

        /**
         * @brief Compute the magnitude (Euclidean norm).
         * @return |vec{v}| = sqrt{sum v_i^2}
         */
        [[nodiscard]] constexpr auto magnitude() const {
            return std::sqrt(squared_mag());
        }

        /**
         * @brief Return a normalized copy of the vector.
         * @return norm{v} = vec{v} / |vec{v}|
         */
        [[nodiscard("`normalized()` returns a new vector. Use `normalize()` for in-place operation.")]]
        auto normalized() const {
            auto vect_mag = magnitude();
            Vector<Dim, T> normalized;
            for (auto i = 0; i < Dim; ++i) {
                normalized[i] = _data[i] / vect_mag;
            }
            return normalized;
        }

        /**
         * @brief Normalize the current vector in place.
         * @note Modifies the current vector.
         */
        void normalize() {
            auto vect_mag = magnitude();
            for (auto &d: _data) {
                d /= vect_mag;
            }
        }

        /**
         * @brief Compute the cross product of two 3D vectors.
         * @return vec{a} cross vec{b}
         * @note Only enabled for Dim == 3.
         */
        template<typename T2 = T>
        [[nodiscard]] auto cross(const Vector<Dim, T2> &other) const
            requires (Dim == 3) {
            // Even though requires should do the work, intellisense might still show the method.
            static_assert(Dim == 3, "Cannot cross vectors that are not 3D.");
            using CrossType = decltype(_data[0] * other[0]);
            return Vector<3, CrossType>(
                _data[1] * other[2] - _data[2] * other[1],
                _data[2] * other[0] - _data[0] * other[2],
                _data[0] * other[1] - _data[1] * other[0]
            );
        }
    };

    // Typedefs for common use cases.
    using Vector2 = Vector<2, double>;
    using Vector3 = Vector<3, double>;
    using Vector2f = Vector<2, float>;
    using Vector3f = Vector<3, float>;
    using Vector2i = Vector<2, int>;
    using Vector3i = Vector<3, int>;
} // namespace Geometry

#endif // VECTOR_H
