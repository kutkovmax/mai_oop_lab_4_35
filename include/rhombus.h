#pragma once
#include "figure.h"
#include <memory>
#include <cmath>

template <Scalar T>
class Rhombus : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4;

    static double dist2(const Point<T>& a, const Point<T>& b) {
        double dx = double(a.x - b.x);
        double dy = double(a.y - b.y);
        return dx*dx + dy*dy;
    }

public:
    Rhombus()
        : p1(std::make_unique<Point<T>>()),
          p2(std::make_unique<Point<T>>()),
          p3(std::make_unique<Point<T>>()),
          p4(std::make_unique<Point<T>>()) {}

    Rhombus(const Rhombus& other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
    }
    Rhombus& operator=(const Rhombus& other) {
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
        os << "Rhombus: " << *p1 << " " << *p2 << " " << *p3 << " " << *p4;
    }

    Point<T> center() const override {
        Point<T> sum = *p1 + *p2 + *p3 + *p4;
        return sum / 4.0;
    }

    double area() const override {
        // area = (d1 * d2) / 2, diagonals between p1-p3 and p2-p4
        double d1 = std::sqrt(dist2(*p1, *p3));
        double d2 = std::sqrt(dist2(*p2, *p4));
        return (d1 * d2) / 2.0;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhombus<T>>(*this);
    }
};

template <Scalar T>
inline std::istream& operator>>(std::istream& is, Rhombus<T>& r) {
    r.read(is);
    return is;
}
