#pragma once

#include <immintrin.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>

/**
 * @brief
 * SIMD optimized functions for memory operations on arrays, supportded types are:
 * - int32_t
 * - float
 * - double
 * The functions are implemented using AVX2 intrinsics
 * @warning:
 * The functions are not safe:
 * - They do not check for memory alignment
 * - They do not check for nullptr
 *
 */

/**
 * INTRINSICS TYPES
 *
 */

template<typename T>
struct IntrinsicType;

template<>
struct IntrinsicType<int32_t> {
    using VecType = __m256i;
    static constexpr size_t BlockSize = 8;

    static inline VecType load(const int* ptr) {
        return _mm256_load_si256(reinterpret_cast<const __m256i*>(ptr));
    }
    static inline VecType setzero() {
        return _mm256_setzero_si256();
    }
    static inline VecType Set1(int a) {
        return _mm256_set1_epi32(a);
    }
    static inline VecType add(VecType a, VecType b) {
        return _mm256_add_epi32(a, b);
    }
    static inline VecType sub(VecType a, VecType b) {
        return _mm256_sub_epi32(a, b);
    }
    static inline VecType mult(VecType a, VecType b) {
        return _mm256_mullo_epi32(a, b);
    }
    static inline VecType fmadd(VecType a, VecType b, VecType c) {
        return _mm256_add_epi32(_mm256_mullo_epi32(a, b), c);
    }
    static inline void store(int* ptr, VecType a) {
        _mm256_store_si256(reinterpret_cast<__m256i*>(ptr), a);
    }
};


// NO `_mm256_mullo_epi64` in AVX2, too lazy to fix right now
// template<>
// struct IntrinsicType<int64_t> {
//     using VecType = __m256i;
//     static constexpr size_t BlockSize = 4;

//     static inline VecType load(const __m256i* ptr) {
//         return _mm256_load_si256(ptr);
//     }
//     static inline VecType setzero() {
//         return _mm256_setzero_si256();
//     }
//     static inline VecType add(VecType a, VecType b) {
//         return _mm256_add_epi64(a, b);
//     }
//     static inline VecType mult(VecType a, VecType b) {
//         return _mm256_mullo_epi64(a, b);
//     }
//     static inline void store(__m256i* ptr, VecType a) {
//         _mm256_store_si256(ptr, a);
//     }
// };

template<>
struct IntrinsicType<float> {
    using VecType = __m256;
    static constexpr size_t BlockSize = 8;

    static inline VecType load(const float* ptr) {
        return _mm256_load_ps(ptr);
    }
    static inline VecType setzero() {
        return _mm256_setzero_ps();
    }
    static inline VecType Set1(float a) {
        return _mm256_set1_ps(a);
    }
    static inline VecType add(VecType a, VecType b) {
        return _mm256_add_ps(a, b);
    }
    static inline VecType sub(VecType a, VecType b) {
        return _mm256_sub_ps(a, b);
    }
    static inline VecType mult(VecType a, VecType b) {
        return _mm256_mul_ps(a, b);
    }
    static inline VecType fmadd(VecType a, VecType b, VecType c) {
        return _mm256_fmadd_ps(a, b, c);
    }
    static inline void store(float* ptr, VecType a) {
        _mm256_store_ps(ptr, a);
    }
};

template<>
struct IntrinsicType<double> {
    using VecType = __m256d;
    static constexpr size_t BlockSize = 4;

    static inline VecType load(const double* ptr) {
        return _mm256_load_pd(ptr);
    }
    static inline VecType setzero() {
        return _mm256_setzero_pd();
    }
    static inline VecType Set1(double a) {
        return _mm256_set1_pd(a);
    }
    static inline VecType add(VecType a, VecType b) {
        return _mm256_add_pd(a, b);
    }
    static inline VecType sub(VecType a, VecType b) {
        return _mm256_sub_pd(a, b);
    }
    static inline VecType mult(VecType a, VecType b) {
        return _mm256_mul_pd(a, b);
    }
    static inline VecType fmadd(VecType a, VecType b, VecType c) {
        return _mm256_fmadd_pd(a, b, c);
    }
    static inline void store(double* ptr, VecType a) {
        _mm256_store_pd(ptr, a);
    }
};

/**
 * METHODS
 *
 */

/**
 * @brief
 * Memove with vectorized instructions, the function is safe to use with overlapping memory
 * :param dest: dest array
 * :param src: src array
 * :param size: the full size of the arrays
 * :return: void
 */
// template<typename T>
// void simd_memmove(T* dest, const T* src, size_t size) {
//     using Intrinsic = IntrinsicType<T>;
//     using VecType = typename Intrinsic::VecType;

//     if (dest > src) {  // Copy backwards
//         if (size < Intrinsic::BlockSize || dest - src < Intrinsic::BlockSize) {
//             for (ssize_t k = size; k > 0; k--) {
//                 dest[k - 1] = src[k - 1];  // Fix out-of-bounds error
//             }
//             return;
//         } else {
//             ssize_t k = size - Intrinsic::BlockSize;
//             for (; k >= Intrinsic::BlockSize; k -= Intrinsic::BlockSize) {  // Fix boundary condition
//                 VecType src_vec = Intrinsic::load(src + k);
//                 Intrinsic::store(dest + k, src_vec);
//             }
//             for (; k > 0; k--) {  // Fix missing src[0]
//                 dest[k - 1] = src[k - 1];
//             }
//         }
//     } else {  // Copy forward
//         if (size < Intrinsic::BlockSize || src - dest < Intrinsic::BlockSize) {
//             for (size_t k = 0; k < size; k++) {
//                 dest[k] = src[k];
//             }
//             return;
//         } else {
//             size_t margin = size - size % Intrinsic::BlockSize;
//             size_t k = 0;

//             for (; k < margin; k += Intrinsic::BlockSize) {
//                 VecType src_vec = Intrinsic::load(src + k);
//                 Intrinsic::store(dest + k, src_vec);
//             }
//             for (; k < size; k++) {
//                 dest[k] = src[k];
//             }
//         }
//     }
// }

/**
 * @brief
 * Accumulate the sum of the products between two arrays
 * :param A: first array
 * :param B: second array
 * :param margin: the last index for vectorized computation, can be either provided or left to be computed
 * :param size: the full size of the arrays
 * :param result: the result of the accumulation
 * :return: void
 */
template <typename T>
void simd_accumulate_product(const T* A, const T* B, size_t margin, size_t size, T*result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    T sum = 0;
    if (size >= Intrinsic::BlockSize) {
        VecType sum_vec = Intrinsic::setzero();
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            sum_vec = Intrinsic::fmadd(a_vec, b_vec, sum_vec);
        }
        alignas(32) T tmp[Intrinsic::BlockSize];
        Intrinsic::store(tmp, sum_vec);
        for (size_t i = 0; i < Intrinsic::BlockSize; i++) {
            sum += tmp[i];
        }
    }
    for (; k < size; k++) {
        sum += A[k] * B[k];
    }
    *result = sum;
}
template <typename T>
void simd_accumulate_product(const T* A, const T* B, size_t size, T*result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t margin = size - size % Intrinsic::BlockSize;
    size_t k = 0;
    T sum = 0;
    if (size >= Intrinsic::BlockSize) {
        VecType sum_vec = Intrinsic::setzero();
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            sum_vec = Intrinsic::fmadd(a_vec, b_vec, sum_vec);
        }
        alignas(32) T tmp[Intrinsic::BlockSize];
        Intrinsic::store(tmp, sum_vec);
        for (size_t i = 0; i < Intrinsic::BlockSize; i++) {
            sum += tmp[i];
        }
    }
    for (; k < size; k++) {
        sum += A[k] * B[k];
    }
    *result = sum;
}

/**
 * @brief
 * Compute the sum of an array
 * :param A: the array
 * :param margin: the last index for vectorized computation, can be either provided or left to be computed
 * :param size: the full size of the array
 * :param result: the result of the accumulation
 * :return: void
 */
template<typename T>
void simd_sum(const T* A, size_t margin, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    T sum = 0;
    if (size >= Intrinsic::BlockSize) {
        VecType sum_vec = Intrinsic::setzero();
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            sum_vec = Intrinsic::add(a_vec, sum_vec);
        }
        alignas(32) T tmp[Intrinsic::BlockSize];
        Intrinsic::store(tmp, sum_vec);
        for (size_t i = 0; i < Intrinsic::BlockSize; i++) {
            sum += tmp[i];
        }
    }
    for (; k < size; k++) {
        sum += A[k];
    }
    *result = sum;
}
template<typename T>
void simd_sum(const T* A, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t margin = size - size % Intrinsic::BlockSize;
    size_t k = 0;
    T sum = 0;
    if (size >= Intrinsic::BlockSize) {
        VecType sum_vec = Intrinsic::setzero();
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            sum_vec = Intrinsic::add(a_vec, sum_vec);
        }
        alignas(32) T tmp[Intrinsic::BlockSize];
        Intrinsic::store(tmp, sum_vec);
        for (size_t i = 0; i < Intrinsic::BlockSize; i++) {
            sum += tmp[i];
        }
    }
    for (; k < size; k++) {
        sum += A[k];
    }
    *result = sum;
}

/**
 * @brief
 * Stores the product of two arrays into a third array
 * :param A: first array
 * :param B: second array
 * :param margin: the last index for vectorized computation, can be either provided or left to be computed
 * :param size: the full size of the arrays
 * :param result: the result of the product
 * :return: void
 */
template<typename T>
void simd_product_into(const T* A, const T* B, size_t margin, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            VecType mult_vec = Intrinsic::mult(a_vec, b_vec);
            Intrinsic::store(result + k, mult_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] * B[k];
    }
}
template<typename T>
void simd_product_into(const T* A, const T* B, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t margin = size - size % Intrinsic::BlockSize;
    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            VecType mult_vec = Intrinsic::mult(a_vec, b_vec);
            Intrinsic::store(result + k, mult_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] * B[k];
    }
}

/**
 * @brief
 * Stores the sum of two arrays into a third array
 * :param A: first array
 * :param B: second array
 * :param margin: the last index for vectorized computation, can be either provided or left to be computed
 * :param size: the full size of the arrays
 * :param result: the result of the computation
 * :return: void
 */
template<typename T>
void simd_sum_into(const T* A, const T* B, size_t margin, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            VecType sum_vec = Intrinsic::add(a_vec, b_vec);
            Intrinsic::store(result + k, sum_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] + B[k];
    }
}
template<typename T>
void simd_sum_into(const T* A, const T* B, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t margin = size - size % Intrinsic::BlockSize;
    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            VecType sum_vec = Intrinsic::add(a_vec, b_vec);
            Intrinsic::store(result + k, sum_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] + B[k];
    }
}

/**
 * @brief
 * Stores the substraction of two arrays into a third array
 * :param A: first array
 * :param B: second array
 * :param margin: the last index for vectorized computation, can be either provided or left to be computed
 * :param size: the full size of the arrays
 * :param result: the result of the computation
 * :return: void
 */
template<typename T>
void simd_sub_into(const T* A, const T* B, size_t margin, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            VecType sub_vec = Intrinsic::sub(a_vec, b_vec);
            Intrinsic::store(result + k, sub_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] + B[k];
    }
}
template<typename T>
void simd_sub_into(const T* A, const T* B, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t margin = size - size % Intrinsic::BlockSize;
    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        for (; k < margin; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType b_vec = Intrinsic::load(B + k);
            VecType sub_vec = Intrinsic::sub(a_vec, b_vec);
            Intrinsic::store(result + k, sub_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] + B[k];
    }
}

/**
 * @brief
 * Scale an array by a scalar and store the result into a second array
 * :param A: the array
 * :param scalar: the scalar
 * :param size: the full size of the array
 * :param result: the result of the computation
 * :return: void
 */
template<typename T>
void simd_mul_scalar(const T* A, T scalar, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        VecType scalar_vec = Intrinsic::Set1(scalar);
        for (; k < size; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType mult_vec = Intrinsic::mult(a_vec, scalar_vec);
            Intrinsic::store(result + k, mult_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] * scalar;
    }
}

/**
 * @brief
 * Add a scalar to the array
 * :param A: the array
 * :param scalar: the scalar
 * :param size: the full size of the array
 * :param result: the result of the computation
 * :return: void
 */
template<typename T>
void simd_add_scalar(const T* A, T scalar, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        VecType scalar_vec = Intrinsic::Set1(scalar);
        for (; k < size; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType sum_vec = Intrinsic::add(a_vec, scalar_vec);
            Intrinsic::store(result + k, sum_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] + scalar;
    }
}

/**
 * @brief
 * Subtract a scalar from the array
 * :param A: the array
 * :param scalar: the scalar
 * :param size: the full size of the array
 * :param result: the result of the computation
 * :return: void
 */
template<typename T>
void simd_sub_scalar(const T* A, T scalar, size_t size, T* result) {
    using Intrinsic = IntrinsicType<T>;
    using VecType = typename Intrinsic::VecType;

    size_t k = 0;
    if (size >= Intrinsic::BlockSize) {
        VecType scalar_vec = Intrinsic::Set1(scalar);
        for (; k < size; k += Intrinsic::BlockSize) {
            VecType a_vec = Intrinsic::load(A + k);
            VecType sub_vec = Intrinsic::sub(a_vec, scalar_vec);
            Intrinsic::store(result + k, sub_vec);
        }
    }
    for (; k < size; k++) {
        result[k] = A[k] - scalar;
    }
}
