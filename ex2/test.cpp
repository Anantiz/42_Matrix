#include "vector.hpp"

int main() {

    {
        Vector<float> a({0.0});
        Vector<float> b({1.0});

        auto c = Vector<float>::linear_interpolation(a, b, 0);
        auto d = Vector<float>::linear_interpolation(a, b, 1);
        auto e = Vector<float>::linear_interpolation(a, b, 0.5);
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "Interpolation t=0 : " << c << std::endl;
        std::cout << "Interpolation t=1 : " << d << std::endl;
        std::cout << "Interpolation t=0.5 : " << e << std::endl;

        Vector<float> x({21.0});
        Vector<float> y({42.0});

        std::cout << "\nx: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        auto z = Vector<float>::linear_interpolation(x, y, 0.3);
        std::cout << "Interpolation t=0.3 : " << z << std::endl;

        Vector<float> u({2.0, 1.0});
        Vector<float> v({4.0, 2.0});
        auto w = Vector<float>::linear_interpolation(u, v, 0.3);
        std::cout << "\nu: " << u << std::endl;
        std::cout << "v: " << v << std::endl;
        std::cout << "Interpolation t=0.3 : " << w << std::endl;

        Matrix<float> m({{2.0, 1.0}, {3.0, 4.0}});
        Matrix<float> n({{20.0, 10.0}, {30.0, 40.0}});
        auto o = Matrix<float>::linear_interpolation(m, n, 0.5);
        std::cout << "\nm:\n" << m << std::endl;
        std::cout << "n:\n" << n << std::endl;
        std::cout << "Interpolation t=0.5 :\n" << o << std::endl;
    }
}