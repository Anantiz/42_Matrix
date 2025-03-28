#include "vector.hpp"

int main() {
    // Test cases
    Vector<float> u1 = {0., 0., 1.};
    Vector<float> v1 = {1., 0., 0.};
    Vector<float> result1 = u1.cross_product(v1);
    std::cout << result1 << std::endl; // Output: [0, 1, 0]

    Vector<float> u2 = {1., 2., 3.};
    Vector<float> v2 = {4., 5., 6.};
    Vector<float> result2 = u2.cross_product(v2);
    std::cout << result2 << std::endl; // Output: [-3, 6, -3]

    Vector<float> u3 = {4., 2., -3.};
    Vector<float> v3 = {-2., -5., 16.};
    Vector<float> result3 = u3.cross_product(v3);
    std::cout << result3 << std::endl; // Output: [17, -58, -16]

    return 0;
}