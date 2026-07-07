#ifndef _ELLIPSE2_H_
#define _ELLIPSE2_H_

namespace myL{
    
    namespace math{
        
        namespace dimension2{
            
            struct ellipse{
                vector i;
                vector j;
                vector pos;
                       ellipse  () = default;
                       ellipse  (const vector &i, const vector &j, const vector &pos)       : i(i), j(j), pos(pos){}
                vector getFromT (float t)                                             const {return i*cosf(t) + j*sinf(t) + pos;}
            };
        }
    }
}

#endif //_ELLIPSE2_H_