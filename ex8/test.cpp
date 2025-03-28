#include "matrix.hpp"
#include <iostream>

int main() {
    // Test cases for Matrix trace
    Matrix<float> u1 = {
        {1., 0.},
        {0., 1.}
    };
    std::cout << u1.trace() << std::endl; // Output: 2.0

    Matrix<float> u2 = {
        {2., -5., 0.},
        {4., 3., 7.},
        {-2., 3., 4.}
    };
    std::cout << u2.trace() << std::endl; // Output: 9.0

    Matrix<float> u3 = {
        {-2., -8., 4.},
        {1., -23., 4.},
        {0., 6., 4.}
    };
    std::cout << u3.trace() << std::endl; // Output: -21.0

    return 0;
}
