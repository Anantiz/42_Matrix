#include "matrix.hpp"
#include <iostream>

int main() {
    // Test case 1: Identity matrix
    Matrix<float> u1 = {
        {1., 0., 0.},
        {0., 1., 0.},
        {0., 0., 1.}
    };
    std::cout << "Matrix 1:" << std::endl;
    std::cout << u1 << std::endl;
    std::cout << "Inverse:" << std::endl;
    std::cout << u1.inverse() << std::endl;
    std::cout << "Expected:" << std::endl;
    std::cout << "[1.0, 0.0, 0.0]\n[0.0, 1.0, 0.0]\n[0.0, 0.0, 1.0]" << std::endl << std::endl;

    // Test case 2: Scalar multiple of identity
    Matrix<float> u2 = {
        {2., 0., 0.},
        {0., 2., 0.},
        {0., 0., 2.}
    };
    std::cout << "Matrix 2:" << std::endl;
    std::cout << u2 << std::endl;
    std::cout << "Inverse:" << std::endl;
    std::cout << u2.inverse() << std::endl;
    std::cout << "Expected:" << std::endl;
    std::cout << "[0.5, 0.0, 0.0]\n[0.0, 0.5, 0.0]\n[0.0, 0.0, 0.5]" << std::endl << std::endl;

    // Test case 3: General 3x3 matrix
    Matrix<float> u3 = {
        {8., 5., -2.},
        {4., 7., 20.},
        {7., 6., 1.}
    };
    std::cout << "Matrix 3:" << std::endl;
    std::cout << u3 << std::endl;
    std::cout << "Inverse:" << std::endl;
    std::cout << u3.inverse() << std::endl;
    std::cout << "Expected:" << std::endl;
    std::cout << "[0.649425287, 0.097701149, -0.655172414]\n[-0.781609195, -0.126436782, 0.965517241]\n[0.143678161, 0.074712644, -0.206896552]" << std::endl << std::endl;

    return 0;
}
