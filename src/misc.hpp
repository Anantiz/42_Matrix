#pragma once
#include "matrix.hpp"

template <typename T>
inline T* Matrix<T>::data() {
    return _data;
}

template <typename T>
inline size_t Matrix<T>::rows() const {
    return _rows;
}

template <typename T>
inline size_t Matrix<T>::cols() const {
    return _cols;
}

template <typename T>
inline size_t Matrix<T>::size() const {
    return _size;
}

template <typename T>
Matrix<T> &Matrix<T>::zero() {
    fill((T)0);
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::identity() {
    if (_rows != _cols) {
        throw std::invalid_argument("Identity matrix must be square");
    }
    fill((T)0);
    for (size_t i = 0; i < _rows; i++) {
        _data[i * _cols + i] = (T)1;
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::fill(T value) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] = value;
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::randomize() {
    for (size_t i = 0; i < _size; i++) {
        _data[i] = (T)rand() / (T)RAND_MAX;
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::randomize(T min, T max) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] = min + (T)rand() / (float)RAND_MAX * (max - min);
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::xavier_init(double n) {
    // A nice randomizer for sigmoid activation
    T scale = sqrt(n / (_rows + _cols));
    return randomize(-scale, scale);
}

template <typename T>
void Matrix<T>::set_cleanup(bool free_data) {
    _cleanup = free_data;
}

template <typename T>
void Matrix<T>::set_at(uint32_t row, uint32_t col, T value) {
    if (row >= _rows || col >= _cols) {
        throw std::out_of_range("Matrix index out of range");
    }
    _data[row * _cols + col] = value;
}

template <typename T>
void Matrix<T>::set_at_flat(uint32_t index, T value) {
    if (index >= _size) {
        throw std::out_of_range("Matrix index out of range");
    }
    _data[index] = value;
}

template <typename T>
T Matrix<T>::get_at(uint32_t row, uint32_t col) const {
    if (row >= _rows || col >= _cols) {
        throw std::out_of_range("Matrix index out of range");
    }
    return _data[row * _cols + col];
}

template <typename T>
T Matrix<T>::get_at_flat(uint32_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Matrix index out of range");
    }
    return _data[index];
}

template <typename T>
std::string Matrix<T>::export_string() const {
    std::string result = std::to_string(_rows) + " " + std::to_string(_cols) + " ";
    for (size_t i = 0; i < _size; i++) {
        result += std::to_string(_data[i]) + " ";
    }
    return result;
}

template <typename T>
size_t Matrix<T>::argmax_index() const {
    T max = _data[0];
    size_t index = 0;
    for (size_t i = 1; i < _size; i++) {
        if (_data[i] > max) {
            max = _data[i];
            index = i;
        }
    }
    return index;
}

template <typename T>
T Matrix<T>::argmax_value() const {
    T max = _data[0];
    for (size_t i = 1; i < _size; i++) {
        if (_data[i] > max) {
            max = _data[i];
        }
    }
    return max;
}

template <typename T>
size_t Matrix<T>::argmin_index() const {
    T min = _data[0];
    size_t index = 0;
    for (size_t i = 1; i < _size; i++) {
        if (_data[i] < min) {
            min = _data[i];
            index = i;
        }
    }
    return index;
}

template <typename T>
T Matrix<T>::argmin_value() const {
    T min = _data[0];
    for (size_t i = 1; i < _size; i++) {
    if (_data[i] < min) {
            min = _data[i];
        }
    }
    return min;
}


template <typename T>
void Matrix<T>::print_dim(const std::string &text) const {
    std::cout << text << ": [r " << _rows << ", c " << _cols << "]" << std::endl;
}

// template <typename T>
// std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
//     for (size_t i = 0; i < matrix._rows; i++) {
//         for (size_t j = 0; j < matrix._cols; j++) {
//             os << matrix._data[i * matrix._cols + j] << " ";
//         }
//         os << std::endl;
//     }
//     return os;
// }