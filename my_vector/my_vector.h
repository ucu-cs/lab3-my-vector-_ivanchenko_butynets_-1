#ifndef TEMPLATE_MY_VECTOR_H
#define TEMPLATE_MY_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <iterator>

template <typename T>
class my_vector {
private:
    size_t capacity_m{};   // actual amount of elements
    size_t data_size_m{};  // allocated memory
    T* data;
public:
    using value_type = T;

    // constructors
    my_vector() : data(new T[data_size_m]) {};
    my_vector(size_t n, T elem) : capacity_m(n), data_size_m(n), data(new T[data_size_m]) {
        for (size_t i = 0; i < n; i++) {
            data[i] = elem;
        }
    }
    template <typename It> // my_vector<T>::iterator
    my_vector(It start, It end) {
        size_t count = std::distance(start, end);
        capacity_m = count;
        data_size_m = count;
        data = new T[data_size_m];
        for (size_t i = 0; i < count; i++) {
            data[i] = *start;
            start++;
        }
    }
    my_vector(std::initializer_list<T> list) : my_vector<T>(list.begin(), list.end()) {}
    my_vector(const my_vector<T> &other) : capacity_m(other.capacity_m), data_size_m(other.data_size_m), data(new T[data_size_m]) {
        for (size_t i = 0; i < capacity_m; i++) {
            data[i] = other.data[i];
        }
    }
    my_vector(my_vector<T> &&other) noexcept : capacity_m(other.capacity_m), data_size_m(other.data_size_m), data(other.data) {
        other.capacity_m = size_t{};
        other.data_size_m = size_t{};
        other.data = nullptr;
    }

    // destructor
    ~my_vector() {
        delete[] data;
        data = nullptr;
        capacity_m = size_t{};
        data_size_m = size_t{};
    }

    // assigment operators
    my_vector<T>& operator=(const my_vector<T> &other) {
        my_vector<T> temp(other);
        swap(temp);
        return *this;
    }

    my_vector<T>& operator=(my_vector<T> &&other) noexcept {
        my_vector<T> temp(std::move(other));
        swap(temp);
        return *this;
    }

    // elements access operators
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    T& at(size_t index) const {
        if (index > capacity_m - 1) {
            throw std::out_of_range("Index is out of my_vector capacity range.");
        } else {
            return data[index];
        }
    }

    T& front() const {
        if (capacity_m > 0) {
            return data[0];
        } else {
            throw std::out_of_range("This my_vector object is empty.");
        }
    }

    T& back() const {
        if (capacity_m > 0) {
            return data[capacity_m - 1];
        } else {
            throw std::out_of_range("This my_vector object is empty.");
        }
    }

    // iterators functions
    T* begin() const {
        return data;
    }

    T* end() const {
        return data + capacity_m;
    }

    const T* cbegin() const {
        return data;
    }

    const T* cend() const {
        return data + capacity_m;
    }

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

    // helper functions
    bool is_empty() {
        return (capacity_m == size_t{});
    }

    size_t size() {
        return data_size_m;
    }

    size_t capacity() {
        return capacity_m;
    }

    void shrink_to_fit() {
        if (data_size_m > capacity_m) {
            T* tmp = new T[capacity_m];
            for (size_t i = 0; i < capacity_m; i++) {
                tmp[i] = data[i];
            }
            delete[] data;
            data = tmp;
            data_size_m = capacity_m;
        }
    }

    template <typename It>
    void reverse(It start, It end) {
        size_t count = std::distance(start, end) / 2;
        for (size_t i = 0; i < count; i++) {
             std::iter_swap(start + i, end - i - 1);
        }
    }

    void reserve(size_t new_cap) {
        if (new_cap > data_size_m) {
            resize(new_cap);
            data_size_m = new_cap;
        }
    }

    void swap(my_vector<T> &other) noexcept {
        std::swap(other.capacity_m, capacity_m);
        std::swap(other.data_size_m, data_size_m);
        std::swap(other.data, data);
    }

    void clear() {
        for (size_t i = 0; i < capacity_m; i++) {
            data[i].~T();
        }
        capacity_m = size_t{};
    }

    void resize(size_t count) {
        if (count != capacity_m) {
            T* tmp = new T[count];
            capacity_m = count < capacity_m ? count : capacity_m;
            for (size_t i = 0; i < capacity_m; i++) {
                tmp[i] = data[i];
            }
            delete[] data;
            data = tmp;
        }
    }

    void pop_back() {
        data[capacity_m - 1].~T();
        capacity_m--;
    }

    void push_back(T new_elem) {
        if (data_size_m < capacity_m + 1) {
            resize(data_size_m + data_size_m/2);
            data_size_m += data_size_m/2;
        }
        data[capacity_m] = new_elem;
        capacity_m++;
    }

    template <class... Args>
    void emplace_back(Args&&... args) {
        if (data_size_m < capacity_m + 1) {
            resize(data_size_m + data_size_m/2);
            data_size_m += data_size_m/2;
        }
        data[capacity_m] = T(std::forward<Args>(args)...);
        capacity_m++;
    }

    T* insert(T* index, T new_elem) {
        if (index >= data && index < data + capacity_m + 1) {
            size_t idx = index - data;
            if (capacity_m >= data_size_m) {
                resize(data_size_m + data_size_m/2);
                data_size_m += data_size_m/2;
            }
            for (size_t i = capacity_m; i > idx; i--) {
                data[i] = data[i-1];
            }
            data[idx] = new_elem;
            capacity_m++;
            return data + idx;
        }
        return data;
    }

    template <class It>
    T* insert (T* index, It start, It end) {
        if (index >= data && index < data + capacity_m + 1) {
            size_t idx = index - data;
            size_t count = std::distance(start, end);

            if (capacity_m + count >= data_size_m) {
                resize(data_size_m + count);
                data_size_m += count;
            }
            for (size_t i = capacity_m; i > idx; i--) {
                data[i + count - 1] = data[i-1];
            }
            for (; start < end; start++) {
                data[idx] = *start;
                idx++;
                capacity_m++;
            }
            return data + idx;
        }
        return data;
    }

    T* erase(T* index) {
        if (index >= data && index < data + capacity_m + 1) {
            size_t idx = index - data;
            data[idx].~T();
            capacity_m--;
            for (size_t i = idx; i < capacity_m; i++) {
                data[i] = data[i+1];
            }
            return data + idx - 1;
        }
        return data;
    }

    T* erase (T* start, T* end) {
        if (start >= data && end < data + capacity_m + 1) {
            size_t idx = start - data;
            size_t count = std::distance(start, end);

            for (size_t i = idx; i < idx + count; i++) {
                data[i].~T();
                capacity_m--;
            }

            for (size_t i = idx; i < capacity_m; i++) {
                data[i] = data[i + count];
            }
            return data + idx - 1;
        }
        return data;
    }

    std::strong_ordering operator<=>(my_vector<T> &other) {
        int number_of_array = std::min(capacity_m, other.capacity_m);
        for (int i = 0; i < number_of_array; i++) {
            auto result = data[i] <=> other.data[i];
            if (result != std::strong_ordering::equivalent) {
                return result;
            }
        }
        return capacity_m <=> other.capacity_m;
    }



};

#endif //TEMPLATE_MY_VECTOR_H
