#pragma once
#include "matrix.hpp"
#include <cstdlib>

/**
 * @brief Matrix class:
 * - A matrix class that can be used for any data type
 * - The data type is defined by the template parameter, T
 * :param: rows
 * :param: cols
 */
template <typename T>
Matrix<T>::Matrix(uint32_t rows, uint32_t cols) : _rows(rows), _cols(cols), _size(rows * cols) {
    _cleanup = true;
    _data = (T*) std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( _size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : _size * sizeof(T));
    if (_data == nullptr) {
        throw std::bad_alloc();
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other) : _rows(other._rows), _cols(other._cols), _size(other._size) {
    _cleanup = true;
    _data = (T*) std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( _size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : _size * sizeof(T));
    if (_data == nullptr) {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < _rows * _cols; i++) {
        _data[i] = other._data[i];
    }
}

template <typename T>
Matrix<T>::Matrix(const std::string& string_repr) {
    std::istringstream iss(string_repr);
    iss >> _rows >> _cols;
    _size = _rows * _cols;
    _cleanup = true;
    _data = (T*) std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( _size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : _size * sizeof(T));
    if (_data == nullptr) {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < _size; i++) {
        iss >> _data[i];
    }
}

/**
 * @brief
 * Constructor for initializer lists
 * :param init: initializer list
 * :return: Matrix object
 * :throws: std::bad_alloc
 */
template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> init) : _rows(init.size()), _cols(1), _size(init.size()) {
    _cleanup = true;
    _data = (T*) std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( _size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : _size * sizeof(T));
    if (_data == nullptr) {
        throw std::bad_alloc();
    }
    size_t i = 0;
    for (const T& val : init) {
        _data[i++] = val;
    }
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) : _rows(init.size()), _cols(init.begin()->size()), _size(_rows * _cols), _cleanup(true) {
    _data = (T*) std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( _size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : _size * sizeof(T));
    if (_data == nullptr) {
        throw std::bad_alloc();
    }
    size_t i = 0;
    for (const std::initializer_list<T>& row : init) {
        if (row.size() != _cols) {
            std::free(_data);
            _data = nullptr;
            throw std::invalid_argument("All rows must have the same number of columns");
        }
        for (const T& val : row) {
            _data[i++] = (T)val;
        }
    }
}

/**
 * @brief
 * Constructor from 2D array
 * :param data: 2D array of data
 * :param rows: number of rows
 * :param cols: number of columns
 * :return: Matrix object
 * :throws: std::bad_alloc
 * @warning: The data pointer must be the same shape as the rows and cols
 */
template <typename T>
Matrix<T>::Matrix(const T** data, uint32_t rows, uint32_t cols): _rows(rows), _cols(cols), _size(rows * cols), _cleanup(true) {
    _data = (T*) std::aligned_alloc(MATRIX_ALLIGNEMENT_SIZE, ( _size * sizeof(T))<MATRIX_ALLIGNEMENT_SIZE? MATRIX_ALLIGNEMENT_SIZE : _size * sizeof(T));
    if (_data == nullptr) {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            _data[i * cols + j] = data[i][j];
        }
    }
}

/**
 * !! DANGEROUS !!
 * Constructor from raw data, takes ownership of the data
 * (If only a language existed where the compiler would enforce data ownership to avoid mistakes)
 * الحمد لله، أنا الآن مالك في روح Rust!
*/
template <typename T>
Matrix<T>::Matrix(uint32_t rows, uint32_t cols, T* data) noexcept : _rows(rows), _cols(cols), _size(rows * cols) {
    _cleanup = true;
    _data = data; // Take ownership of the data pointer
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept : _rows(other._rows), _cols(other._cols), _size(other._size) {
    std::cerr << "Move constructor" << std::endl;
    _cleanup = other._cleanup;
    _data = other._data;
    other._data = nullptr;  // *Pirate noises*
}

/**
 * @brief
 * Matrix class destructor
 * - Free the memory if the cleanup flag is set
 * Sometimes we want to isolate the data from the matrix object for performance reasons
 * In that case the matrix should not free the data
 */
template <typename T>
Matrix<T>::~Matrix() {
    if (_cleanup) std::free(_data);
}