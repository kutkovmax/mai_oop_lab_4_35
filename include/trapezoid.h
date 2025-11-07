#pragma once
#include "figure.h"
#include <memory>
#include <cmath>

template <Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4;

    static double tri_area(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        return std::abs((a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0);
    }

public:
    Trapezoid()
        : p1(std::make_unique<Point<T>>()),
          p2(std::make_unique<Point<T>>()),
          p3(std::make_unique<Point<T>>()),
          p4(std::make_unique<Point<T>>()) {}

    Trapezoid(const Trapezoid& other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
    }
    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
        return *this;
    }

    void read(std::istream& is) override {
        is >> p1->x >> p1->y >> p2->x >> p2->y >> p3->x >> p3->y >> p4->x >> p4->y;
    }

    void print(std::ostream& os) const override {
        os << "Trapezoid: " << *p1 << " " << *p2 << " " << *p3 << " " << *p4;
    }

    Point<T> center() const override {
        Point<T> sum = *p1 + *p2 + *p3 + *p4;
        return sum / 4.0;
    }

    double area() const override {
        return tri_area(*p1, *p2, *p3) + tri_area(*p1, *p3, *p4);
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
