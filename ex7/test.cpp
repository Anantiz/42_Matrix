#include "vector.hpp"

int main() {

    std::cout << "Matrix X Vector" << std::endl;
    Vector<float> v1 = {1, 2, 3};
    Matrix<float> m1(3, 3);
    m1.identity();
    m1.set_at_flat(1, 1);
    m1.set_at_flat(2, 1);

    auto result1 = m1 * v1;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "m1: \n" << m1 << std::endl;
    std::cout << "result: \n" << result1 << std::endl;

    try {
        std::cout << "\nVector X Matrix" << std::endl;
        auto result = v1 * m1;
        std::cout << "result: \n" << result << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "Matrix X Matrix" << std::endl;
    Matrix<float> u = {
        {3., -5.},
        {6., 8.}
    };
    Matrix<float> v = {
        {2., 1.},
        {4., 2.}
    };
    auto result2 = u * v;
    std::cout << "u: \n" << u << std::endl;
    std::cout << "v: \n" << v << std::endl;
    std::cout << "result: \n" << result2 << std::endl;

}