#include "matrix.hpp" // Matrix
#include "vector.hpp" // Vector
#include <iostream> // std::cout, std::endl

int main() {

    std::cout << "VECTOR" << std::endl;
    {
        std::cout << "ADDITION" << std::endl;
        Vector<float> a = {1.0, 2.0, 3.0};
        Vector<float> b = {3.0, 2.0, 1.0};
        Vector<float> c = a + b;
        std::cout << "a: " <<  a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "result: " << c << std::endl;
    }
    {
        std::cout << "SUBSTRACTION" << std::endl;
        Vector<float> a = {1, 2, 3};
        Vector<float> b = {3, 2, 1};
        Vector<float> c = a - b;
        std::cout << "a: " <<  a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "result: " << c << std::endl;
    }
    {
        std::cout << "SCALE" << std::endl;
        Vector<float> a = {1, 2, 3};
        Vector<float> c = a * 5;
        std::cout << "a: " <<  a << std::endl;
        std::cout << "result: a*5 " << c << std::endl;
    }
    std::cout << "\nMATRIX" << std::endl;
    {
        std::cout << "ADDITION" << std::endl;
        Matrix<float> a = {{1, 2, 3}, {4, 5, 6}};
        Matrix<float> b = {{3, 2, 1}, {6, 5, 4}};
        Matrix<float> c = a + b;
        std::cout << "a:\n" <<  a << std::endl;
        std::cout << "b:\n" << b << std::endl;
        std::cout << "result:\n" << c << std::endl;
    }
    {
        std::cout << "SUBSTRACTION" << std::endl;
        Matrix<float> a = {{1, 2, 3}, {4, 5, 6}};
        Matrix<float> b = {{3, 2, 1}, {6, 5, 4}};
        Matrix<float> c = a - b;
        std::cout << "a:\n" <<  a << std::endl;
        std::cout << "b:\n" << b << std::endl;
        std::cout << "result:\n" << c << std::endl;
    }
    {
        std::cout << "SCALE" << std::endl;
        Matrix<float> a = {{1, 2, 3}, {4, 5, 6}};
        Matrix<float> c = a * 5;
        std::cout << "a:\n" <<  a << std::endl;
        std::cout << "result: a * 5\n" << c << std::endl;
    }
}