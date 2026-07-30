#ifndef _MAGL__MATHFUNC_H_
#define _MAGL__MATHFUNC_H_

#include <cmath>

namespace MAGL{

    namespace math{
        
        const float EPS = 1e-07f;
    
        inline bool isNull(float x){
            return std::abs(x) < EPS;
        }
    }
}

#endif /* _MAGL__MATHFUNC_H_ */