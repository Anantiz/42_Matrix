#include "matrix.hpp"

template<typename T>
class Vector {

private:

    Matrix<T> _data; // 0 efforts provided, go screw yourself if you are not happy with this

public:

    Vector() : _data() {}
    Vector(const Matrix<T> &data) : _data(data) {}
    Vector(uint32_t size) : _data(size, 1) {}
    Vector(const Vector<T> &other) : _data(other._data) {}

    // Constructor for initializer lists
    Vector(std::initializer_list<T> init) {
        _data = Matrix<T>(init);
    }

    Vector(const T* data, size_t n) {
        _data = Matrix<T>(n, 1);
        for (size_t i = 0; i < n; i++) {
            _data.set_at_flat(i, data[i]);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector<T> &vector) {
        for (size_t i = 0; i < vector._data.size(); i++) {
            os << vector._data.get_at_flat(i) << " ";
        }
        return os;
    }

    Vector<T> &zero() {
        _data.zero();
        return *this;
    }

    Vector<T> operator+(const Vector<T> &other) const {
        return Vector<T>(_data + other._data);
    }

    Vector<T> operator-(const Vector<T> &other) const {
        return Vector<T>(_data - other._data);
    }

    Vector<T> operator*(T scalar) const {
        return Vector<T>(_data * scalar);
    }

    Vector<T> operator/(T scalar) const {
        return Vector<T>(_data / scalar);
    }

    Vector<T> &operator+=(const Vector<T> &other) {
        _data += other._data;
        return *this;
    }

    Vector<T> &operator-=(const Vector<T> &other) {
        _data -= other._data;
        return *this;
    }

    Matrix<T> operator*(const Matrix<T> &matrix) const {
        std::cerr << "WARNING: Vector X Matrix is not a standard operation; returning Matrix X Vector instead, switch operands position to fix" << std::endl;
        if (_data.size() != matrix.rows()) {
            throw std::invalid_argument("Vector and Matrix dimensions must match");
        }
        Matrix<T> result(1, matrix.cols());
        for (size_t i = 0; i < matrix.cols(); i++) {
            T sum = 0;
            for (size_t j = 0; j < _data.size(); j++) {
                sum += _data.get_at_flat(j) * matrix.get_at(j, i);
            }
            result.set_at_flat(i, sum);
        }
        return result;
    }

    T &operator[](size_t index) {
        return _data.get_at_flat(index);
    }

    T operator[](size_t index) const {
        return _data.get_at_flat(index);
    }

    void set_at(size_t index, T value) {
        _data.set_at_flat(index, value);
    }

    size_t size() const {
        return _data.size();
    }

    static Vector<T> linear_combination(const std::vector<Vector<T>> &vectors, const std::vector<T> &coefficients) {
        if (vectors.size() != coefficients.size()) {
            throw std::invalid_argument("Vectors and coefficients must have the same size");
        }
        Vector<T> result(vectors[0].size());
        for (size_t i = 0; i < vectors.size(); i++) {
            if (vectors[i].size() != result.size()) {
                throw std::invalid_argument("Vectors must have the same size");
            }
            result += vectors[i] * coefficients[i];
        }
        return result;
    }

    static Vector<T> linear_interpolation(const Vector<T> &a, const Vector<T> &b, T t) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        return a * (1 - t) + b * t;
    }

    T dot(const Vector<T> &other) const {
        return _data.dot(other._data);
    }

    T norm() const {
        // pow 0.5 cuz the school subject doens't allow sqrt
        // and think we are too stupid to know that pow(, 0.5) is sqrt
        // so it wants us to learn it here even tho everyone knows this at 10 years old
        return std::pow(dot(*this), 0.5);
    }

    T norm_manhattan() const {
        T sum = 0;
        for (size_t i = 0; i < _data.size(); i++) {
            sum += _data[i] > 0 ? _data[i] : -_data[i];
        }
        return sum;
    }

    T norm_supremum() const {
        T max = 0;
        for (size_t i = 0; i < _data.size(); i++) {
            T abs = _data[i] > 0 ? _data[i] : -_data[i];
            if (abs > max) {
                max = abs;
            }
        }
        return max;
    }

    double angle_cos(const Vector<T> &other) const {
        // Def: A⋅B=∥A∥⋅∥B∥⋅cos(θ)
        // Thus: cos(θ) = A⋅B / (∥A∥⋅∥B∥)
        return this->dot(other) / (this->norm() * other.norm());
    }

    Vector<T> cross_product(const Vector<T>&other) const {
        if (this->size() != 3 || other.size() != 3) {
            throw std::invalid_argument("Cross product is only defined for 3D vectors");
        }
        return Vector<T>({
            (*this)[1] * other[2] - (*this)[2] * other[1],
            (*this)[2] * other[0] - (*this)[0] * other[2],
            (*this)[0] * other[1] - (*this)[1] * other[0]
        });
    }
};

template<typename T>
Vector<T> Matrix<T>::operator*(const Vector<T> &vector) const {
    if (_cols != vector.size()) {
        throw std::invalid_argument("Matrix and Vector dimensions must match");
    }
    Vector<T> result(_rows);
    for (size_t i = 0; i < _rows; i++) {
        T sum = 0;
        for (size_t k = 0; k < _cols; k++) {
            sum += _data[i * _cols + k] * vector[k];
        }
        result.set_at(i, sum);
    }
    return result;
}
