#include "vector.hpp"

int main() {
    Vector<float> u1 = {0., 0., 0.};
    std::cout << u1.norm_manhattan() << ", " << u1.norm() << ", " << u1.norm_supremum() << std::endl;
    // Output: 0.0, 0.0, 0.0

    Vector<float> u2 = {1., 2., 3.};
    std::cout << u2.norm_manhattan() << ", " << u2.norm() << ", " << u2.norm_supremum() << std::endl;
    // Output: 6.0, 3.7416573867739413, 3.0

    Vector<float> u3 = {-1., -2.};
    std::cout << u3.norm_manhattan() << ", " << u3.norm() << ", " << u3.norm_supremum() << std::endl;
    // Output: 3.0, 2.23606797749979, 2.0

    return 0;
}