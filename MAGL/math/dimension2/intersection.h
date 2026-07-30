#ifndef _MAGL__INTERSECT2_H_
#define _MAGL__INTERSECT2_H_

#include "vector.h"
#include "line.h"
#include "ellipse.h"

#include "../intersect_type.h"
#include "../math.h"
#include "../polynom.h"

#include <cmath>

namespace MAGL{

    namespace math{
        
        namespace dimension2{
            
            struct intersection{
                float outT[4];
                int outCnt;
                INTERSECT_TYPE intersect;
                
                     intersection () : intersect(INTERSECT_TYPE::SEPARATION){}
                
                void operator()   (const vector &pt1, const vector &pt2)          {
                                                                                    vector t = pt1 - pt2;
                                                                                    if(isNull(t*t))
                                                                                        intersect = INTERSECT_TYPE::OVERLAP;
                                                                                    else
                                                                                        intersect = INTERSECT_TYPE::SEPARATION;
                                                                                    outCnt = 0;
                                                                                  }
                                                                        
                void operator()   (const vector &pt, const line &ln)              {
                                                                                    vector t(pt - ln.pos);
                                                                                    if(isNull(t^ln.dir)){
                                                                                        outT[0] = (t * ln.dir) / (ln.dir * ln.dir);
                                                                                        
                                                                                        intersect = INTERSECT_TYPE::OVERLAP;
                                                                                        outCnt = 1;
                                                                                    }
                                                                                    else{
                                                                                        intersect = INTERSECT_TYPE::SEPARATION;
                                                                                        outCnt = 0;
                                                                                    }
                                                                                  }
                                                                        
                void operator()   (const vector &pt, const ellipse &elps)         {
                                                                                    vector t(pt - elps.pos);
                                                                                    float n = elps.i^elps.j;
                                                                                    t = vector(elps.i^t, elps.j^t);
                                                                                    
                                                                                    if(isNull(t*t - n*n)){
                                                                                        n = std::copysign(1.0f,n);
                                                                                        outT[0] = std::atan2(n*t.first(), -n*t.second());
                                                                                        
                                                                                        intersect = INTERSECT_TYPE::OVERLAP;
                                                                                        outCnt = 1;
                                                                                    }
                                                                                    else{
                                                                                        intersect = INTERSECT_TYPE::SEPARATION;
                                                                                        outCnt = 0;
                                                                                    }
                                                                                  }
                
                void operator()   (const line &ln, const vector &pt)              {this->operator()(pt, ln);}
                
                void operator()   (const line &ln1, const line &ln2)              {
                                                                                    float n(ln2.dir^ln1.dir);
                                                                                    
                                                                                    if(isNull(n))
                                                                                        (*this)(ln2.pos, ln1);
                                                                                    else{
                                                                                        vector dp(ln1.pos - ln2.pos);
                                                                                        
                                                                                        n = 1.0f / n;
                                                                                        
                                                                                        outT[0] = (dp^ln2.dir) * n;
                                                                                        outT[1] = (dp^ln1.dir) * n;
                                                                                        intersect = INTERSECT_TYPE::INTERSECTION;
                                                                                        outCnt = 2;
                                                                                    }
                                                                                  }
                                                                        
                void operator()   (const line &ln, const ellipse &elps)           {
                                                                                    vector a(elps.i^ln.dir, elps.j^ln.dir);
                                                                                    vector b(ln.pos - elps.pos);
                                                                                    float n = elps.i^elps.j;
                                                                                    
                                                                                    b = vector(elps.i^b, elps.j^b);
                                                                                    
                                                                                    switch(polynom<2>::roots(a*a, 2*(a*b), b*b - n*n, outT[0], outT[1])){
                                                                                        case -1:
                                                                                            intersect = INTERSECT_TYPE::SEPARATION;
                                                                                            outCnt = 0;
                                                                                            
                                                                                            break;
                                                                                        case 0:
                                                                                            intersect = INTERSECT_TYPE::OVERLAP;
                                                                                            outCnt = 0;
                                                                                            
                                                                                            break;
                                                                                        case 1:
                                                                                            n = std::copysign(1.0f,n);
                                                                                            outT[2] = outT[3] = std::atan2(n*(a.first()*outT[0] + b.first()), -n*(a.second()*outT[0] + b.second()));
                                                                                            
                                                                                            intersect = INTERSECT_TYPE::INTERSECTION;
                                                                                            outCnt = 4;
                                                                                            
                                                                                            break;
                                                                                        case 2:
                                                                                            n = std::copysign(1.0f,n);
                                                                                            outT[2] = std::atan2(n*(a.first()*outT[0] + b.first()), -n*(a.second()*outT[0] + b.second()));
                                                                                            outT[3] = std::atan2(n*(a.first()*outT[1] + b.first()), -n*(a.second()*outT[1] + b.second()));
                                                                                            
                                                                                            intersect = INTERSECT_TYPE::INTERSECTION;
                                                                                            outCnt = 4;
                                                                                            
                                                                                            break;
                                                                                    }
                                                                                  }
                
                void operator()   (const ellipse &elps, const vector &pt)         {this->operator()(pt, elps);}
                
                void operator()   (const ellipse &elps, const line &ln)           {this->operator()(ln, elps);}
                
                void operator()   (const ellipse &elps1, const ellipse &elps2)    {
                                                                                  }
            };
        }
    }
}

#endif /* _MAGL__INTERSECT2_H_ */