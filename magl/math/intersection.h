#ifndef MAGL_INTERSECTION_H
#define MAGL_INTERSECTION_H

#include "dimension2/vector.h"
#include "dimension2/line.h"
#include "dimension2/ellipse.h"

#include "polynom.h"

#include <cmath>

namespace magl {

    namespace math {
        
        template <typename valueT>
        struct intersection_info {
                
            const int *cnt;
            const valueT *t_type1;
            const valueT *t_type2;
            
            intersection_info (const int *count, const valueT *t_t1, const valueT *t_t2) : cnt(count), t_type1(t_t1), t_type2(t_t2) {}
        };
        
        template<template <typename> typename T1, template <typename> typename T2, typename valueT = float>
        struct intersection;
        
        template <typename valueT> 
        struct intersection<dimension2::vector, dimension2::vector, valueT> {
            
            using Type1 = dimension2::vector<valueT>;
            using Type2 = dimension2::vector<valueT>;
            
            intersection () : cnt(0) {}
            
            void operator() (const Type1 &pt1, const Type2 &pt2) {
                Type1 t {pt1 - pt2};
                if (is_zero<valueT>(t*t))
                    cnt = -1; // overlap
                else
                    cnt = 0;  // separate
            }
            static int intrsct (const Type1 &pt1, const Type2 &pt2) {
                Type1 t {pt1 - pt2};
                if (is_zero<valueT>(t*t))
                    return -1; // overlap
                else
                    return 0;  // separate
            }
            intersection_info<valueT> get_info () {
                return intersection_info<valueT>(&cnt, nullptr, nullptr);
            }
            int cnt;
        };
        
        template <typename valueT>
        struct intersection<dimension2::vector, dimension2::line, valueT> {
            
            using Type1 = dimension2::vector<valueT>;
            using Type2 = dimension2::line<valueT>;
                        
            intersection () : cnt(0) {}
            
            void operator() (const Type1 &pt, const Type2 &ln) {
                Type1 t {pt - ln.pos};
                if (is_zero<valueT>(t^ln.dir)) {
                    t_type2[0] = (t * ln.dir) / (ln.dir * ln.dir);

                    cnt = 1; // intersect
                }
                else {
                    cnt = 0; // separate
                }
            }
            void operator() (const Type2 &ln, const Type1 &pt) {
                operator()(pt, ln);
            }
                   
            static int intrsct (const Type1 &pt, const Type2 &ln) {
                Type1 t(pt - ln.pos);
                if (is_zero<valueT>(t^ln.dir))
                    return 1; // intersect
                else
                    return 0; // separate
            }
            static int intrsct (const Type2 &ln, const Type1 &pt) {
                return intrsct(pt, ln);
            }            
            intersection_info<valueT> get_info () {
                return intersection_info<valueT>(&cnt, nullptr, t_type2);
            }
            int cnt;
            valueT t_type2[1];
        };
        
        template <typename valueT>
        struct intersection<dimension2::vector, dimension2::ellipse, valueT> {
            
            using Type1 = dimension2::vector<valueT>;
            using Type2 = dimension2::ellipse<valueT>;
            
            intersection () : cnt(0) {}
            
            void operator() (const Type1 &pt, const Type2 &elps) {
                Type1 t {pt - elps.pos};
                valueT n {elps.i^elps.j};
                t = Type1(elps.i^t, elps.j^t);

                if (is_zero<valueT>(t*t - n*n)) {
                    n = std::copysign(1.0f, n);
                    t_type2[0] = std::atan2(n*t.first(), -n*t.second());

                    cnt = 1; // intersect
                }
                else {
                    cnt = 0; // separate
                }
            }
            void operator() (const Type2 &elps, const Type1 &pt) {
                operator()(pt, elps);
            }
            static int intrsct (const Type1 &pt, const Type2 &elps) {
                Type1 t(pt - elps.pos);
                valueT n = elps.i^elps.j;
                t = Type1(elps.i^t, elps.j^t);

                if (is_zero<valueT>(t*t - n*n))
                    return 1; // intersect
                else
                    return 0; // separate
            }
            static int intrsct (const Type2 &elps, const Type1 &pt) {
                return intrsct(pt, elps);
            }
            intersection_info<valueT> get_info () {
                return intersection_info<valueT>(&cnt, nullptr, t_type2);
            }
            int cnt;
            valueT t_type2[1];
        };

        
        template <typename valueT>
        struct intersection<dimension2::line, dimension2::line, valueT> {
            
            using Type1 = dimension2::line<valueT>;
            using Type2 = dimension2::line<valueT>;
            
            intersection () : cnt(0) {}
            
            void operator() (const Type1 &ln1, const Type2 &ln2) {
                valueT n {ln2.dir^ln1.dir};

                if (is_zero<valueT>(n)) {
                    switch(intersection<dimension2::vector, dimension2::line, valueT>::intrsct(ln2.pos, ln1)) {
                        case 1: 
                            cnt = -1; // overlap
                            break;
                        case 0:
                            cnt = 0;  // separate
                            break;
                    }
                }
                else {
                    dimension2::vector<valueT> dp {ln1.pos - ln2.pos};
                    
                    n = valueT(1.0) / n;
                    
                    t_type1[0] = (dp^ln2.dir) * n;
                    t_type2[0] = (dp^ln1.dir) * n;
                    cnt = 1; // intersect
                }
            }
            static int intrsct (const Type1 &ln1, const Type2 &ln2) {
                valueT n {ln2.dir^ln1.dir};

                if (is_zero<valueT>(n)){
                    switch(intersection<dimension2::vector, dimension2::line, valueT>::intrsct(ln2.pos, ln1)) {
                        case 1: return -1; // overlap
                        case 0: return 0;  // separate
                    }
                }
                else
                    return 1; // intersect
            }
            intersection_info<valueT> get_info () {
                return intersection_info<valueT>(&cnt, t_type1, t_type2);
            }
            int cnt;
            valueT t_type1[1];
            valueT t_type2[1];
        };
        
        template <typename valueT>
        struct intersection<dimension2::line, dimension2::ellipse, valueT> {
            
            using Type1 = dimension2::line<valueT>;
            using Type2 = dimension2::ellipse<valueT>;
            using Vector = dimension2::vector<valueT>;
            
            intersection () : cnt(0) {}
            
            void operator() (const Type1 &ln, const Type2 &elps) {
                cnt = 0;
                Vector a {elps.i^ln.dir, elps.j^ln.dir};
                Vector b {ln.pos - elps.pos};
                valueT n {elps.i^elps.j};

                b = Vector(elps.i^b, elps.j^b);

                std::complex<valueT> x[2];
                int i;
                int t_t1count = polynom<2, valueT>::roots(
                    a*a,
                    2*(a*b), 
                    b*b - n*n, 
                    x
                );
                n = std::copysign(c_1, n);

                for (i = 0; i != t_t1count; i++)
                    if (is_zero<valueT>(x[i].imag())) {
                        t_type1[cnt] = x[i].real();
                        t_type2[cnt] = std::atan2(n*(a.first()*t_type1[cnt] + b.first()), -n*(a.second()*t_type1[cnt] + b.second()));
                        cnt++;
                    }
                // intersect / separate
            }
            void operator() (const Type2 &elps, const Type1 &ln) {
                operator()(ln, elps);
            }
            static int intrsct (const Type1 &ln, const Type2 &elps) {
                Vector a {elps.i^ln.dir, elps.j^ln.dir};
                Vector b {ln.pos - elps.pos};
                valueT n {elps.i^elps.j};

                b = Vector(elps.i^b, elps.j^b);

                std::complex<valueT> x[2];
                int i, cnt;
                int t_t1count = polynom<2, valueT>::roots(
                    a*a,
                    2*(a*b),
                    b*b - n*n,
                    x
                );
                
                cnt = 0;
                for (i = 0; i != t_t1count; i++)
                    if (is_zero<valueT>(x[i].imag()))
                        cnt++;
                
                return cnt; // intersect / separate
            }
            static int intrsct (const Type2 &elps, const Type1 &ln) {
                return intrsct(ln, elps);
            }
            intersection_info<valueT> get_info () {
                return intersection_info<valueT>(&cnt, t_type1, t_type2);
            }
            int cnt;
            valueT t_type1[2];
            valueT t_type2[2];
        
        private:    
            static constexpr valueT c_1 {1.0};
        };
        
        template <typename valueT>
        struct intersection<dimension2::ellipse, dimension2::ellipse, valueT> {
            
            using Type1 = dimension2::ellipse<valueT>;
            using Type2 = dimension2::ellipse<valueT>;
            using Vector = dimension2::vector<valueT>;
            
            intersection () : cnt(0) {}
            
            void operator() (const Type1 &elps1, const Type2 &elps2) {
                valueT el1_det {elps1.i^elps1.j};
                if (is_zero(el1_det)) { cnt = 0; return; }
                
                Vector vx {(elps2.i^elps1.j) / el1_det, (elps1.i^elps2.i) / el1_det};
                Vector vy {(elps2.j^elps1.j) / el1_det, (elps1.i^elps2.j) / el1_det};
                Vector p  {(elps2.pos - elps1.pos) / el1_det};
                p = Vector(p^elps1.j, elps1.i^p);
                
                valueT vx_sq {vx*vx};
                valueT vy_sq {vy*vy};
                
                valueT a {vx_sq - vy_sq};
                valueT b {c_2 * (vx*p)};
                valueT c {p*p + vy_sq - c_1};
                valueT d {c_2 * (vx*vy)};
                valueT e {c_2 * (vy*p)};
                
                std::complex<valueT> x[4];
                int t2_cnt = polynom<4, valueT>::roots(
                    a*a + d*d,
                    c_2*(a*b + d*e),
                    (c_2*a*c + b*b - d*d + e*e),
                    c_2*(b*c - d*e),
                    c*c - e*e,
                    x
                );
                
                if (t2_cnt == -1) {
                    cnt = -1;
                    return;
                }
                cnt = 0;
                
                Vector dp = elps2.pos - elps1.pos; 
                Vector e2, dir;
                
                int i;
                for (i = 0; i < t2_cnt; i++)
                    if (is_zero(x[i].imag())) {
                        e2.x() = x[i].real();
                        
                        e2.y() = d * e2.x() + e;
                        if (is_zero(e2.y())) {
                            valueT clamp_x = std::clamp(e2.x(), -c_1, c_1);
                            e2.y() = std::sqrt(c_1 - clamp_x * clamp_x);
                        } else {
                            e2.y() = -(a*e2.x()*e2.x() + b*e2.x() + c) / e2.y();
                        }
                        
                        dir = elps2.i*e2.x() + elps2.j*e2.y() + dp;
                        
                        t_type1[cnt] = std::atan2((elps1.i^dir), (dir^elps1.j));
                        t_type2[cnt] = std::atan2(e2.y(), e2.x());
                        
                        cnt++;
                    }
            }
            /*void operator() (const Type1 &elps1, const Type2 &elps2) {
                // 1. Переводим всё в систему координат первого эллипса, 
                // где он становится единичной окружностью.
                // Для этого находим обратную матрицу базиса elps1.
                valueT det1 = elps1.i ^ elps1.j;
                if (is_zero(det1)) { cnt = 0; return; }
                
                // Вектор смещения центров
                Vector dp = elps2.pos - elps1.pos;
                
                // Локальные координаты центра второго эллипса в базисе первого
                Vector c2_loc(
                    (dp ^ elps1.j) / det1,
                    (elps1.i ^ dp) / det1
                );
                
                // Локальные направления осей второго эллипса в базисе первого
                Vector i2_loc(
                    (elps2.i ^ elps1.j) / det1,
                    (elps1.i ^ elps2.i) / det1
                );
                Vector j2_loc(
                    (elps2.j ^ elps1.j) / det1,
                    (elps1.i ^ elps2.j) / det1
                );
                
                // 2. Теперь строим матрицу квадратичной формы второго эллипса в этом пространстве.
                // Уравнение второго эллипса: (r - c2_loc)^T * A * (r - c2_loc) = 1
                // Где A = (Matrix_2)^(-T) * (Matrix_2)^(-1)
                valueT det2 = i2_loc ^ j2_loc;
                if (is_zero(det2)) { cnt = 0; return; }
                
                // Коэффициенты матрицы квадратичной формы второго эллипса
                valueT A = (j2_loc.y()*j2_loc.y() + i2_loc.y()*i2_loc.y()) / (det2*det2);
                valueT B = -(j2_loc.x()*j2_loc.y() + i2_loc.x()*i2_loc.y()) / (det2*det2); // без двойки
                valueT C_coeff = (j2_loc.x()*j2_loc.x() + i2_loc.x()*i2_loc.x()) / (det2*det2);
                
                // Линейная часть и константа с учетом смещения центра c2_loc
                valueT D = -A * c2_loc.x() - B * c2_loc.y();
                valueT E = -B * c2_loc.x() - C_coeff * c2_loc.y();
                valueT F = A * c2_loc.x()*c2_loc.x() + c_2 * B * c2_loc.x()*c2_loc.y() + C_coeff * c2_loc.y()*c2_loc.y() - c_1;
                
                // 3. Пересекаем с единичной окружностью первого эллипса (x^2 + y^2 = 1)
                // Подставляем параметризацию x = (1-t^2)/(1+t^2), y = 2t/(1+t^2) 
                // Это превращает уравнение в полином 4-й степени от t.
                std::complex<valueT> x_roots[4];
                int t_t1cnt = polynom<4, valueT>::roots(
                    F - c_2*D + A,
                    c_4*E - c_4*B,
                    c_2*F - c_2*A + c_4*C_coeff,
                    c_4*E + c_4*B,
                    F + c_2*D + A,
                    x_roots
                );
                
                if (t_t1cnt == -1) {
                    cnt = -1;
                    return;
                }
                
                cnt = 0;
                for (int i = 0; i < t_t1cnt; i++) {
                    if (is_zero(x_roots[i].imag())) {
                        valueT t_param = x_roots[i].real();
                        valueT t_sq = t_param * t_param;
                        
                        // Возвращаемся из тригонометрической подстановки к координатам на окружности
                        valueT x_loc = (c_1 - t_sq) / (c_1 + t_sq);
                        valueT y_loc = (c_2 * t_param) / (c_1 + t_sq);
                        
                        // Вычисляем угол t для первого эллипса
                        t_type1[cnt] = std::atan2(y_loc, x_loc);
                        
                        // Находим глобальную точку пересечения
                        Vector global_pt = elps1.pos + elps1.i * x_loc + elps1.j * y_loc;
                        
                        // Проецируем глобальную точку на оси второго эллипса для получения его угла t
                        Vector div2 = global_pt - elps2.pos;
                        valueT det_elps2 = elps2.i ^ elps2.j;
                        valueT sgn2 = std::copysign(c_1, det_elps2);
                        
                        t_type2[cnt] = std::atan2((elps2.i ^ div2) * sgn2, (div2 ^ elps2.j) * sgn2);
                        
                        cnt++;
                    }
                }
            }*/

            static int intrsct (const Type1 &elps1, const Type2 &elps2) {
                return 0;
            }
            intersection_info<valueT> get_info () {
                return intersection_info<valueT>(&cnt, t_type1, t_type2);
            }
            int cnt;
            valueT t_type1[4];
            valueT t_type2[4];
        
        private:    
            static inline constexpr valueT c_0   {0.0};
            static inline constexpr valueT c_0p5 {0.5};
            static inline constexpr valueT c_1   {1.0};
            static inline constexpr valueT c_2   {2.0};
            static inline constexpr valueT c_4   {4.0};
        };
    }
}

#endif /* MAGL_INTERSECTION_H */