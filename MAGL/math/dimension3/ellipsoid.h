#ifndef _ELLIPSOID_H_
#define _ELLIPSOID_H_

namespace MAGL{
    
    namespace math{
        
        namespace dimension3{
            struct ellipsoid{
                vector i;
                vector j;
                vector k;
                vector pos;
            };
        }
    }
}

#endif /* _ELLIPSOID_H_ */