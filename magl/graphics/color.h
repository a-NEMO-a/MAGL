#ifndef _MAGL_RGBA_H_
#define _MAGL_RGBA_H_

#include <cstdint>

namespace magl {

    namespace graphics {

        struct color {
            
            color () = default;
            color (float r, float g, float b) : r(r), g(g), b(b) {}
            
            void setR (float red)   {r = red;}
            void setG (float green) {g = green;}
            void setB (float blue)  {b = blue;}
            
            float getR () const {return r;}
            float getG () const {return g;}
            float getB () const {return b;}
            
            bool setRGB (float R, float G, float B) {
                r = R;
                g = G;
                b = B;
                
                return true;
            }
            
            color light (color lght, float intens) {
                return color(intens * getR()*lght.getR(), intens * getG()*lght.getG(), intens * getB()*lght.getB());
            }
        private:
            float r;
            float g;
            float b;
        };
    }
}

#endif /* _MAGL_RGBA_H_ */
