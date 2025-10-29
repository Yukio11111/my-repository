#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <fstream>
#include <cmath>

// Используем псевдонимы и функции из предыдущих заданий
using Complex = std::complex<double>;
using Vector = std::vector<Complex>;

// Функция загрузки сигнала из бинарного файла (та же, что и раньше)
Vector load_signal_from_bin(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return {};
    }
    file.seekg(0, std::ios::end);
    long long file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    int num_doubles = file_size / sizeof(double);
    int num_samples = num_doubles / 2;
    Vector signal(num_samples);
    std::vector<double> buffer(num_doubles);
    file.read(reinterpret_cast<char*>(buffer.data()), file_size);
    for (int i = 0; i < num_samples; ++i) {
        signal[i] = Complex(buffer[2 * i], buffer[2 * i + 1]);
    }
    return signal;
}

// Функция для вычисления нормы разности L2 (та же, что и раньше)
double calculate_difference_norm(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) return -1.0;
    double accum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        accum += std::norm(v1[i] - v2[i]);
    }
    return std::sqrt(accum);
}


/**
 * @brief Вычисляет дискретную свертку двух последовательностей напрямую по формуле (3).
 * u[n] = sum_{k=0 to n} x[k] * y[n-k]
 * @param x Первая последовательность (длиной M).
 * @param y Вторая последовательность (длиной L).
 * @return Результирующая последовательность свертки (длиной M + L - 1).
 */
Vector direct_convolution(const Vector& x, const Vector& y) {
    int M = x.size();
    int L = y.size();
    if (M == 0 || L == 0) {
        return {};
    }
    
    int result_size = M + L - 1;
    // Инициализируем результирующий вектор нулями
    Vector u(result_size, {0.0, 0.0});

    // Внешний цикл по элементам результирующей последовательности
    for (int n = 0; n < result_size; ++n) {
        // Внутренний цикл для вычисления суммы
        for (int k = 0; k < M; ++k) {
            // Проверяем, что индекс для y (n-k) находится в допустимых границах
            if (n - k >= 0 && n - k < L) {
                u[n] += x[k] * y[n - k];
            }
        }
    }
    return u;
}


int main() {
    // 1. Загружаем две исходные последовательности
    Vector x = load_signal_from_bin("convolution_data/x_sequence.bin");
    Vector y = load_signal_from_bin("convolution_data/y_sequence.bin");

    if (x.empty() || y.empty()) {
        std::cerr << "Не удалось загрузить входные последовательности." << std::endl;
        return 1;
    }
    std::cout << "Загружены последовательности: x (размер " << x.size() << ") и y (размер " << y.size() << ")" << std::endl;

    // 2. Выполняем прямое вычисление свертки
    std::cout << "Выполняется прямое вычисление свертки..." << std::endl;
    Vector u = direct_convolution(x, y);
    std::cout << "Свертка вычислена. Размер результата: " << u.size() << std::endl;

    // 3. Загружаем эталонный результат из NumPy для проверки
    Vector numpy_conv = load_signal_from_bin("convolution_data/numpy_convolution.bin");
    if (numpy_conv.empty()) {
        std::cerr << "Не удалось загрузить эталонную свертку NumPy." << std::endl;
        return 1;
    }
    
    // 4. Сравниваем наш результат с эталонным
    double difference = calculate_difference_norm(u, numpy_conv);

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Проверка результата:" << std::endl;
    std::cout << "Норма разности с результатом NumPy: " << std::scientific << difference << std::endl;
    
    if (difference < 1e-9) {
        std::cout << "Результат корректен! Реализация прямого вычисления свертки верна." << std::endl;
    } else {
        std::cout << "Внимание: обнаружено значительное расхождение с эталонным результатом." << std::endl;
    }
    
    return 0;
}