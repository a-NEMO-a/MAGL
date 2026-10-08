#ifndef _MAGL_CANVAS2_H_
#define _MAGL_CANVAS2_H_

#include "../../math/dimension2/vector.h"

namespace magl {

    namespace graphics {
        
        namespace dimension2 {
            
            template <typename valueT = float>
            struct canvas {
                using Vector = magl::math::dimension2::vector<valueT>;
                
                Vector hrznt;
                Vector vrtcl;
                Vector pos;
                
                canvas () = default;
                canvas (valueT lenH, valueT lenV, const Vector &pos) : hrznt(lenH, 0.0f), vrtcl(0.0f, lenV), pos(pos) {}
                canvas (const Vector &hrznt, const Vector &vrtcl, const Vector &pos) : hrznt(hrznt), vrtcl(vrtcl), pos(pos) {}
                       
                void move (const Vector &v) {pos+= v;}
                void spin (const Vector &center, const Vector &r) {
                    hrznt.spin(r);
                    vrtcl.spin(r);
                    pos = (pos - center).spin(r) + center;
                }
                void scale (valueT z) {
                    hrznt*= z / hrznt.length();
                    vrtcl*= z / vrtcl.length();
                }
            };
        }
    }
}
#endif /* _MAGL_CANVAS2_H_ */