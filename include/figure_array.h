#pragma once
#include <memory>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <type_traits>

template <typename T>
class Array {
private:
    size_t capacity_;
    size_t size_;
    std::shared_ptr<T[]> data_;

    void ensure_capacity(size_t minCap) {
        if (capacity_ >= minCap) return;
        size_t newCap = capacity_ ? capacity_ * 2 : 4;
        if (newCap < minCap) newCap = minCap;
        std::shared_ptr<T[]> newData(new T[newCap]);
        for (size_t i = 0; i < size_; ++i) {
            newData.get()[i] = std::move(data_.get()[i]);
        }
        data_ = std::move(newData);
        capacity_ = newCap;
    }

public:
    Array(size_t cap = 4) : capacity_(cap), size_(0) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }

    // disable copy to be explicit; copy can be implemented if needed
    Array(const Array& other) = delete;
    Array& operator=(const Array& other) = delete;

    Array(Array&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), data_(std::move(other.data_)) {
        other.capacity_ = 0;
        other.size_ = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = std::move(other.data_);
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    ~Array() = default;

    void push_back(const T& v) {
        ensure_capacity(size_ + 1);
        data_.get()[size_++] = v;
    }

    void push_back(T&& v) {
        ensure_capacity(size_ + 1);
        data_.get()[size_++] = std::move(v);
    }

    void erase(size_t idx) {
        if (idx >= size_) throw std::out_of_range("Array::erase: bad index");
        for (size_t i = idx; i + 1 < size_; ++i) {
            data_.get()[i] = std::move(data_.get()[i + 1]);
        }
        --size_;
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    T& operator[](size_t i) {
        if (i >= size_) throw std::out_of_range("Array::operator[]");
        return data_.get()[i];
    }
    const T& operator[](size_t i) const {
        if (i >= size_) throw std::out_of_range("Array::operator[]");
        return data_.get()[i];
    }

    // Print all elements with area. Works for:
    // - T is concrete figure type (has operator double and print/center)
    // - T is std::shared_ptr<Figure<...>>
    void printAll() const {
        if (size_ == 0) {
            std::cout << "Array is empty\n";
            return;
        }
        for (size_t i = 0; i < size_; ++i) {
            // if T is pointer-like (shared_ptr) dereference
            if constexpr (std::is_pointer_v<T>) {
                std::cout << i << ": " << *data_.get()[i] << " | Area: " << double(*data_.get()[i]) << "\n";
            } else if constexpr (requires { *data_.get()[i]; }) {
                // handles shared_ptr and unique_ptr
                std::cout << i << ": " << *data_.get()[i] << " | Area: " << double(*data_.get()[i]) << "\n";
            } else {
                std::cout << i << ": " << data_.get()[i] << " | Area: " << double(data_.get()[i]) << "\n";
            }
        }
    }

    void printCenters() const {
        if (size_ == 0) {
            std::cout << "Array is empty\n";
            return;
        }
        for (size_t i = 0; i < size_; ++i) {
            if constexpr (requires { data_.get()[i]->center(); }) {
                auto c = data_.get()[i]->center();
                std::cout << i << ": Center = (" << c.x << ", " << c.y << ")\n";
            } else if constexpr (requires { data_.get()[i].center(); }) {
                auto c = data_.get()[i].center();
                std::cout << i << ": Center = (" << c.x << ", " << c.y << ")\n";
            } else {
                std::cout << i << ": center not available\n";
            }
        }
    }

    double totalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            if constexpr (requires { double(*data_.get()[i]); }) {
                total += double(*data_.get()[i]);
            } else if constexpr (requires { double(data_.get()[i]); }) {
                total += double(data_.get()[i]);
            } else {
                // can't compute area
            }
        }
        return total;
    }
};
