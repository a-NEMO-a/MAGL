#ifndef _INTERSECTION3_H_
#define _INTERSECTION3_H_

namespace MAGL{
    
    namespace math{
        
        namespace dimension3{
            
            struct intersection{
                float outPt[8];
                INTERSECT_TYPE intersect;
                
                     intersection ();
                void operator()   (const vector &pt1, const vector &pt2);
                void operator()   (const vector &pt, const line &ln);
                void operator()   (const vector &pt, const ellipse &elps);
                void operator()   (const vector &pt, const flat &ft);
                void operator()   (const vector &pt, const ellipsoid &elps);
                
                void operator()   (const line &ln, const vector &pt);
                void operator()   (const line &ln1, const line &ln2);
                void operator()   (const line &ln, const ellipse &elps);
                void operator()   (const line &ln, const flat &ft);
                void operator()   (const line &ln, const ellipsoid &elps);

                void operator()   (const ellipse &elps, const vector &pt);
                void operator()   (const ellipse &elps, const line &ln);
                void operator()   (const ellipse &elps1, const ellipse &elps2);
                void operator()   (const ellipse &elps, const flat &ft);
                void operator()   (const ellipse &elps, const ellipsoid &elpsd);
                
                void operator()   (const flat &ft, const vector &pt);
                void operator()   (const flat &ft, const line &ln);
                void operator()   (const flat &ft, const ellipse &elps);
                void operator()   (const flat &ft1, const flat &ft2);
                void operator()   (const flat &ft, const ellipsoid &elps);
                
                void operator()   (const ellipsoid &elps, const vector &pt);
                void operator()   (const ellipsoid &elps, const line &ln);
                void operator()   (const ellipsoid &elpsd, const ellipse &elps);
                void operator()   (const ellipsoid &elps, const flat &ft);
                void operator()   (const ellipsoid &elps1, const ellipsoid &elps2);
            };
        }
    }
}

#endif /* _INTERSECTION3_H_ */