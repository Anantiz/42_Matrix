#include "vector.hpp"

int main() {
    // Test cases
    Vector<float> u1 = {1., 0.};
    Vector<float> v1 = {1., 0.};
    std::cout << u1.angle_cos(v1) << std::endl; // 1.0

    Vector<float> u2 = {1., 0.};
    Vector<float> v2 = {0., 1.};
    std::cout << u2.angle_cos(v2) << std::endl; // 0.0

    Vector<float> u3 = {-1., 1.};
    Vector<float> v3 = {1., -1.};
    std::cout << u3.angle_cos(v3) << std::endl; // -1.0

    Vector<float> u4 = {2., 1.};
    Vector<float> v4 = {4., 2.};
    std::cout << u4.angle_cos(v4) << std::endl; // 1.0

    Vector<float> u5 = {1., 2., 3.};
    Vector<float> v5 = {4., 5., 6.};
    std::cout << u5.angle_cos(v5) << std::endl; // 0.974632

    return 0;
}