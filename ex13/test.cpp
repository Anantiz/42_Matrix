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
    std::cout << "Rank: " << u1.rank() << std::endl;
    std::cout << "Expected: 3" << std::endl << std::endl;

    // Test case 2: Linearly dependent rows
    Matrix<float> u2 = {
        { 1., 2., 0., 0.},
        { 2., 4., 0., 0.},
        {-1., 2., 1., 1.}
    };
    std::cout << "Matrix 2:" << std::endl;
    std::cout << u2 << std::endl;
    std::cout << "Rank: " << u2.rank() << std::endl;
    std::cout << "Expected: 2" << std::endl << std::endl;

    // Test case 3: 4x3 matrix
    Matrix<float> u3 = {
        { 8., 5., -2.},
        { 4., 7., 20.},
        { 7., 6., 1.},
        {21., 18., 7.}
    };
    std::cout << "Matrix 3:" << std::endl;
    std::cout << u3 << std::endl;
    std::cout << "Rank: " << u3.rank() << std::endl;
    std::cout << "Expected: 3" << std::endl << std::endl;

    return 0;
}
