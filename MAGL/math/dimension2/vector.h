#ifndef _MAGL__VECTOR2_H_
#define _MAGL__VECTOR2_H_

#include <cmath>

namespace MAGL{
    
    namespace math{
        
        namespace dimension2{
            
            struct vector{
                float        coord[2];

                             vector      () = default;
                             vector      (float x, float y)                             {this->x() = x;this->y() = y;}
                                      
                vector       operator-   ()                                       const {return vector(-x(), -y());}
                vector       operator!   ()                                       const {return vector(-y(), x());}
                
                vector       operator+   (const vector &v)                        const {return vector(x() + v.x(), y() + v.y());}
                vector       operator-   (const vector &v)                        const {return vector(x() - v.x(), y() - v.y());}
                vector       operator*   (float s)                                const {return vector(s*x(), s*y());}
                float        operator*   (const vector &v)                        const {return x()*v.x() + y()*v.y();}
                float        operator^   (const vector &v)                        const {return x()*v.y() - y()*v.x();}
                
                vector&      operator+=  (const vector &v)                              {return *this = *this + v;};
                vector&      operator-=  (const vector &v)                              {return *this = *this - v;};
                vector&      operator*=  (float s)                                      {return *this = *this * s;};
                
                void         spin        (float spin)                                   {*this = (*this)*std::cos(spin) + (!*this)*std::sin(spin);}
                float        length      ()                                       const {return std::sqrt( x()*x() + y()*y() );}
                vector       normal      ()                                       const {return *this * (1.0f / length());}
                vector       toBase      (const vector &e1, const vector &e2)     const {
                                                                                            float d = determinant(e1, e2);
                                                                                            return vector(determinant(*this, e2) / d, determinant(e1, *this) / d);
                                                                                        }
                vector&      toBase      (const vector &e1, const vector &e2)           {return *this = this->toBase(e1, e2);}
                
                float&       first       ()                                             {return coord[0];}
                float&       second      ()                                             {return coord[1];}
                const float& first       ()                                       const {return coord[0];}
                const float& second      ()                                       const {return coord[1];}
                
                float&       x           ()                                             {return first();}
                float&       y           ()                                             {return second();}
                const float& x           ()                                       const {return first();}
                const float& y           ()                                       const {return second();}
                
                static float determinant (const vector &col1, const vector &col2)       {return col1^col2;}
            };
            inline vector operator* (float s, const vector &v) {return v*s;}
        }
    }
}

#endif  /* _MAGL__VECTOR2_H_ */