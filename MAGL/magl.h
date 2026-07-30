#ifndef _MAGL_LIB_FOR_MATH_AND_GRAPHICS_H_
#define _MAGL_LIB_FOR_MATH_AND_GRAPHICS_H_

namespace MAGL{
    
    namespace math{
        
        template<int N>
        struct polynom;
        
        namespace dimension2{
            
            struct vector;
            struct line;
            struct ellipse;
            struct intersection;
        }
        
        namespace dimension3{
            
            struct vector;
            struct line;
            struct ellipse;
            struct flat;
            struct ellipsoid;
            struct intersection;
        }
    }
    
    namespace graphics{
    
        union rgba;
        struct field;
        
        namespace dimension2{
            
            struct canvas;
            struct render;
        }
        
        namespace dimension3{
            
            struct camera;
            struct render;
        }
    }
}

#include "math/dimension2/vector.h"
#include "math/dimension2/line.h"
#include "math/dimension2/ellipse.h"
#include "math/dimension2/intersection.h"

#include "math/dimension3/vector.h"
#include "math/dimension3/line.h"
#include "math/dimension3/flat.h"
#include "math/dimension3/ellipse.h"
#include "math/dimension3/ellipsoid.h"
#include "math/dimension3/intersection.h"

#endif /* _MAGL_LIB_FOR_MATH_AND_GRAPHICS_H_ */
