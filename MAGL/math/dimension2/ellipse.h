#ifndef _MAGL__ELLIPSE2_H_
#define _MAGL__ELLIPSE2_H_

#include "vector.h"

#include "../math.h"

#include <cmath>

namespace MAGL{
    
    namespace math{
        
        namespace dimension2{
            
            struct ellipse{
                vector i;
                vector j;
                vector pos;
                
                       ellipse  () = default;
                       ellipse  (const vector &i, const vector &j, const vector &pos)       : i(i), j(j), pos(pos){}
                       
                vector getFromT (float t)                                             const {return i*std::cos(t) + j*std::sin(t) + pos;}
                
                bool   isValid  ()                                                    const {return !isNull(i^j);}
            };
        }
    }
}

#endif /* _MAGL__ELLIPSE2_H_ */