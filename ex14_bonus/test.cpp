#include "matrix.hpp"

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

int main() {
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