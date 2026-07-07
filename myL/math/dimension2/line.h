#ifndef _LINE2_H_
#define _LINE2_H_

namespace myL{
    
    namespace math{
        namespace dimension2{
            
            struct line{
                vector dir;
                vector pos;
                
                       line     () = default;
                       line     (vector pt1, vector pt2)       : dir(pt2 - pt1), pos(pt1){}
                       
                float  getFromX (float x)                const {return dir.y()*(x - pos.x())/dir.x() + pos.y();}
                float  getFromY (float y)                const {return dir.x()*(y - pos.y())/dir.y() + pos.x();}
                vector getFromT (float t)                const {return dir*t + pos;}
            };
        }
    }
}

#endif //_LINE2_H_