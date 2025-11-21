#pragma once
#include "concepts.h"
#include "figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>

template <Scalar T>
class Rhombus : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4;

    static double tri_area(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        return std::abs((a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0);
    }

    static double dist(const Point<T>& u, const Point<T>& v) {
        return std::sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
    }

    static double angle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        double ux = a.x - b.x, uy = a.y - b.y;
        double vx = c.x - b.x, vy = c.y - b.y;
        double dot = ux * vx + uy * vy;
        double nu = std::sqrt(ux * ux + uy * uy);
        double nv = std::sqrt(vx * vx + vy * vy);
        return std::acos(dot / (nu * nv));
    }

    bool isCyclic() const {
        double A = angle(*p2, *p1, *p4);
        double C = angle(*p2, *p3, *p4);
        return std::abs((A + C) - M_PI) < 1e-6;
    }

    void validate() const {
        // Проверка равенства всех сторон
        double s1 = dist(*p1, *p2);
        double s2 = dist(*p2, *p3);
        double s3 = dist(*p3, *p4);
        double s4 = dist(*p4, *p1);

        if (!(std::abs(s1 - s2) < 1e-6 &&
              std::abs(s2 - s3) < 1e-6 &&
              std::abs(s3 - s4) < 1e-6))
            throw std::logic_error("Not a rhombus (sides differ)");

        // Проверка цикличности (ромб должен быть квадратом)
        if (!isCyclic())
            throw std::logic_error("Rhombus must be cyclic — only squares are cyclic");
    }

public:
    Rhombus()
        : p1(std::make_unique<Point<T>>()),
          p2(std::make_unique<Point<T>>()),
          p3(std::make_unique<Point<T>>()),
          p4(std::make_unique<Point<T>>()) {}

    Rhombus(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d)
        : p1(std::make_unique<Point<T>>(a)),
          p2(std::make_unique<Point<T>>(b)),
          p3(std::make_unique<Point<T>>(c)),
          p4(std::make_unique<Point<T>>(d)) 
    {
        validate();
    }

    Rhombus(const Rhombus& other)
        : p1(std::make_unique<Point<T>>(*other.p1)),
          p2(std::make_unique<Point<T>>(*other.p2)),
          p3(std::make_unique<Point<T>>(*other.p3)),
          p4(std::make_unique<Point<T>>(*other.p4)) {}

    Rhombus& operator=(const Rhombus& other) {
        if (this == &other) return *this;
        *p1 = *other.p1;
        *p2 = *other.p2;
        *p3 = *other.p3;
        *p4 = *other.p4;
        return *this;
    }

    void read(std::istream& is) override {
        is >> p1->x >> p1->y >> p2->x >> p2->y >> p3->x >> p3->y >> p4->x >> p4->y;
        validate();
    }

    void print(std::ostream& os) const override {
        os << "Rhombus: " << *p1 << " " << *p2 << " " << *p3 << " " << *p4;
    }

    Point<T> center() const override {
        Point<T> sum = *p1 + *p2 + *p3 + *p4;
        return sum / 4.0;
    }

    double area() const override {
        return tri_area(*p1, *p2, *p3) + tri_area(*p1, *p3, *p4);
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhombus<T>>(*this);
    }

    bool operator==(const Rhombus<T>& other) const {
        return *p1 == *other.p1 && *p2 == *other.p2 && *p3 == *other.p3 && *p4 == *other.p4;
    }
};

template <Scalar T>
inline std::istream& operator>>(std::istream& is, Rhombus<T>& rh) {
    rh.read(is);
    return is;
}
