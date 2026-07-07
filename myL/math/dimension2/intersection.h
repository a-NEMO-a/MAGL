#ifndef _INTERSECT2_H_
#define _INTERSECT2_H_

namespace myL{

    namespace math{
        namespace dimension2{
            struct intersection{
                float outT[4];
                INTERSECT_TYPE intersect;
                
                     intersection () : intersect(INTERSECT_TYPE::SEPARATION){}
                
                void operator() (const vector &pt1, const vector &pt2){
                    vector t = pt1 - pt2;
                    if(isNull(t*t))
                        intersect = INTERSECT_TYPE::OVERLAP;
                    else
                        intersect = INTERSECT_TYPE::SEPARATION;
                }
                void operator() (const vector &pt, const line &ln){
                    if(isNull((pt - ln.pos)^ln.dir))
                        intersect = INTERSECT_TYPE::OVERLAP;
                    else
                        intersect = INTERSECT_TYPE::SEPARATION;
                }
                void operator() (const vector &pt, const ellipse &elps){
                    vector t(pt.toBase(elps.i, elps.j));
                    
                    if(isNull(t*t - 1.0f))
                        intersect = INTERSECT_TYPE::OVERLAP;
                    else
                        intersect = INTERSECT_TYPE::SEPARATION;
                }
                
                void operator() (const line &ln, const vector &pt){
                    this->operator()(pt, ln);
                }
                void operator() (const line &ln1, const line &ln2){
                    float n(ln2.dir^ln1.dir);
                    
                    if(isNull(n))
                        (*this)(ln2.pos, ln1);
                    else{
                        vector dp(ln1.pos - ln2.pos);
                        
                        n = 1.0f / n;
                        
                        outT[0] = (dp^ln2.dir) * n;
                        outT[1] = (dp^ln1.dir) * n;
                        intersect = INTERSECT_TYPE::INTERSECTION;
                    }
                }
                void operator() (const line &ln, const ellipse &elps){
                    vector a(elps.i^ln.dir, elps.j^ln.dir);
                    vector b(ln.pos - elps.pos);
                    
                    float d, n = elps.i^elps.j;
                    float t = a*a;
                    
                    b = vector(elps.i^b, elps.j^b);
                    
                    if(isNull(n))
                        (*this)(elps.pos, ln);
                    else if(isNull(t))
                        (*this)(ln.pos, elps);
                    else{
                        
                        d = n*n*t - quad(a^b);
                        t = 1.0f / t;
                        n = copysign(1.0f,n);
                        
                        if(isNull(d)){
                            t*= a*b;
                            outT[0] = outT[1] = -t;
                            outT[2] = outT[3] = atan2(n*(a.first*outT[0] + b.first), -n*(a.second*outT[0] + b.second));
                            
                            intersect = INTERSECT_TYPE::INTERSECTION;
                        }
                        else if(d > 0.0f){
                            d = sqrt(d) * t;
                            t*= a*b;
                            outT[0] =  d - t;
                            outT[1] = -d - t;
                            outT[2] = atan2(n*(a.first*outT[0] + b.first), -n*(a.second*outT[0] + b.second));
                            outT[3] = atan2(n*(a.first*outT[1] + b.first), -n*(a.second*outT[1] + b.second));
                            
                            intersect = INTERSECT_TYPE::INTERSECTION;
                        }
                        else
                            intersect = INTERSECT_TYPE::SEPARATION;
                    }
                }
                
                void operator() (const ellipse &elps, const vector &pt){
                    this->operator()(pt, elps);
                }
                void operator() (const ellipse &elps, const line &ln){
                    this->operator()(ln, elps);
                }
                void operator() (const ellipse &elps1, const ellipse &elps2){
                }
            };
        }
    }
}

#endif //_INTERSECT2_H_