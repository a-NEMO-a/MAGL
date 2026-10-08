#ifndef _LINE3_H_
#define _LINE3_H_

namespace MAGL{
    
    namespace math{
        
        namespace dimension3{
            struct line{
                vector dir;
                vector pos;
                
                       line     () = default;
                       line     (vector pt1, vector pt2);
                       
                vector getFromX (float x)                const;
                vector getFromY (float y)                const;
                vector getFromZ (float z)                const;
                vector getFromT (float t)                const;
            };
        }
    }
}

#endif /* _LINE3_H_ */