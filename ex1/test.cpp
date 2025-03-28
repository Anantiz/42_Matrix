#include "vector.hpp"

int main() {
    {
        std::vector<Vector<float>> vectors;
        vectors.push_back({1, 0, 0});
        vectors.push_back({0, 1, 0});
        vectors.push_back({0, 0, 1});

        std::vector<float> coefficients = {10, -2, 0.5};

        std::cout << "Linear combination:" << std::endl;
        for (size_t i = 0; i < vectors.size(); i++) {
            std::cout << "v: " << vectors[i] << "| * " << coefficients[i] << std::endl;
        }
        std::cout << "Result:" << std::endl;

        Vector<float> v = Vector<float>::linear_combination(vectors, coefficients);
        std::cout << v << std::endl;
    }

    {
        std::vector<Vector<float>> vectors;
        vectors.push_back({1, 2, 3});
        vectors.push_back({0, 10, -100});

        std::vector<float> coefficients = {10, -2};

        std::cout << "Linear combination:" << std::endl;
        for (size_t i = 0; i < vectors.size(); i++) {
            std::cout << "v: " << vectors[i] << "| * " << coefficients[i] << std::endl;
        }
        std::cout << "Result:" << std::endl;

        Vector<float> v = Vector<float>::linear_combination(vectors, coefficients);
        std::cout << v << std::endl;
    }
}