#pragma once
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <initializer_list>
#include <iomanip>
#include <vector>

#ifndef MATRIX_ALLIGNEMENT_SIZE
# define MATRIX_ALLIGNEMENT_SIZE 32
#endif

#ifndef NO_SIMD // To target architectures without SIMD support add -DNO_SIMD to the compiler flags`
# include "simd.hpp"
# ifndef THRESHOLD_SIMD_USE
#  define THRESHOLD_SIMD_USE 64
# endif
#endif


template<typename T>
class Vector;

/**
 * @brief Matrix class:
 * About operator overloading:
 *  {+, -, *, /} Will create a new matrix and return it
 *  {+=, -=, *=, /=} Will modify the current matrix in place
 *
 * Buffer information: the data buffer goes as row_1, row_2, ..., row_n,
 * in lingo the matrix is stored in `row-major` order (contiguous rows)
 */
template<typename T>
class Matrix {
protected:
    size_t          _rows;
    size_t          _cols;
    size_t          _size;
    T*              _data;
    bool            _cleanup;

public:

    /**
     * constructors
     */

    Matrix() : _rows(0), _cols(0), _size(0), _data(nullptr), _cleanup(true) {}
    Matrix(uint32_t rows, uint32_t cols);
    Matrix(const Matrix<T> &other);
    Matrix(const std::string& string_repr);
    Matrix(std::initializer_list<T> init);
    Matrix(std::initializer_list<std::initializer_list<T>> init);
    Matrix(const T** data, uint32_t rows, uint32_t cols);
    Matrix(uint32_t rows, uint32_t cols, T* data) noexcept;
    Matrix(Matrix<T> &&other) noexcept;

    ~Matrix();


    /**
     * operators scalar
     */

    Matrix<T> operator+(T scalar) const;
    Matrix<T> operator-(T scalar) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator/(T scalar) const;
    Matrix<T> &operator+=(T scalar);
    Matrix<T> &operator-=(T scalar);
    Matrix<T> &operator*=(T scalar);
    Matrix<T> &operator/=(T scalar);
    T &operator[](size_t index);
    T operator[](size_t index) const;
    T &operator()(size_t row, size_t col);
    T operator()(size_t row, size_t col) const;


    /**
     * operators matrix
     */

    Matrix<T> &operator=(const Matrix<T> &other);
    Matrix<T> operator+(const Matrix<T> &other) const;
    Matrix<T> operator-(const Matrix<T> &other) const;
    Matrix<T> operator*(const Matrix<T> &other) const;
    Matrix<T> &operator+=(const Matrix<T> &other);
    Matrix<T> &operator-=(const Matrix<T> &other);
    Matrix<T> &operator*=(const Matrix<T> &other);

    Vector<T> operator*(const Vector<T> &vector) const;
    /**
     * methods
     */

    Matrix<T> &transpose_inplace();
    Matrix<T> as_transposed() const;
    static Matrix<T> matrix_row_scaling_from_vector(const Matrix<T> &matrix, const Matrix<T> &vector);
    T dot(const Matrix<T> &other) const;
    Matrix<T> &sigmoid_inplace();
    Matrix<T> as_diagonal() const;
    T trace() const;
    inline size_t most_significant_col(size_t row) const;
    static Matrix<T> hadamard(const Matrix<T> &a, const Matrix<T> &b);
    static Matrix<T> linear_combination(const std::vector<Matrix<T>> &matrices, const std::vector<T> &coefficients);
    static Matrix<T> linear_interpolation(const Matrix<T> &a, const Matrix<T> &b, T t);
    Matrix<T> &row_echelon();
    T determinant() const;

    /**
     * misc
     */

    T* data();
    size_t rows() const;
    size_t cols() const;
    size_t size() const;
    Matrix<T> &zero();
    Matrix<T> &identity();
    Matrix<T> &fill(T value);
    Matrix<T> &randomize();
    Matrix<T> &randomize(T min, T max);
    Matrix<T> &xavier_init(double n);
    void set_cleanup(bool free_data);
    void set_at(uint32_t row, uint32_t col, T value);
    void set_at_flat(uint32_t index, T value);
    T get_at(uint32_t row, uint32_t col) const;
    T get_at_flat(uint32_t index) const;
    std::string export_string() const;
    size_t argmax_index() const;
    T argmax_value() const;
    size_t argmin_index() const;
    T argmin_value() const;
    void print_dim(const std::string &text = "") const;

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
        for (size_t i = 0; i < matrix._rows; i++) {
            for (size_t j = 0; j < matrix._cols; j++) {
                os << matrix._data[i * matrix._cols + j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

#include "constructors.hpp"
#include "overloads_scalar.hpp"
#include "overloads_matrix.hpp"
#include "general_methods.hpp"
#include "misc.hpp"
