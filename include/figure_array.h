#pragma once
#include <memory>
#include <iostream>
#include <concepts>
#include <type_traits>
#include <stdexcept>

// --- concept-проверки ---
// Объект должен поддерживать operator double()
template <class X>
concept HasArea = requires(X a) {
    { double(a) } -> std::convertible_to<double>;
};

// Объект должен иметь метод center() возвращающий Point<T>
template <class X>
concept HasCenter = requires(X a) {
    { a.center() };
};

// Объект должен быть печатаемым через <<
template <class X>
concept Printable = requires(std::ostream& os, X a) {
    { os << a } -> std::same_as<std::ostream&>;
};

// --- Шаблон динамического массива ---
template <class T>
class Array {
private:
    size_t size_{0};
    size_t capacity_{0};
    std::unique_ptr<T[]> data_;

    // Проверка и расширение массива
    void ensure_capacity(size_t need) {
        if (capacity_ >= need) return;
        size_t newCap = capacity_ ? capacity_ * 2 : 4;
        if (newCap < need) newCap = need;

        std::unique_ptr<T[]> tmp(new T[newCap]);
        for (size_t i = 0; i < size_; ++i)
            tmp[i] = std::move(data_[i]);

        data_ = std::move(tmp);
        capacity_ = newCap;
    }

public:
    // --- Конструкторы ---
    Array() = default;

    Array(Array&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_), data_(std::move(other.data_)) {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = std::move(other.data_);
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    // --- Методы доступа ---
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    T& operator[](size_t i) {
        if (i >= size_) throw std::out_of_range("bad index");
        return data_[i];
    }

    const T& operator[](size_t i) const {
        if (i >= size_) throw std::out_of_range("bad index");
        return data_[i];
    }

    // --- Модификаторы ---
    void push_back(const T& value) {
        ensure_capacity(size_ + 1);
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        ensure_capacity(size_ + 1);
        data_[size_++] = std::move(value);
    }

    void erase(size_t idx) {
        if (idx >= size_) throw std::out_of_range("bad index");
        for (size_t i = idx; i + 1 < size_; ++i)
            data_[i] = std::move(data_[i + 1]);
        size_--;
    }

    void clear() noexcept {
        size_ = 0;
    }

    // --- Функции печати и анализа ---
    void printAll() const {
        if (size_ == 0) {
            std::cout << "[Empty]\n";
            return;
        }

        for (size_t i = 0; i < size_; ++i) {
            const auto& v = data_[i];

            std::cout << i << ": ";
            if constexpr (Printable<decltype(*v)>)
                std::cout << *v;
            else if constexpr (Printable<T>)
                std::cout << v;
            else
                std::cout << "<no-print>";

            if constexpr (HasArea<decltype(*v)>)
                std::cout << " Area = " << double(*v);
            else if constexpr (HasArea<T>)
                std::cout << " Area = " << double(v);

            std::cout << "\n";
        }
    }

    void printCenters() const {
        if (size_ == 0) {
            std::cout << "Empty\n";
            return;
        }

        for (size_t i = 0; i < size_; ++i) {
            const auto& v = data_[i];
            std::cout << i << ": ";
            if constexpr (HasCenter<decltype(*v)>) {
                auto c = v->center();
                std::cout << "(" << c.x << ", " << c.y << ")";
            } else if constexpr (HasCenter<T>) {
                auto c = v.center();
                std::cout << "(" << c.x << ", " << c.y << ")";
            } else {
                std::cout << "<no center>";
            }
            std::cout << "\n";
        }
    }

    double totalArea() const {
    double sum = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        const auto& v = data_[i];

        if constexpr (std::is_pointer_v<T> || requires { v.operator->(); }) {
            if constexpr (HasArea<decltype(*v)>)
                sum += double(*v);
        } else {
            if constexpr (HasArea<T>)
                sum += double(v);
        }
    }
    return sum;
}

};
