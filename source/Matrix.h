//
// Created by Gael on 28/11/2023.
//

#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <type_traits>

namespace Geometry
{
    template<
        unsigned int DimH,
        unsigned int DimW,
        typename T,
        typename = std::enable_if_t<std::is_arithmetic_v<T>, T>
    >
    class Matrix {
        private:
            std::array<T, DimH * DimW> _data;
        };
} // namespace Geometry


#endif //MATRIX_H
