/**
 * @brief

 * Designed for updating the weights and biases in a neural network
 * :param mult: The matrix to multiply with, shall be mn*np compatible
 * :param add: The vector of biases, shall be mp compatible (p is 1)
 */
void MultAdd(const Matrix<T> &mult, const Matrix<T> &add) {
    if (_cols != mult._rows || _rows != add._rows) {
        throw std::invalid_argument("MultAdd: Matrix dimensions must match");
    }
    Matrix<T> result(_rows, mult._cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < mult._cols; j++) {
            for (size_t k = 0; k < _cols; k++) {
                result._data[i * mult._cols + j] += _data[i * _cols + k] * mult._data[k * mult._cols + j];
            }
            result._data[i * mult._cols + j] += add._data[i];
        }
    }
    free(_data);
    _data = result._data;
    _cols = result._cols;
    _rows = result._rows;
    _size = result._size;
}
