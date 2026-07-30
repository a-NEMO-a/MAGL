#ifndef _MAGL__MATH_POLYNOM_H_
#define _MAGL__MATH_POLYNOM_H_

#include "math.h"

namespace MAGL{

    namespace math{
       
        template<>
        struct polynom<0>{
            static int roots(float a){
                if(isNull(a))
                    return 0;
                else
                    return -1;
            }
        };
        
        template<>
        struct polynom<1>{
            static int roots(float a, float c, float& x1){
                if(isNull(a))
                    return polynom<0>::roots(c);
                
                x1 = -c/a;
                return 1;
            }
        };
        
        template<>
        struct polynom<2>{
            static int roots(float a, float b, float c, float& x1, float &x2){
                if(isNull(a)){
                    int res = polynom<1>::roots(b, c, x1);
                    if(res == 1)
                        x2 = x1;
                    
                    return res;
                }
                
                float d = b*b - 4*a*c;
                
                a = 1 / (2*a);
                if(isNull(d)){
                    x1 = x2 = -(b * a);
                    
                    return 2;
                }
                else if(d > 0.0){
                    d = std::sqrt(d);
                    x1 =  (d - b) * a;
                    x2 = (-d - b) * a;
                    
                    return 2;
                }
                else
                    return -1;
            }
        };
    }
}

#endif /* _MAGL__MATH_POLYNOM_H_ */