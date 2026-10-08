#ifndef MAGL_MATH_POLYNOM_H
#define MAGL_MATH_POLYNOM_H

#include <cmath>
#include <complex>

namespace magl {

    namespace math {
        
        template<typename valueT>        
        inline bool is_zero (const std::complex<valueT> &v) {
            return is_zero<valueT>(v.real()) && is_zero<valueT>(v.imag());
        }
        
        template<int N, typename valueT>
        struct polynom;
        
        template <typename valueT>
        struct polynom<0, valueT> {
            static int roots 
                (const std::complex<valueT> &a)
                {
                    return is_zero<valueT>(a)? -1 : 0;
                }
             
            static int roots
                ()
                {
                    return -1;
                }
        };
        
        template <typename valueT>
        struct polynom<1, valueT> {
            static int roots
               (const std::complex<valueT> &a,
                const std::complex<valueT> &b,
                std::complex<valueT> x[1])
                {
                    return is_zero<valueT>(a) ? 
                           polynom<0, valueT>::roots(b) :
                           roots(b/a, x);
                }
             
            static int roots
               (const std::complex<valueT> &b,
                std::complex<valueT> x[1])
                {
                    x[0] = -b;
                    
                    return 1;
                }
        };
        
        template <typename valueT>
        struct polynom<2, valueT> {
            static int roots
               (const std::complex<valueT> &a,
                const std::complex<valueT> &b,
                const std::complex<valueT> &c,
                std::complex<valueT> x[2])
                {
                    return is_zero<valueT>(a) ?
                           polynom<1, valueT>::roots(b, c, x) :
                           roots(b/a, c/a, x);
                }
        
            static int roots
               (const std::complex<valueT> &b,
                const std::complex<valueT> &c,
                std::complex<valueT> x[2])
            {
                std::complex<valueT> d = std::sqrt(b*b - c_4 * c);
                
                x[0] = c_0p5 * (d - b);
                x[1] = c_0p5 * (-d - b);
                
                return is_zero<valueT>(d) ? 1 : 2;
            }
            
        private:
            static inline constexpr valueT c_0p5 {0.5};
            static inline constexpr valueT c_4   {4.0};
        };

        template <typename valueT>
        struct polynom<3, valueT> {
            static int roots
               (const std::complex<valueT> &a,
                const std::complex<valueT> &b,
                const std::complex<valueT> &c,
                const std::complex<valueT> &d,
                std::complex<valueT> x[3])
                {
                    return is_zero<valueT>(a) ?
                           polynom<2, valueT>::roots(b, c, d, x) :
                           roots(b/a * c_inv3, c/a * c_inv3, d/a, x);
                }
       
            static int roots
               (const std::complex<valueT> &b,
                const std::complex<valueT> &c,
                const std::complex<valueT> &d,
                std::complex<valueT> x[3])
                {
                    std::complex<valueT> b_sq {b*b};
                    std::complex<valueT> p {c - b_sq}, q {b_sq*b - c_1p5 * b*c + c_0p5 * d};
                    std::complex<valueT> Q {std::sqrt(p*p*p + q*q)};
                    
                    std::complex<valueT> u {std::pow(-q + Q, c_inv3)}, v {is_zero<valueT>(u)? std::pow(-q - Q, c_inv3) : -p/u};
                    
                    x[0] = u + v - b;
                    x[1] = u*w1 + v*w2 - b;
                    x[2] = u*w2 + v*w1 - b;
                    
                    int i, j, cnt = 1;
                    bool unique;
                    for (i = 1; i < 3; i++) {
                        unique = true;
                        for (j = 0; j < cnt; j++) {
                            if (is_zero<valueT>(x[i] - x[j])) {
                                unique = false;
                                break;
                            }
                        }
                        if (unique)
                            x[cnt++] = x[i];
                    }

                    return cnt;
                }
        private:         
            static inline constexpr valueT c_inv3       {valueT(1.0) / valueT(3.0)};
            static inline constexpr valueT c_0p5        {0.5};
            static inline constexpr valueT c_1p5        {1.5};
            static inline constexpr valueT c_sqrt3      {std::sqrt(valueT(3.0))}; // 0.86602540378443864676
            static inline constexpr std::complex<valueT> w1 {-c_0p5, c_sqrt3 * c_0p5};  // -0.5 + i*0.5*sqrt(3);
            static inline constexpr std::complex<valueT> w2 {-c_0p5, -c_sqrt3 * c_0p5}; // -0.5 - i*0.5*sqrt(3);
        };
        
        template <typename valueT>
        struct polynom<4, valueT> {
            static int roots
               (const std::complex<valueT> &a,
                const std::complex<valueT> &b,
                const std::complex<valueT> &c,
                const std::complex<valueT> &d,
                const std::complex<valueT> &e,
                std::complex<valueT> x[4])
                {
                    return is_zero<valueT>(a) ? 
                           polynom<3, valueT>::roots(b, c, d, e, x) :
                           roots(b/a * c_inv4, c/a * c_inv6, d/a * c_inv4, e/a, x);
                }
        
            static int roots
               (const std::complex<valueT> &b,
                const std::complex<valueT> &c,
                const std::complex<valueT> &d,
                const std::complex<valueT> &e,
                std::complex<valueT> x[4])
                {
                    
                    std::complex<valueT> b_sq {b*b};
                    std::complex<valueT> p {c_3*(c - b_sq)}, q {c_4*(b_sq*b - c_1p5*b*c + c_0p5*d)}, r {e + c_6*b_sq*c - c_4*b*d - c_3*b_sq*b_sq};
                    
                    std::complex<valueT> t[3];
                    
                    int i, j, cnt, maxCnt;
                    
                    if (is_zero<valueT>(q)) {
                        
                        t[0] = std::sqrt(p*p - r);
                        t[1] = std::sqrt(-p - t[0]);
                        t[2] = std::sqrt(-p + t[0]);
                        
                        x[0] =  t[1];
                        x[1] = -t[1];
                        x[2] =  t[2];
                        x[3] = -t[2];
                        
                        maxCnt = 4;
                    }
                    else {
                        
                        maxCnt = polynom<3, valueT>::roots(
                            c_2,
                            c_4*p,
                            c_2*(p*p - r),
                            -q*q,
                            t
                        );
                        
                        j = 0;
                        for (i = 1; i < maxCnt; i++)
                            if (std::norm(t[i]) > std::norm(t[j]))
                                j = i;
                        
                        t[0] = t[j];
                        t[1] = std::sqrt(c_2*t[0]); // sqrt(2t)
                        t[2] = p + t[0];            // p + t
                        t[0] = q / t[1];            // q / sqrt(2t)
                        
                        maxCnt = polynom<2, valueT>::roots(
                            c_1,
                            -t[1],          // -sqrt(2t)
                            t[2] + t[0],    // p + t + q / sqrt(2t)
                            x
                        );
                        maxCnt+= polynom<2, valueT>::roots(
                            c_1,
                            t[1],           // sqrt(2t)
                            t[2] - t[0],    // p + t - q / sqrt(2t)
                            x + maxCnt
                        );
                    }
                    
                    cnt = 0;
                    bool unique;
                    for (i = 0; i != maxCnt; i++)
                        x[i]-= b;
                        
                    if (maxCnt > 0) {
                        cnt = 1;
                        for (i = 1; i < maxCnt; i++) {
                            unique = true;
                            for (j = 0; j < cnt; j++) {
                                if (is_zero<valueT>(x[i] - x[j])) {
                                    unique = false;
                                    break;
                                }
                            }
                            if (unique)
                                x[cnt++] = x[i];
                        }
                    }
                    return cnt;
                }
                
        private:        
            static inline constexpr valueT c_inv6 {valueT(1.0) / valueT(6.0)};
            static inline constexpr valueT c_inv4 {valueT(1.0) / valueT(4.0)};
            static inline constexpr std::complex<valueT> c_0 {valueT{0.0}, valueT{0.0}};
            static inline constexpr valueT c_0p5  {0.5};
            static inline constexpr std::complex<valueT> c_1 {valueT{1.0}, valueT{0.0}};
            static inline constexpr valueT c_1p5  {1.5};
            static inline constexpr std::complex<valueT> c_2 {valueT{2.0}, valueT{0.0}};
            static inline constexpr valueT c_3    {3.0};
            static inline constexpr valueT c_4    {4.0};
            static inline constexpr valueT c_6    {6.0};
        };

    }
}

#endif /* MAGL_MATH_POLYNOM_H */