#pragma once
#include <type_traits>
#include <concepts>
#include <iostream>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
    T x{};
    T y{};
    Point() = default;
    Point(T _x, T _y) : x(_x), y(_y) {}

    Point<T> operator+(const Point<T>& o) const { return { x + o.x, y + o.y }; }
    Point<T> operator-(const Point<T>& o) const { return { x - o.x, y - o.y }; }
    Point<T> operator/(double d) const { return { static_cast<T>(x / d), static_cast<T>(y / d) }; }
};

template <Scalar T>
inline std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
