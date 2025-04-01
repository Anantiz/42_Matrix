#include "matrix.hpp"
#include "vector.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include "complex.hpp"

using namespace std;

template <typename T>
Matrix<T> build_projection_matrix(float fov, float ratio, float near, float far) {
    Matrix<T> projection(4, 4);
    projection.set_at(0, 0, 1 / (ratio * tan(fov / 2)));
    projection.set_at(1, 1, 1 / tan(fov / 2));
    projection.set_at(2, 2, -(far + near) / (far - near));
    projection.set_at(2, 3, -(2 * far * near) / (far - near));
    projection.set_at(3, 2, -1);
    return projection;
}

template <typename T>
void test_0() {
    cout << "VECTOR" << endl;
    {
        cout << "ADDITION" << endl;
        Vector<T> a = {1.0, 2.0, 3.0};
        Vector<T> b = {3.0, 2.0, 1.0};
        Vector<T> c = a + b;
        cout << "a: " <<  a << endl;
        cout << "b: " << b << endl;
        cout << "result: " << c << endl;
    }
    {
        cout << "SUBTRACTION" << endl;
        Vector<T> a = {1, 2, 3};
        Vector<T> b = {3, 2, 1};
        Vector<T> c = a - b;
        cout << "a: " <<  a << endl;
        cout << "b: " << b << endl;
        cout << "result: " << c << endl;
    }
    {
        cout << "SCALE" << endl;
        Vector<T> a = {1, 2, 3};
        Vector<T> c = a * 5;
        cout << "a: " <<  a << endl;
        cout << "result: a*5 " << c << endl;
    }
    cout << "\nMATRIX" << endl;
    {
        cout << "ADDITION" << endl;
        Matrix<T> a = {{1, 2, 3}, {4, 5, 6}};
        Matrix<T> b = {{3, 2, 1}, {6, 5, 4}};
        Matrix<T> c = a + b;
        cout << "a:\n" <<  a << endl;
        cout << "b:\n" << b << endl;
        cout << "result:\n" << c << endl;
    }
    {
        cout << "SUBTRACTION" << endl;
        Matrix<T> a = {{1, 2, 3}, {4, 5, 6}};
        Matrix<T> b = {{3, 2, 1}, {6, 5, 4}};
        Matrix<T> c = a - b;
        cout << "a:\n" <<  a << endl;
        cout << "b:\n" << b << endl;
        cout << "result:\n" << c << endl;
    }
    {
        cout << "SCALE" << endl;
        Matrix<T> a = {{1, 2, 3}, {4, 5, 6}};
        Matrix<T> c = a * 5;
        cout << "a:\n" <<  a << endl;
        cout << "result: a * 5\n" << c << endl;
    }
}

template <typename T>
void test_1() {
    {
        std::vector<Vector<T>> vectors;
        vectors.push_back({1, 0, 0});
        vectors.push_back({0, 1, 0});
        vectors.push_back({0, 0, 1});

        std::vector<T> coefficients = {10, -2, 0.5};

        std::cout << "Linear combination:" << std::endl;
        for (size_t i = 0; i < vectors.size(); i++) {
            std::cout << "v: " << vectors[i] << "| * " << coefficients[i] << std::endl;
        }
        std::cout << "Result:" << std::endl;

        Vector<T> v = Vector<T>::linear_combination(vectors, coefficients);
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

template <typename T>
void test_2() {

    {
        Vector<T> a({0.0});
        Vector<T> b({1.0});

        auto c = Vector<T>::linear_interpolation(a, b, 0);
        auto d = Vector<T>::linear_interpolation(a, b, 1);
        auto e = Vector<T>::linear_interpolation(a, b, 0.5);
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "Interpolation t=0 : " << c << std::endl;
        std::cout << "Interpolation t=1 : " << d << std::endl;
        std::cout << "Interpolation t=0.5 : " << e << std::endl;

        Vector<T> x({21.0});
        Vector<T> y({42.0});

        std::cout << "\nx: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        auto z = Vector<T>::linear_interpolation(x, y, 0.3);
        std::cout << "Interpolation t=0.3 : " << z << std::endl;

        Vector<T> u({2.0, 1.0});
        Vector<T> v({4.0, 2.0});
        auto w = Vector<T>::linear_interpolation(u, v, 0.3);
        std::cout << "\nu: " << u << std::endl;
        std::cout << "v: " << v << std::endl;
        std::cout << "Interpolation t=0.3 : " << w << std::endl;

        Matrix<T> m({{2.0, 1.0}, {3.0, 4.0}});
        Matrix<T> n({{20.0, 10.0}, {30.0, 40.0}});
        auto o = Matrix<float>::linear_interpolation(m, n, 0.5);
        std::cout << "\nm:\n" << m << std::endl;
        std::cout << "n:\n" << n << std::endl;
        std::cout << "Interpolation t=0.5 :\n" << o << std::endl;
    }
}

void test_3() {
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

void test_4() {
    Vector<float> u1 = {0., 0., 0.};
    std::cout << u1.norm_manhattan() << ", " << u1.norm() << ", " << u1.norm_supremum() << std::endl;
    // Output: 0.0, 0.0, 0.0

    Vector<float> u2 = {1., 2., 3.};
    std::cout << u2.norm_manhattan() << ", " << u2.norm() << ", " << u2.norm_supremum() << std::endl;
    // Output: 6.0, 3.7416573867739413, 3.0

    Vector<float> u3 = {-1., -2.};
    std::cout << u3.norm_manhattan() << ", " << u3.norm() << ", " << u3.norm_supremum() << std::endl;
    // Output: 3.0, 2.23606797749979, 2.0
}

void test_5() {
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

}

void test_6() {
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
}

void test_7() {

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

void test_8() {
    // Test cases for Matrix trace
    Matrix<float> u1 = {
        {1., 0.},
        {0., 1.}
    };
    std::cout << u1.trace() << std::endl; // Output: 2.0

    Matrix<float> u2 = {
        {2., -5., 0.},
        {4., 3., 7.},
        {-2., 3., 4.}
    };
    std::cout << u2.trace() << std::endl; // Output: 9.0

    Matrix<float> u3 = {
        {-2., -8., 4.},
        {1., -23., 4.},
        {0., 6., 4.}
    };
    std::cout << u3.trace() << std::endl; // Output: -21.0
}

void test_9() {

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

void test_10() {
    // Test case 1: Identity matrix
    Matrix<float> u1 = {
        {1., 0., 0.},
        {0., 1., 0.},
        {0., 0., 1.}
    };
    std::cout << "u1: \n" << u1.row_echelon() << std::endl;
    // Expected:
    // [1.0, 0.0, 0.0]
    // [0.0, 1.0, 0.0]
    // [0.0, 0.0, 1.0]

    // Test case 2: 2x2 invertible matrix
    Matrix<float> u2 = {
        {1., 2.},
        {3., 4.}
    };
    std::cout << "u2: \n"<< u2.row_echelon() << std::endl;
    // Expected:
    // [1.0, 0.0]
    // [0.0, 1.0]

    // Test case 3: 2x2 singular matrix
    Matrix<float> u3 = {
        {1., 2.},
        {2., 4.}
    };
    std::cout << "u3: \n" << u3.row_echelon() << std::endl;
    // Expected:
    // [1.0, 2.0]
    // [0.0, 0.0]

    // Test case 4: 3x5 matrix
    Matrix<float> u4 = {
        {8., 5., -2., 4., 28.},
        {4., 2.5, 20., 4., -4.},
        {8., 5., 1., 4., 17.}
    };
    std::cout << "u4: \n" << u4.row_echelon() << std::endl;
    // Expected:
    // [1.0, 0.625, 0.0, 0.0, -12.1666667]
    // [0.0, 0.0, 1.0, 0.0, -3.6666667]
    // [0.0, 0.0, 0.0, 1.0, 29.5]

    Matrix<float> u5 = {
        {4, 7},
        {2, 1}
    };
    std::cout << "u5: \n" << u5.row_echelon() << std::endl;
}

void test_11() {
    // Test case 1
    Matrix<float> u1 = {
        {1., -1.},
        {-1., 1.}
    };

    std::cout << "Matrix 1:" << std::endl;
    std::cout << u1 << std::endl;
    std::cout << "Determinant: " << u1.determinant() << std::endl;
    std::cout << "Expected: 0.0" << std::endl << std::endl;

    // Test case 2
    Matrix<float> u2 = {
        {2., 0., 0.},
        {0., 2., 0.},
        {0., 0., 2.}
    };
    std::cout << "Matrix 2:" << std::endl;
    std::cout << u2 << std::endl;
    std::cout << "Determinant: " << u2.determinant() << std::endl;
    std::cout << "Expected: 8.0" << std::endl << std::endl;

    // Test case 3
    Matrix<float> u3 = {
        {8., 5., -2.},
        {4., 7., 20.},
        {7., 6., 1.}
    };
    std::cout << "Matrix 3:" << std::endl;
    std::cout << u3 << std::endl;
    std::cout << "Determinant: " << u3.determinant() << std::endl;
    std::cout << "Expected: -174.0" << std::endl << std::endl;

    // Test case 4
    Matrix<float> u4 = {
        {8., 5., -2., 4.},
        {4., 2.5, 20., 4.},
        {8., 5., 1., 4.},
        {28., -4., 17., 1.}
    };
    std::cout << "Matrix 4:" << std::endl;
    std::cout << u4 << std::endl;
    std::cout << "Determinant: " << u4.determinant() << std::endl;
    std::cout << "Expected: 1032" << std::endl << std::endl;
}


void test_12() {
    // Test case 1: Identity matrix
    Matrix<float> u1 = {
        {1., 0., 0.},
        {0., 1., 0.},
        {0., 0., 1.}
    };
    std::cout << "Matrix 1:" << std::endl;
    std::cout << u1 << std::endl;
    std::cout << "Inverse:" << std::endl;
    std::cout << u1.inverse() << std::endl;
    std::cout << "Expected:" << std::endl;
    std::cout << "[1.0, 0.0, 0.0]\n[0.0, 1.0, 0.0]\n[0.0, 0.0, 1.0]" << std::endl << std::endl;

    // Test case 2: Scalar multiple of identity
    Matrix<float> u2 = {
        {2., 0., 0.},
        {0., 2., 0.},
        {0., 0., 2.}
    };
    std::cout << "Matrix 2:" << std::endl;
    std::cout << u2 << std::endl;
    std::cout << "Inverse:" << std::endl;
    std::cout << u2.inverse() << std::endl;
    std::cout << "Expected:" << std::endl;
    std::cout << "[0.5, 0.0, 0.0]\n[0.0, 0.5, 0.0]\n[0.0, 0.0, 0.5]" << std::endl << std::endl;

    // Test case 3: General 3x3 matrix
    Matrix<float> u3 = {
        {8., 5., -2.},
        {4., 7., 20.},
        {7., 6., 1.}
    };
    std::cout << "Matrix 3:" << std::endl;
    std::cout << u3 << std::endl;
    std::cout << "Inverse:" << std::endl;
    std::cout << u3.inverse() << std::endl;
    std::cout << "Expected:" << std::endl;
    std::cout << "[0.649425287, 0.097701149, -0.655172414]\n[-0.781609195, -0.126436782, 0.965517241]\n[0.143678161, 0.074712644, -0.206896552]" << std::endl << std::endl;
}

void test_13() {
    // Test case 1: Identity matrix
    Matrix<float> u1 = {
        {1., 0., 0.},
        {0., 1., 0.},
        {0., 0., 1.}
    };
    std::cout << "Matrix 1:" << std::endl;
    std::cout << u1 << std::endl;
    std::cout << "Rank: " << u1.rank() << std::endl;
    std::cout << "Expected: 3" << std::endl << std::endl;

    // Test case 2: Linearly dependent rows
    Matrix<float> u2 = {
        { 1., 2., 0., 0.},
        { 2., 4., 0., 0.},
        {-1., 2., 1., 1.}
    };
    std::cout << "Matrix 2:" << std::endl;
    std::cout << u2 << std::endl;
    std::cout << "Rank: " << u2.rank() << std::endl;
    std::cout << "Expected: 2" << std::endl << std::endl;

    // Test case 3: 4x3 matrix
    Matrix<float> u3 = {
        { 8., 5., -2.},
        { 4., 7., 20.},
        { 7., 6., 1.},
        {21., 18., 7.}
    };
    std::cout << "Matrix 3:" << std::endl;
    std::cout << u3 << std::endl;
    std::cout << "Rank: " << u3.rank() << std::endl;
    std::cout << "Expected: 3" << std::endl << std::endl;
}

void test_14() {
    {
        std::cout << "Projection matrix:" << std::endl;
        Matrix<float> projection = build_projection_matrix<float>(M_PI / 4, 1.0f, 0.1f, 100.0f);
        std::cout << projection.as_transposed() << std::endl; // Transpose it because the tester wants column-major and we are row-major
    }
    {
        std::cout << "Projection matrix:" << std::endl;
        Matrix<float> projection = build_projection_matrix<float>(M_PI / 6, 1.0f, 5.0f, 50.0f);
        std::cout << projection.as_transposed() << std::endl; // Transpose it because the tester wants column-major and we are row-major
    }
}

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr<< "Wrong argument count" << std::endl;
        return 1;
    }
    int test_number = -1;
    try {
        test_number = std::stoi(av[1]);
    } catch (std::invalid_argument &e) {
        std::cerr << "Invalid argument" << std::endl;
        return 1;
    } catch (std::out_of_range &e) {
        std::cerr << "Out of range" << std::endl;
        return 1;
    }
    switch (test_number)
    {
        case 0:
            test_0<float>();
            break;
        case 1:
            test_1<float>();
            break;
        case 2:
            test_2<float>();
            break;
        case 3:
            test_3();
            break;
        case 4:
            test_4();
            break;
        case 5:
            test_5();
            break;
        case 6:
            test_6();
            break;
        case 7:
            test_7();
            break;
        case 8:
            test_8();
            break;
        case 9:
            test_9();
            break;
        case 10:
            test_10();
            break;
        case 11:
            test_11();
            break;
        case 12:
            test_12();
            break;
        case 13:
            test_13();
            break;
        case 14:
            test_14();
            break;
        default:
            std::cerr << "Unknown test number" << std::endl;
            return 1;
    }
    return 0;
}