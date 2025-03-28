#pragma once
#include "matrix.hpp"

template <typename T>
Matrix<T> Matrix<T>::operator+(T scalar) const {
    Matrix<T> result(_rows, _cols);
    for (size_t i = 0; i < _rows * _cols; i++) {
        result._data[i] = _data[i] + scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(T scalar) const {
    Matrix<T> result(_rows, _cols);
    for (size_t i = 0; i < _rows * _cols; i++) {
        result._data[i] = _data[i] - scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    Matrix<T> result(_rows, _cols);
    for (size_t i = 0; i < _rows * _cols; i++) {
        result._data[i] = _data[i] * scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T scalar) const {
    Matrix<T> result(_rows, _cols);
    for (size_t i = 0; i < _rows * _cols; i++) {
        result._data[i] = _data[i] / scalar;
    }
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(T scalar) {
    for (size_t i = 0; i < _rows * _cols; i++) {
        _data[i] += scalar;
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(T scalar) {
    for (size_t i = 0; i < _rows * _cols; i++) {
        _data[i] -= scalar;
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(T scalar) {
    #ifndef NO_SIMD
    if (_size % 8 == 0) {
        size_t i = 0;
        for (; i <= _size - 8; i += 8) {
            __m256 input_vec = _mm256_load_ps(&_data[i]);
            __m256 scalar_vec = _mm256_set1_ps(scalar);
            __m256 sum = _mm256_mul_ps(input_vec, scalar_vec);
            _mm256_store_ps(&_data[i], sum);
        }
        while (i < _size)
            _data[i++] *= scalar;
    } else {
        for (size_t i = 0; i < _size; i++) {
            _data[i] *= scalar;
        }
    }
    #else
    for (size_t i = 0; i < _size; i++) {
        _data[i] *= scalar;
    }
    #endif
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(T scalar) {
    #ifndef NO_SIMD
    if (_size % 8 == 0) {
        size_t i = 0;
        for (; i <= _size - 8; i += 8) {
            __m256 input_vec = _mm256_load_ps(&_data[i]);
            __m256 scalar_vec = _mm256_set1_ps(scalar);
            __m256 sum = _mm256_div_ps(input_vec, scalar_vec);
            _mm256_store_ps(&_data[i], sum);
        }
        while (i < _size)
            _data[i++] /= scalar;
    } else {
        for (size_t i = 0; i < _size; i++) {
            _data[i] /= scalar;
        }
    }
    #else
    for (size_t i = 0; i < _size; i++) {
        _data[i] /= scalar;
    }
    #endif
    return *this;
}

template <typename T>
T &Matrix<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Matrix index out of range");
    }
    return _data[index];
}

template <typename T>
T Matrix<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Matrix index out of range");
    }
    return _data[index];
}

template <typename T>
T &Matrix<T>::operator()(size_t row, size_t col) {
    size_t index = _cols*row + col;
    if (index >= _size) {
        throw std::out_of_range("Matrix index out of range");
    }
    return _data[index];
}

template <typename T>
T Matrix<T>::operator()(size_t row, size_t col) const {
    size_t index = _cols*row + col;
    if (index >= _size) {
        throw std::out_of_range("Matrix index out of range");
    }
    return _data[index];
}
