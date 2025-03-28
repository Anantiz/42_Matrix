#include "matrix.hpp"
#include <iostream>

int main() {

    Matrix<float> u1 = {
        {1., 2., 3.},
        {0., 1., 2},
        {0., 0., 1}
    };

    std::cout << "Original: " << std::endl;
    std::cout << u1 << std::endl;
    std::cout << "Transposed: " << std::endl;
    std::cout << u1.as_transposed() << std::endl;

    Matrix<float> u2 = {
        {1., 2., 3.},
        {0., 1., 2},
    };

    std::cout << "Original: " << std::endl;
    std::cout << u2 << std::endl;
    std::cout << "Transposed: " << std::endl;
    std::cout << u2.as_transposed() << std::endl;
}
