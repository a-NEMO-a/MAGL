#ifndef _VECTOR3_H_
#define _VECTOR3_H_

namespace MAGL{
    
    namespace math{
        
        namespace dimension3{
            
            struct vector{
                float        coord[3];

                             vector      () = default;
                             vector      (float x, float y, float z);

                vector       operator-   ()                                                           const;
                vector       operator+   (const vector &v)                                            const;
                vector       operator-   (const vector &v)                                            const;
                vector       operator*   (float s)                                                    const;
                vector       operator^   (const vector &v)                                            const;
                float        operator*   (const vector &v)                                            const;

                void         spin        (const vector &n, float spin);
                float        length      ()                                                           const;
                vector       normal      ()                                                           const;
                vector&      toBase      (const vector &e1, const vector &e2, const vector &e3);
                       
                vector&      operator+=  (const vector &v)                                                  {return *this = *this + v;}
                vector&      operator-=  (const vector &v)                                                  {return *this = *this - v;}
                vector&      operator*=  (float s)                                                          {return *this = *this * s;}
                vector&      operator^=  (const vector &v)                                                  {return *this = *this ^ v;}
                       
                float&       x           ()                                                                 {return coord[0];}
                float&       y           ()                                                                 {return coord[1];}
                float&       z           ()                                                                 {return coord[2];}
                const float& x           ()                                                           const {return coord[0];}
                const float& y           ()                                                           const {return coord[1];}
                const float& z           ()                                                           const {return coord[2];}
            };
            vector operator* (float s, const vector &v) {return v*s;}
        }
    }
}

#endif /* _VECTOR3_H_*/