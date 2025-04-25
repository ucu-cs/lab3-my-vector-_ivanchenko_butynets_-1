#ifndef TEMPLATE_MY_ARRAY_H
#define TEMPLATE_MY_ARRAY_H

#include <iostream>

template<typename T, std::size_t N>
class my_array {
public:
    T data[N];
    using value_type = T;

    // elements access operators
    value_type& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    value_type& at(size_t index) {
        if (index > N - 1) {
            throw std::out_of_range("Index is out of my_array size range.");
        } else {
            return data[index];
        }
    }

    const value_type& at(size_t index) const {
        if (index > N - 1) {
            throw std::out_of_range("Index is out of my_array size range.");
        } else {
            return data[index];
        }
    }

    value_type& front() {
        if (N > 0) {
            return data[0];
        } else {
            throw std::out_of_range("This my_array object is empty.");
        }
    }

    const value_type& front() const{
        if (N > 0) {
            return data[0];
        } else {
            throw std::out_of_range("This my_array object is empty.");
        }
    }

    value_type& back() {
        if (N > 0) {
            return data[N - 1];
        } else {
            throw std::out_of_range("This my_array object is empty.");
        }
    }

    const value_type& back() const {
        if (N > 0) {
            return data[N - 1];
        } else {
            throw std::out_of_range("This my_array object is empty.");
        }
    }

    // iterators functions
    value_type* begin() const { return data; }
    value_type* end() const { return data + N; }

    const value_type* cbegin() const { return data; }
    const value_type* cend() const { return data + N; }

    std::reverse_iterator<T*> rbegin() {
        return std::reverse_iterator<T*>(end());
    }

    std::reverse_iterator<T*> rend() {
        return std::reverse_iterator<T*>(begin());
    }

    std::reverse_iterator<const T*> rcbegin() {
        return std::reverse_iterator<T*>(end());
    }

    std::reverse_iterator<const T*> rcend() {
        return std::reverse_iterator<T*>(begin());
    }

    // capacity functions
    bool is_empty() { return (N == size_t{}); }
    size_t size() { return N; }

    // helper functions
    void swap(my_array<T, N>& other) noexcept {
        for (size_t i = 0; i < N; i++) {
            std::swap(data[i], other.data[i]);
        }
    }
    // spaceship operator
    std::strong_ordering operator<=>(my_array<T, N> &other) {
        int number_of_array = std::min(size(), other.size());
        for (int i = 0; i < number_of_array; i++) {
            auto result = data[i] <=> other.data[i];
            if (result != std::strong_ordering::equivalent) {
                return result;
            }
        }
        return size() <=> other.size();
    }
};

#endif //TEMPLATE_MY_ARRAY_H
