#ifndef _FLAT_H_
#define _FLAT_H_

namespace MAGL{
    
    namespace math{
        
        namespace dimension3{
            
            struct flat{
                vector i;
                vector j;
                vector pos;
                
                       flat     () = default;
                       flat     (vector pt1, vector pt2, vector pt3);
                       
                vector normal   ()                                   const;
                line   getFromX (float x)                            const;
                line   getFromY (float y)                            const;
                line   getFromZ (float z)                            const;
                vector getFromT (float t1, float t2)                 const;
            };
        }
    }
}

#endif /* _FLAT_H_ */