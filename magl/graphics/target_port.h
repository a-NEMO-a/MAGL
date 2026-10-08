#ifndef _MAGL_VIEWPORT_H_
#define _MAGL_VIEWPORT_H_

namespace magl {

    namespace graphics {
        
        struct position {
            float x;
            float y;
            
            constexpr position () = default;
            constexpr position (float x, float y) : x(x), y(y) {}
        };
            
        struct box {
            int left;
            int up;
            int right;
            int bottom;
            
            constexpr box () = default;
            constexpr box (int left, int up, int right, int bottom) : left(left), up(up), right(right), bottom(bottom) {}
        };
        
        struct target_port {
            box field;
            position center;
            
            constexpr target_port () = default;
            constexpr target_port (int left, int up, int right, int bottom, float cntrX, float cntrY) : field(left, up, right, bottom), center(cntrX, cntrY) {}
            constexpr target_port (int left, int up, int right, int bottom) : field(left, up, right, bottom), center((left + right + 1) * 0.5f, (bottom + up + 1) * 0.5f) {}
            constexpr target_port (box field, position center) : field(field), center(center) {}
        };
    }
}

#endif /* _MAGL_VIEWPORT_H_ */