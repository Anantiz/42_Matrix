/**
 * @brief
 * Transpose the matrix in place
 */
template <typename T>
Matrix<T> &Matrix<T>::transpose_inplace() {
    Matrix<T> result(_cols, _rows);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result._data[j * _rows + i] = _data[i * _cols + j];
        }
    }
    *this = result;
    return *this;
}

/**
 * @brief
 * Transpose the matrix and return a new matrix
 */
template <typename T>
Matrix<T> Matrix<T>::as_transposed() const {
    Matrix<T> result(_cols, _rows);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result._data[j * _rows + i] = _data[i * _cols + j];
        }
    }
    return result;
}

/**
 * @brief
 * Scales each row of the matrix with the corresponding element of the vector
 * The vector must have the same number of rows as the matrix
 */
template <typename T>
Matrix<T> Matrix<T>::matrix_row_scaling_from_vector(const Matrix<T> &matrix, const Matrix<T> &vector) {
    if (matrix._rows != vector._rows) {
        throw std::invalid_argument("row scaling:Rows dimensions must match");
    }
    Matrix<T> result(matrix._rows, matrix._cols);
    for (size_t i = 0; i < matrix._size; i++) {
        result._data[i] = matrix._data[i] * vector._data[i % vector._rows];
    }
    return result;
}

template <typename T>
T Matrix<T>::dot(const Matrix<T> &other) const {
    if (_size != other._size) {
        throw std::invalid_argument("dot:Matrix dimensions must match");
    }
    T result = 0;
    for (size_t i = 0; i < _size; i++) {
        result += _data[i] * other._data[i];
    }
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::sigmoid_inplace() {
    for (size_t i = 0; i < _rows * _cols; i++) {
        _data[i] = 1 / (1 + exp(-_data[i]));
    }
    return *this;
}

/**
 * @brief
 * WARNING: Outputs bullshit if the input is not a vector
 */
template <typename T>
Matrix<T> Matrix<T>::as_diagonal() const {
    Matrix<T> result(_size, _size);
    result.fill((T)0);
    for (size_t i = 0; i < _size; i++) {
        result._data[i * _size + i] = _data[i];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::hadamard(const Matrix<T> &a, const Matrix<T> &b) {
    if (a._rows != b._rows || a._cols != b._cols) {
        throw std::invalid_argument("hadamard:Matrix dimensions must match");
    }
    Matrix<T> result(a._rows, a._cols);
    for (size_t i = 0; i < a._rows * a._cols; i++) {
        result._data[i] = a._data[i] * b._data[i];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::linear_combination(const std::vector<Matrix<T>> &matrices, const std::vector<T> &coefficients) {
    if (matrices.size() != coefficients.size()) {
        throw std::invalid_argument("linear_combination:Vectors and coefficients must have the same size");
    }
    Matrix<T> result(matrices[0]._rows, matrices[0]._cols);
    for (size_t i = 0; i < matrices.size(); i++) {
        if (matrices[i]._rows != result._rows || matrices[i]._cols != result._cols) {
            throw std::invalid_argument("linear_combination:Vectors must have the same size");
        }
        result += matrices[i] * coefficients[i];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::linear_interpolation(const Matrix<T> &a, const Matrix<T> &b, T t) {
    if (a._rows != b._rows || a._cols != b._cols) {
        throw std::invalid_argument("linear_interpolation:Matrix dimensions must match");
    }
    Matrix<T> result(a._rows, a._cols);
    for (size_t i = 0; i < a._size; i++) {
        result._data[i] = a._data[i] * (1 - t) + b._data[i] * t;
    }
    return result;
}

template<typename T>
T Matrix<T>::trace() const {
    if (_rows != _cols) {
        throw std::invalid_argument("trace:Matrix must be square");
    }
    T result = 0;
    size_t index = 0;
    for (size_t i = 0; i < _rows; i++) {
        result += _data[index];
        index += _cols + 1;
    }
    return result;
}


template <typename T>
static void swap_rows(Matrix<T> &m, size_t a, size_t b) {
    if (a==b) return;
    T *start_a = m.data() + a * m.cols();
    T *start_b = m.data() + b * m.cols();

    for (size_t i = 0; i < m.cols(); i++) {
        std::swap(start_a[i], start_b[i]);
    }
}

/**
 * @brief
 * Substract b from a with a scaling factor
 */
template <typename T>
static void sub_row(Matrix<T> &m, size_t a, size_t b, T factor) {
    if (factor==0) return;
    T *data = m.data();
    T *start_a = data + a*m.cols();
    T *start_b = data + b*m.cols();
    for (size_t i=0;i<m.cols();i++) {
        start_a[i] -= start_b[i]*factor;
    }
}

template <typename T>
static inline T my_abs(T n){
    return n >= 0 ? n : -n;
}

template <typename T>
Matrix<T> &Matrix<T>::row_echelon() {
    size_t current_col = 0;
    size_t current_row = 0;
    while (current_row<_rows && current_col<_cols) {
        // 1. Find the larger abs value in the current column and swap the row with the first row
        //    Operating on the larger abs value reduce numerical instabilities from small divisions
        size_t pivot_row = current_row;
        // Select a row who has it's `current_col` at not zero, and the largest if possible
        for (size_t idx_row=current_row; idx_row<_rows;idx_row++) {
            if (my_abs(_data[idx_row*_cols + current_col]) > my_abs(_data[pivot_row*_cols + current_col])) {
                pivot_row = idx_row;
            }
        }
        // If all remaining row have a 0 in the current column go to the next one and check again
        if (_data[pivot_row*_cols+ current_col] == 0) {
            ++current_col;
            continue;
        }
        swap_rows(*this, current_row, pivot_row);

        // 2. Normalize the row with regards to the left-most entry
        T head_val = _data[current_row*_cols + current_col];
        if (head_val != 0 ) {
            T* ptr_start = (T*)(_data + current_row * _cols);
            for (size_t i=current_col; i < _cols; i++) {
                ptr_start[i] /= head_val;
            }
        } else {
            // Empty row, a degree of liberty
            break;
        }

        // 3. Forward substitution
        for (size_t row=current_row+1; row<_rows; row++) {
            sub_row(*this, row, current_row, _data[row*_cols + current_col]);
        }
        // 4. Back substitution
        for (ssize_t row=current_row-1; row>=0; row--) {
            sub_row(*this, row, current_row, _data[row*_cols + current_col]);
        }
        ++current_row;
        ++current_col; // Create a zero lower triangle
    }
    return *this;
}

template <typename T>
T Matrix<T>::determinant() const {
    Matrix<T> tmp(*this); // throw if not square

    std::vector<T> coefs(_cols, 1);
    int swaps=0;

    // ROW ECHELON
    {
        size_t current_col = 0;
        size_t current_row = 0;
        while (current_row<_rows && current_col<_cols) {
            // 1. Find the larger abs value in the current column and swap the row with the first row
            //    Operating on the larger abs value reduce numerical instabilities from small divisions
            size_t pivot_row = current_row;
            // Select a row who has it's `current_col` at not zero, and the largest if possible
            for (size_t idx_row=current_row; idx_row<_rows;idx_row++) {
                if (my_abs(tmp._data[idx_row*_cols + current_col]) > my_abs(tmp._data[pivot_row*_cols + current_col])) {
                    pivot_row = idx_row;
                }
            }
            // If all remaining row have a 0 in the current column go to the next one and check again
            if (tmp._data[pivot_row*_cols+ current_col] == 0) {
                coefs[current_col] = 0;
                ++current_col;
                continue;
            }
            if (current_row != pivot_row) {
                swap_rows(tmp, current_row, pivot_row);
                swaps++;
            }

            // 2. Normalize the row with regards to the left-most entry
            T head_val = tmp._data[current_row*_cols + current_col];
            if (head_val != 0 ) {
                T* ptr_start = (T*)(tmp._data + current_row * _cols);
                for (size_t i=current_col; i < _cols; i++) {
                    ptr_start[i] /= head_val;
                    coefs[current_col] = head_val;
                }
            } else {
                // Empty row, a degree of liberty
                break;
            }

            // 3. Forward substitution
            for (size_t row=current_row+1; row<_rows; row++) {
                sub_row(tmp, row, current_row, tmp._data[row*_cols + current_col]);
            }
            // 4. Back substitution
            for (ssize_t row=current_row-1; row>=0; row--) {
                sub_row(tmp, row, current_row, tmp._data[row*_cols + current_col]);
            }
            ++current_row;
            ++current_col; // Create a zero lower triangle
        }
    }

    T prod = 1;
    for (size_t i=0; i<_cols;i++) {
        prod *= tmp._data[i*_cols + i] * coefs[i];
    }
    return prod * (swaps%2 ? -1 : 1);
}