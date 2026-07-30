#ifndef _MAGL__INTERSECT_TYPE_H_
#define _MAGL__INTERSECT_TYPE_H_

namespace MAGL{
    
    namespace math{
        
        enum class INTERSECT_TYPE : int{
            SEPARATION,
            INTERSECTION,
            OVERLAP
        };
    }

}

#endif /* _MAGL__INTERSECT_TYPE_H_ */