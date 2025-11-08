#pragma once
#include <type_traits>  
#include <concepts>
#include <iostream>    

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;


template <class X>
concept HasArea = requires(X a) {
    { double(a) } -> std::convertible_to<double>;
};

template <class X>
concept HasCenter = requires(X a) {
    { a.center() };
};

template <class X>
concept Printable = requires(std::ostream& os, X a) {
    { os << a } -> std::same_as<std::ostream&>;
};