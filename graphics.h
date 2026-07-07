#ifndef _LGL_GRAPHICS_H_
#define _LGL_GRAPHICS_H_

#include <math.h>

#include "myL\epsilon.h"
#include "myL\intersect_type.h"
#include "myL\math\mathfunc.h"

namespace myL{
    
    namespace math{
        
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

#include "myL\math\dimension2\vector.h"
#include "myL\math\dimension2\line.h"
#include "myL\math\dimension2\ellipse.h"
#include "myL\math\dimension2\intersection.h"

#include "myL\math\dimension3\vector.h"
#include "myL\math\dimension3\line.h"
#include "myL\math\dimension3\flat.h"
#include "myL\math\dimension3\ellipse.h"
#include "myL\math\dimension3\ellipsoid.h"
#include "myL\math\dimension3\intersection.h"

#endif /* _LGL_GRAPHICS_H_ */
