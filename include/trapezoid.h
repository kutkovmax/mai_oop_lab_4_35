#pragma once
#include "figure.h"
#include <memory>
#include <cmath>
#include <iostream>

template <Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::unique_ptr<Point<T>> a, b, c, d;

    static double tri_area(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        return std::abs((p1.x * (p2.y - p3.y) +
                         p2.x * (p3.y - p1.y) +
                         p3.x * (p1.y - p2.y)) / 2.0);
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
          d(std::make_unique<Point<T>>(p4)) {}

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
