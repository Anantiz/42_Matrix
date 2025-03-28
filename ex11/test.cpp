#include "matrix.hpp"
#include <iostream>

int main() {
    // Test case 1
    Matrix<float> u1 = {
        {1., -1.},
        {-1., 1.}
    };

    std::cout << "Matrix 1:" << std::endl;
    std::cout << u1 << std::endl;
    std::cout << "Determinant: " << u1.determinant() << std::endl;
    std::cout << "Expected: 0.0" << std::endl << std::endl;

    // Test case 2
    Matrix<float> u2 = {
        {2., 0., 0.},
        {0., 2., 0.},
        {0., 0., 2.}
    };
    std::cout << "Matrix 2:" << std::endl;
    std::cout << u2 << std::endl;
    std::cout << "Determinant: " << u2.determinant() << std::endl;
    std::cout << "Expected: 8.0" << std::endl << std::endl;

    // Test case 3
    Matrix<float> u3 = {
        {8., 5., -2.},
        {4., 7., 20.},
        {7., 6., 1.}
    };
    std::cout << "Matrix 3:" << std::endl;
    std::cout << u3 << std::endl;
    std::cout << "Determinant: " << u3.determinant() << std::endl;
    std::cout << "Expected: -174.0" << std::endl << std::endl;

    // Test case 4
    Matrix<float> u4 = {
        {8., 5., -2., 4.},
        {4., 2.5, 20., 4.},
        {8., 5., 1., 4.},
        {28., -4., 17., 1.}
    };
    std::cout << "Matrix 4:" << std::endl;
    std::cout << u4 << std::endl;
    std::cout << "Determinant: " << u4.determinant() << std::endl;
    std::cout << "Expected: 1032" << std::endl << std::endl;

    return 0;
}