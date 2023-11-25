//
// Created by hadriax on 25/11/23.
//

#include "Vector.h"

namespace Geometry {
    template<unsigned Dim, typename T>
    Vector<Dim, T>::Vector(const T coords[Dim]) {
        for (unsigned int i = 0; i < Dim; ++i) {
            _data[i] = coords[i];
        }
    }

    template<unsigned Dim, typename T>
    template<unsigned D = Dim>
    std::enable_if_t<D == 2, Vector<2, T>> Vector<Dim, T>::xy() const {
        return Vector<2, T>(_data[0], _data[1]);
    }


} // Geometry