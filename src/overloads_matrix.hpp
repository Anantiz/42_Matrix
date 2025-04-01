#pragma once
#include "matrix.hpp"

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
    if (this == &other) return *this;
    T* new_buff = _data;
    if (_cleanup) {
        // Don't reallocate if the size is the same
        if (_size != other._size) {
            new_buff = (T*)std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( other._size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : other._size * sizeof(T));
            if (new_buff == nullptr)
                throw std::bad_alloc();
        }
    }
    else {
        // Auto-cleanup is disabled, we can't reuse the buffer
        new_buff = (T*)std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( _size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : _size * sizeof(T));
        if (new_buff == nullptr)
            throw std::bad_alloc();
    }
    for (size_t i = 0; i < other._rows * other._cols; i++) {
        new_buff[i] = other._data[i];
    }
    if (new_buff != _data)
        std::free(_data);
    _data = new_buff;
    _rows = other._rows;
    _cols = other._cols;
    _size = other._size;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    Matrix<T> result(_rows, _cols);
    #ifndef NO_SIMD
        simd_sum_into(_data, other._data, _size, result._data);
    #else
        for (size_t i = 0; i < _size; i++) {
            result._data[i] = _data[i] + other._data[i];
        }
    #endif
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    Matrix<T> result(_rows, _cols);
    #ifndef NO_SIMD
        simd_sub_into(_data, other._data, _size, result._data);
    #else
        for (size_t i = 0; i < _size; i++) {
            result._data[i] = _data[i] - other._data[i];
        }
    #endif
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
    if (_cols != other._rows) {
        throw std::invalid_argument("Mult: Matrix dimensions must match");
    }

    Matrix<T> result(_rows, other._cols);

    #ifndef NO_SIMD
        using Intrinsic = IntrinsicType<T>;
        const size_t margin = _cols - _cols % Intrinsic::BlockSize;
        const auto &A = *this;
        const auto B = other.as_transposed(); // Transpose rihgt-hand matrix such that it becomes column-major

        // Row major order, the size of a row (_cols) should thus be the inner loop
        for (size_t i = 0; i < A._rows; i++) {
            for (size_t j = 0; j < B._rows; j++) {
                // Accumulate the sum of the products between Ith row of A and Jth row of B
                simd_accumulate_product(
                    A._data + i * A._cols,
                    B._data + j * B._cols,
                    margin, _cols,
                    &result._data[i * result._cols + j]);
            }
        }
    #else
        // Standard triple-loop multiplication
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < other._cols; j++) {
                T sum = 0;
                for (size_t k = 0; k < _cols; k++) {
                    sum += _data[i * _cols + k] * other._data[k * other._cols + j];
                }
                result._data[i * other._cols + j] = sum;
            }
        }
    #endif
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    #ifndef NO_SIMD
        simd_sum_into(_data, other._data, _size, _data);
    #else
        for (size_t i = 0; i < _size; i++) {
            _data[i] += other._data[i];
        }
    #endif
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    #ifndef NO_SIMD
        simd_sub_into(_data, other._data, _size, _data);
    #else
        for (size_t i = 0; i < _size; i++) {
            _data[i] -= other._data[i];
        }
    #endif
    return *this;
}

template <typename T>
inline Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other) {
    *this = *this * other; // Matrix multiplication cannot be done in-place
    return *this;
}