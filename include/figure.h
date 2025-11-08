#pragma once
#include "concepts.h"
#include "point.h"
#include <memory>
#include <iostream>
#include <cmath>

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    operator double() const { return area(); }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& f) {
        f.print(os);
        return os;
    }
};
