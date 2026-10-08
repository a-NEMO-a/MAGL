#ifndef _MAGL_RENDER2_H_
#define _MAGL_RENDER2_H_

#include <cmath>

#include "../../math.h"
#include "../target_port.h"
#include "canvas.h"

namespace magl {

    namespace graphics {
        
        namespace dimension2 {
            
            template <typename valueT = float>
            struct interpolator {
                
                using Vector       = magl::math::dimension2::vector<valueT>;
                using Const_vector = const Vector;
                using Line         = magl::math::dimension2::line<valueT>;
                using Canvas       = magl::graphics::dimension2::canvas<valueT>;
                using Box          = const magl::graphics::box&;
                
                int w;
                int h;
                const hook** shBuff;
                
                interpolator (int w, int h, const hook** shBuff) : w(w), h(h), shBuff(shBuff) {}
                      
                void operator() (Box field, const hook* sh, Const_vector &pt1) const {
                    int x, y, d;

                    x = std::round(pt1.x());
                    y = std::round(pt1.y());
                    if (field.left <= x && x <= field.right && field.up <= y && y <= field.bottom) {
                        d = w*y + x;

                        shBuff[d] = sh;
                    }
                }
                void operator() (Box field, const hook* sh, Vector pt1, Vector pt2) const {
                    int x, y, cnt, ind;
                    valueT len;
                    Vector *a{&pt1}, *b{&pt2}, *tmp;
                    Line toDraw(pt1, pt2);

                    if (a->y() > b->y()) {tmp = a; a = b; b = tmp;}
                    if (a->y() < field.up) {
                        if (b->y() < field.up)
                            return;
                        else
                            *a = toDraw.getFromY(field.up);
                    }
                    if (b->y() > field.bottom) {
                        if (a->y() > field.bottom)
                            return;
                        else
                            *b = toDraw.getFromY(field.bottom);
                    }
                    
                    if (a->x() > b->x()) {tmp = a; a = b; b = tmp;}
                    if (a->x() < field.left) {
                        if (b->x() < field.left)
                            return;
                        else
                            *a = toDraw.getFromX(field.left);
                    }
                    if (b->x() > field.right) {
                        if (a->x() > field.right)
                            return;
                        else
                            *b = toDraw.getFromX(field.right);
                    }
                    toDraw = Line(pt1, pt2);
                    if (std::abs(toDraw.dir.x()) > std::abs(toDraw.dir.y()))
                        len = std::abs(toDraw.dir.x());
                    else
                        len = std::abs(toDraw.dir.y());

                    toDraw.dir/= len;
                    cnt = std::round(len);
                    
                    for (; cnt > 0; cnt--, toDraw.pos+= toDraw.dir) {
                        x = std::round(toDraw.pos.x());
                        y = std::round(toDraw.pos.y());
                        ind = w*y + x;
                        shBuff[ind] = sh;
                    }
                }
                void operator() (Box field, const hook* sh, Const_vector &pt1, Const_vector &pt2,  Const_vector &pt3) const {
                    
                    Const_vector *a{&pt1}, *b{&pt2}, *c{&pt3};
                    
                    struct {
                        
                        const valueT &(Vector::*M)() const;
                        const valueT &(Vector::*N)() const;
                        
                        int mW;
                        int nW;
                        
                        box field;
                        
                        int w;
                        int h;
                        hook** shBuff;
                        hook *sh;
                        
                        void run (Line lLeft, Line lRight) const {
                        
                            int m, mMax, n, nMax, ind;
                            valueT l, r;
                            
                            r = (lLeft.dir.*M)();
                            l = static_cast<valueT>(1.0) / r;
                            lLeft.dir*= l;
                            lRight.dir*= l;
                            
                            m = std::round((lLeft.pos.*M)());
                            mMax = std::round(r + (lLeft.pos.*M)());
                            
                            l = (lLeft.pos.*N)(); 
                            r = (lRight.pos.*N)(); 
                            
                            if (m < field.up) {
                                m = field.up - m;
                                l+= (lLeft.dir.*N)() * m;
                                r+= (lRight.dir.*N)() * m;
                                m = field.up;
                            }
                            if (mMax > field.bottom) mMax = field.bottom + 1;
                            
                            for (; m < mMax; m++) {
                                n = std::round(l);
                                nMax = std::round(r);
                                
                                if (n < field.left)     n = field.left;
                                if (nMax > field.right) nMax = field.right;
                                
                                for (ind = mW*m + nW*n; n <= nMax; n++, ind+= nW) {
                                    shBuff[ind] = sh;
                                }
                                
                                l+= (lLeft.dir.*N)();
                                r+= (lRight.dir.*N)();
                            }
                        }
                
                    }foo;
                    foo.w = w;
                    foo.shBuff = shBuff;
                    foo.sh = sh;
                    
                    Line lInvB, lB, *lLeft, *lRight;

                    {
                        Const_vector *tmp;
                        Const_vector *aX{a}, *bX{b}, *cX{c};
                        Const_vector *aY{a}, *bY{b}, *cY{c};
                        
                        if (bX->x() > aX->x()) {tmp = aX; aX = bX; bX = tmp;}
                        if (cX->x() > bX->x()) {tmp = cX; cX = bX; bX = tmp;
                        if (bX->x() > aX->x()) {tmp = aX; aX = bX; bX = tmp;}}
                        
                        if (bY->y() > aY->y()) {tmp = aY; aY = bY; bY = tmp;}
                        if (cY->y() > bY->y()) {tmp = cY; cY = bY; bY = tmp;
                        if (bY->y() > aY->y()) {tmp = aY; aY = bY; bY = tmp;}}
                        
                        if (aX->x() - cX->x() > aY->y() - cY->y()) {
                            a = aX; b = bX; c = cX;
                            
                            foo.M = &Vector::x;
                            foo.N = &Vector::y;

                            foo.field = box(field.up, field.left, field.bottom, field.right);
                            foo.mW = 1;
                            foo.nW = w;
                        }
                        else {
                            a = aY; b = bY; c = cY;
                            
                            foo.M = &Vector::y;
                            foo.N = &Vector::x;
                            
                            foo.field = field;
                            foo.mW = w;
                            foo.nW = 1;
                        }
                    }
                    
                    Vector invB = Line(*a, *c).getFromT(((b->*foo.M)() - (a->*foo.M)()) / ((c->*foo.M)() - (a->*foo.M)()));
                    
                    if ((b->*foo.N)() > (invB.*foo.N)()) {lLeft = &lInvB; lRight = &lB;}
                    else                                 {lLeft = &lB; lRight = &lInvB;}
                    
                    lInvB = Line(invB, *a);
                    lB = Line(*b, *a);
                    
                    foo.run(*lLeft, *lRight);
                    
                    lInvB = Line(*c, invB);
                    lB = Line(*c, *b);
                    
                    foo.run(*lLeft, *lRight);
                }
            };
        }
    }
}
#endif /* _MAGL_RENDER2_H_ */