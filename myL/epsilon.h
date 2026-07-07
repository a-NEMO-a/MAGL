#ifndef _IMP_EPS_H_
#define _IMP_EPS_H_

namespace myL{
    
    const float EPS = 1e-07f;
    
    inline bool isNull(float x){
        return fabsf(x) < EPS;
    }
}

#endif //_IMP_VECTOR2_H_