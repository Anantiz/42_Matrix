#include <iostream>

// #include "matrix.hpp"
// #include "constructors.hpp"

// int main() {
    //     Matrix<float> a(1024, 128);
    //     Matrix<float> b(128, 1024);
    //     a.randomize();
    //     b.randomize();

    //     Matrix<float> c = a * b;
    //     c.print_dim("Result");
    //     std::cout << c[0] << std::endl;
    // }


#include "simd.hpp"

int main() {

    constexpr size_t size = 1024 * 1024 * 32;
    int* buff_a = (int*)stdstd::aligned_alloc(32, size * sizeof(int));
    int* buff_b = (int*)stdstd::aligned_alloc(32, size * sizeof(int));
    for (size_t i = 0; i < size; i++) {
        buff_a[i] = i;
        buff_b[i] = 0;
    }


    if (buff_a == nullptr || buff_b == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }
    simd_memmove(buff_b, buff_a, size);
    // for (size_t i = 0; i < size; i++) {
    //     buff_b[i] = buff_a[i];
    // }
    // std::cout << "Done" << std::endl;
    std::free(buff_a);
    std::free(buff_b);
    return 0;
}