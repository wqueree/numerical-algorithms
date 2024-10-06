#include <array>
#include <string>
#include <memory>


template <typename T, std::size_t M, std::size_t N>
class Matrix {
private:
    std::array<std::array<T, N>, M> elements_;

public:
    Matrix(std::array<std::array<T, N>, M>& elements);
    Matrix(std::array<std::array<T, N>, M>&& elements);

    T operator()(std::size_t row, std::size_t col);
    std::string to_string();
};


template <typename T, std::size_t M, std::size_t N>
Matrix<T, M, N>::Matrix(std::array<std::array<T, N>, M>& elements)
    : elements_{elements} {}


template <typename T, std::size_t M, std::size_t N>
Matrix<T, M, N>::Matrix(std::array<std::array<T, N>, M>&& elements)
    : elements_{elements} {}


template <typename T, std::size_t M, std::size_t N>
T Matrix<T, M, N>::operator()(std::size_t row, std::size_t col) {
    return elements_[row - 1][col - 1];
}


template <typename T, std::size_t M, std::size_t N>
std::string Matrix<T, M, N>::to_string() {
    std::string result {};
    const size_t format_buffer_size = 8;
    const std::string format_string {"%lf"};
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::unique_ptr<char[]> element_format_buffer = std::make_unique<char[]>(format_buffer_size);
            std::snprintf(element_format_buffer.get(), format_buffer_size, format_string.c_str(), elements_[i][j]);
            result.append(std::string(element_format_buffer.get()));
            if (j < N - 1)
                result.append(" ");
        }
        if (i < M - 1)
            result.append("\n");
    }
    return result;
}
