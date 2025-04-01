#include "matrix.hpp"
#include <iostream>

int main() {
    // Test case 1: Identity matrix
    Matrix<float> u1 = {
        {1., 0., 0.},
        {0., 1., 0.},
        {0., 0., 1.}
    };
    std::cout << "u1: \n" << u1.row_echelon() << std::endl;
    // Expected:
    // [1.0, 0.0, 0.0]
    // [0.0, 1.0, 0.0]
    // [0.0, 0.0, 1.0]

    // Test case 2: 2x2 invertible matrix
    Matrix<float> u2 = {
        {1., 2.},
        {3., 4.}
    };
    std::cout << "u2: \n"<< u2.row_echelon() << std::endl;
    // Expected:
    // [1.0, 0.0]
    // [0.0, 1.0]

    // Test case 3: 2x2 singular matrix
    Matrix<float> u3 = {
        {1., 2.},
        {2., 4.}
    };
    std::cout << "u3: \n" << u3.row_echelon() << std::endl;
    // Expected:
    // [1.0, 2.0]
    // [0.0, 0.0]

    // Test case 4: 3x5 matrix
    Matrix<float> u4 = {
        {8., 5., -2., 4., 28.},
        {4., 2.5, 20., 4., -4.},
        {8., 5., 1., 4., 17.}
    };
    std::cout << "u4: \n" << u4.row_echelon() << std::endl;
    // Expected:
    // [1.0, 0.625, 0.0, 0.0, -12.1666667]
    // [0.0, 0.0, 1.0, 0.0, -3.6666667]
    // [0.0, 0.0, 0.0, 1.0, 29.5]

    Matrix<float> u5 = {
        {4, 7},
        {2, 1}
    };
    std::cout << "u5: \n" << u5.row_echelon() << std::endl;

    return 0;
}