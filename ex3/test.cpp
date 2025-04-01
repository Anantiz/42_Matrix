#include "vector.hpp"

int main() {
    {
        std::cout << "VECTOR DOT" << std::endl;

        {
            Vector<float> u({0, 0});
            Vector<float> v({1, 1});
            std::cout << "u = " << u << std::endl;
            std::cout << "v = " << v << std::endl;
            std::cout << "test-1 u . v = " << u.dot(v) << std::endl;
            std::cout << "\ntest-2 v . v = " << v.dot(v) << std::endl;
        }

        Vector<float> u = {-1, 6};
        Vector<float> v = {3, 2};
        std::cout << "\nu = " << u << std::endl;
        std::cout << "v = " << v << std::endl;
        std::cout << "test-3 u . v = " << u.dot(v) << std::endl;
    }
}