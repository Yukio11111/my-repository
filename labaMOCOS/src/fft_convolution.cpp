#include "fft.hpp" // Включаем вашу реализацию БПФ и ВСЕХ вспомогательных функций
#include <iostream>
#include <vector>
#include <string>

// Функция для нахождения следующей степени двойки
int next_power_of_2(int n) {
    int power = 1;
    while (power < n) {
        power <<= 1; // Умножаем на 2
    }
    return power;
}

/**
 * @brief Вычисляет дискретную свертку двух последовательностей с помощью БПФ.
 * @param x Первая последовательность (длиной M).
 * @param y Вторая последовательность (длиной L).
 * @return Результирующая последовательность свертки (длиной M + L - 1).
 */
Vector fft_convolution(Vector x, Vector y) {
    int M = x.size();
    int L = y.size();
    if (M == 0 || L == 0) return {};

    // 1. Определяем размер БПФ
    int result_size = M + L - 1;
    int fft_size = next_power_of_2(result_size);

    // 2. Дополняем сигналы нулями до fft_size
    x.resize(fft_size, {0.0, 0.0});
    y.resize(fft_size, {0.0, 0.0});

    // 3. Применяем БПФ к обоим сигналам
    Vector X = fft(x);
    Vector Y = fft(y);

    // 4. Поэлементно перемножаем спектры
    Vector U(fft_size);
    for (int i = 0; i < fft_size; ++i) {
        U[i] = X[i] * Y[i];
    }

    // 5. Применяем ОБПФ
    Vector u_padded = ifft(U);

    // 6. Обрезаем результат до нужной длины (M + L - 1)
    u_padded.resize(result_size);
    
    return u_padded;
}


int main() {
    std::cout << "--- Вычисление свертки с помощью БПФ ---" << std::endl;

    // 1. Загружаем те же последовательности, что и в предыдущем задании
    Vector x = load_signal_from_bin("convolution_data/x_sequence.bin");
    Vector y = load_signal_from_bin("convolution_data/y_sequence.bin");

    if (x.empty() || y.empty()) {
        std::cerr << "Не удалось загрузить входные последовательности." << std::endl;
        return 1;
    }
    std::cout << "Загружены последовательности: x (размер " << x.size() << ") и y (размер " << y.size() << ")" << std::endl;

    // 2. Выполняем свертку через БПФ
    std::cout << "Выполняется вычисление свертки через БПФ..." << std::endl;
    Vector u_fft = fft_convolution(x, y);
    std::cout << "Свертка вычислена. Размер результата: " << u_fft.size() << std::endl;

    // 3. Загружаем эталонный результат (вычисленный напрямую или через NumPy)
    Vector reference_conv = load_signal_from_bin("convolution_data/numpy_convolution.bin");
    if (reference_conv.empty()) {
        std::cerr << "Не удалось загрузить эталонную свертку." << std::endl;
        return 1;
    }
    
    // 4. Сравниваем наш результат с эталонным
    double difference = calculate_difference_norm(u_fft, reference_conv);

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Проверка результата:" << std::endl;
    std::cout << "Норма разности с эталонным результатом: " << std::scientific << difference << std::endl;
    
    if (difference < 1e-9) {
        std::cout << "Результат корректен! Реализация свертки через БПФ верна." << std::endl;
    } else {
        std::cout << "Внимание: обнаружено значительное расхождение с эталонным результатом." << std::endl;
    }
    
    return 0;
}