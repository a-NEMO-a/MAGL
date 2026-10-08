#ifndef MAGL_MATH_H
#define MAGL_MATH_H

#include <cmath>

namespace magl {

    namespace math {
        
        template <typename valueT>
        constexpr valueT eps {1e-7};
        
        template <typename valueT>
        inline bool is_zero (const valueT &v) {
            return std::abs(v) < eps<valueT>;
        }
    }
}

#include "math/polynom.h"
#include "math/intersection.h"
#include "math/dimension2.h"
#include "math/dimension3.h"

#endif /* MAGL_MATH_H */