#pragma once
#include "concepts.h"
#include "figure.h"
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>

template <Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::unique_ptr<Point<T>> a, b, c, d;

    static double tri_area(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        return std::abs((p1.x * (p2.y - p3.y) +
                         p2.x * (p3.y - p1.y) +
                         p3.x * (p1.y - p2.y)) / 2.0);
    }

    static double dist(const Point<T>& p, const Point<T>& q) {
        return std::sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
    }

    void validate() const {
        // Проверка что это трапеция (AB параллельно CD)
        double ab_x = b->x - a->x, ab_y = b->y - a->y;
        double dc_x = c->x - d->x, dc_y = c->y - d->y;
        
        bool ab_parallel_cd = std::abs(ab_x * dc_y - ab_y * dc_x) < 1e-6;
        
        // Если AB не параллельно CD, проверяем BC параллельно AD
        if (!ab_parallel_cd) {
            double bc_x = c->x - b->x, bc_y = c->y - b->y;
            double ad_x = d->x - a->x, ad_y = d->y - a->y;
            bool bc_parallel_ad = std::abs(bc_x * ad_y - bc_y * ad_x) < 1e-6;
            
            if (!bc_parallel_ad) {
                throw std::logic_error("Not a trapezoid (no parallel sides)");
            }
        }

        // Проверка равнобедренности
        double leg1, leg2;
        if (ab_parallel_cd) {
            // AB || CD => боковые стороны BC и AD
            leg1 = dist(*b, *c);
            leg2 = dist(*a, *d);
        } else {
            // BC || AD => боковые стороны AB и CD  
            leg1 = dist(*a, *b);
            leg2 = dist(*c, *d);
        }

        if (std::abs(leg1 - leg2) > 1e-6) {
            throw std::logic_error("Not an isosceles trapezoid");
        }
    }

public:
    Trapezoid()
        : a(std::make_unique<Point<T>>()),
          b(std::make_unique<Point<T>>()),
          c(std::make_unique<Point<T>>()),
          d(std::make_unique<Point<T>>()) {}

    Trapezoid(const Point<T>& p1, const Point<T>& p2,
              const Point<T>& p3, const Point<T>& p4)
        : a(std::make_unique<Point<T>>(p1)),
          b(std::make_unique<Point<T>>(p2)),
          c(std::make_unique<Point<T>>(p3)),
          d(std::make_unique<Point<T>>(p4)) 
    {
        validate();
    }

    Trapezoid(const Trapezoid& other) {
        a = std::make_unique<Point<T>>(*other.a);
        b = std::make_unique<Point<T>>(*other.b);
        c = std::make_unique<Point<T>>(*other.c);
        d = std::make_unique<Point<T>>(*other.d);
    }

    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        a = std::make_unique<Point<T>>(*other.a);
        b = std::make_unique<Point<T>>(*other.b);
        c = std::make_unique<Point<T>>(*other.c);
        d = std::make_unique<Point<T>>(*other.d);
        return *this;
    }

    Trapezoid(Trapezoid&&) noexcept = default;
    Trapezoid& operator=(Trapezoid&&) noexcept = default;

    void read(std::istream& is) override {
        is >> a->x >> a->y >> b->x >> b->y >> c->x >> c->y >> d->x >> d->y;
        validate();
    }

    void print(std::ostream& os) const override {
        os << "Trapezoid: " << *a << " " << *b << " " << *c << " " << *d;
    }

    Point<T> center() const override {
        return (*a + *b + *c + *d) / 4.0;
    }

    double area() const override {
        return tri_area(*a, *b, *c) + tri_area(*a, *c, *d);
    }

    bool operator==(const Trapezoid& other) const {
        return *a == *other.a && *b == *other.b && *c == *other.c && *d == *other.d;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Trapezoid<T>>(*this);
    }
};

template <Scalar T>
inline std::istream& operator>>(std::istream& is, Trapezoid<T>& tr) {
    tr.read(is);
    return is;
}
