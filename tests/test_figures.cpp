// tests/test_figures.cpp
#include <cassert>
#include <iostream>
#include <memory>

#include "figure_array.h"
#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"

using D = double;

void test_rectangle_basic() {
    Rectangle<D> r1(Point<D>{0,0}, Point<D>{2,0}, Point<D>{2,1}, Point<D>{0,1});
    Rectangle<D> r2 = r1; // copy
    assert(r1 == r2);
    assert(std::abs(r1.area() - 2.0) < 1e-9);
    auto c = r1.center();
    assert(std::abs(c.x - 1.0) < 1e-9 && std::abs(c.y - 0.5) < 1e-9);
    std::cout << "[OK] Rectangle basic\n";
}

void test_rhombus_basic() {
    Rhombus<D> rh(Point<D>{0,0}, Point<D>{1,1}, Point<D>{2,0}, Point<D>{1,-1});
    double a = rh.area();
    assert(a > 0);
    auto c = rh.center();
    assert(std::abs(c.x - 1.0) < 1e-9);
    std::cout << "[OK] Rhombus basic\n";
}

void test_trapezoid_basic() {
    Trapezoid<D> t(Point<D>{0,0}, Point<D>{3,0}, Point<D>{2,1}, Point<D>{1,1});
    double a = t.area();
    assert(a > 0.0);
    auto c = t.center();
    assert(c.x > 0 && c.y >= 0);
    std::cout << "[OK] Trapezoid basic\n";
}

void test_array_operations() {
    Array<std::shared_ptr<Figure<D>>> arr;
    auto r = std::make_shared<Rectangle<D>>(Point<D>{0,0}, Point<D>{1,0}, Point<D>{1,1}, Point<D>{0,1});
    auto t = std::make_shared<Trapezoid<D>>(Point<D>{0,0}, Point<D>{3,0}, Point<D>{2,1}, Point<D>{1,1});
    arr.push_back(r);
    arr.push_back(std::move(t));

    assert(arr.size() == 2);
    double total = arr.totalArea();
    assert(total > 0);

    // erase
    arr.erase(0);
    assert(arr.size() == 1);

    // move
    Array<std::shared_ptr<Figure<D>>> arr2 = std::move(arr);
    assert(arr.size() == 0 && arr2.size() == 1);
    std::cout << "[OK] Array operations\n";
}

void test_array_with_concrete_type() {
    Array<Rectangle<D>> rects;
    Rectangle<D> R1(Point<D>{0,0}, Point<D>{2,0}, Point<D>{2,1}, Point<D>{0,1});
    Rectangle<D> R2(Point<D>{0,0}, Point<D>{1,0}, Point<D>{1,1}, Point<D>{0,1});
    rects.push_back(R1);
    rects.push_back(std::move(R2));
    assert(rects.size() == 2);
    double total = rects.totalArea();
    assert(total > 0);
    rects.erase(1);
    assert(rects.size() == 1);
    std::cout << "[OK] Array<Rectangle> concrete type\n";
}

int main() {
    test_rectangle_basic();
    test_rhombus_basic();
    test_trapezoid_basic();
    test_array_operations();
    test_array_with_concrete_type();
    std::cout << "All tests passed!\n";
    return 0;
}
