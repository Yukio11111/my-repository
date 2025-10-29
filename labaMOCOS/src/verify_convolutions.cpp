#include "fft.hpp" // Ваш заголовочный файл со всеми функциями (БПФ, загрузка, норма)
#include <iostream>
#include <vector>
#include <chrono> // Для измерения времени

// --- Копируем сюда реализацию ПРЯМОЙ свертки из п. 5 ---
Vector direct_convolution(const Vector& x, const Vector& y) {
    int M = x.size();
    int L = y.size();
    if (M == 0 || L == 0) return {};
    int result_size = M + L - 1;
    Vector u(result_size, {0.0, 0.0});
    for (int n = 0; n < result_size; ++n) {
        for (int k = 0; k < M; ++k) {
            if (n - k >= 0 && n - k < L) {
                u[n] += x[k] * y[n - k];
            }
        }
    }
    return u;
}

// --- Копируем сюда реализацию БЫСТРОЙ свертки из п. 6 ---
int next_power_of_2(int n) {
    int power = 1;
    while (power < n) { power <<= 1; }
    return power;
}

Vector fft_convolution(Vector x, Vector y) {
    int M = x.size();
    int L = y.size();
    if (M == 0 || L == 0) return {};
    int result_size = M + L - 1;
    int fft_size = next_power_of_2(result_size);
    x.resize(fft_size, {0.0, 0.0});
    y.resize(fft_size, {0.0, 0.0});
    Vector X = fft(x);
    Vector Y = fft(y);
    Vector U(fft_size);
    for (int i = 0; i < fft_size; ++i) {
        U[i] = X[i] * Y[i];
    }
    Vector u_padded = ifft(U);
    u_padded.resize(result_size);
    return u_padded;
}


int main() {
    // 1. Загрузка данных
    std::cout << "Загрузка больших сигналов (M=1024, L=1024)..." << std::endl;
    Vector x = load_signal_from_bin("verification_large_conv/x_1024.bin");
    Vector y = load_signal_from_bin("verification_large_conv/y_1024.bin");
    Vector reference_conv = load_signal_from_bin("verification_large_conv/numpy_conv_1024.bin");

    if (x.empty() || y.empty() || reference_conv.empty()) {
        std::cerr << "Ошибка загрузки одного из файлов." << std::endl;
        return 1;
    }
    std::cout << "Данные успешно загружены." << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    // 2. Проверка процедуры из п. 6 (Быстрая свертка на БПФ)
    std::cout << "Проверка п. 6: Свертка на основе БПФ..." << std::endl;
    auto start_fft = std::chrono::high_resolution_clock::now();
    Vector u_fft = fft_convolution(x, y);
    auto end_fft = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_fft = end_fft - start_fft;

    double diff_fft = calculate_difference_norm(u_fft, reference_conv);
    std::cout << "Время выполнения: " << duration_fft.count() << " мс" << std::endl;
    std::cout << "Норма разности с NumPy: " << std::scientific << diff_fft << std::endl;
    if(diff_fft < 1e-9) std::cout << "РЕЗУЛЬТАТ КОРРЕКТЕН." << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;


    // 3. Проверка процедуры из п. 5 (Прямая свертка)
    std::cout << "Проверка п. 5: Прямое вычисление свертки..." << std::endl;
    std::cout << "ВНИМАНИЕ: Это ОЧЕНЬ медленная операция (O(N^2)) и может занять несколько минут!" << std::endl;
    
    auto start_direct = std::chrono::high_resolution_clock::now();
    Vector u_direct = direct_convolution(x, y);
    auto end_direct = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_direct = end_direct - start_direct;
    
    double diff_direct = calculate_difference_norm(u_direct, reference_conv);
    std::cout << "Время выполнения: " << duration_direct.count() << " мс" << std::endl;
    std::cout << "Норма разности с NumPy: " << std::scientific << diff_direct << std::endl;
    if(diff_direct < 1e-9) std::cout << "РЕЗУЛЬТАТ КОРРЕКТЕН." << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    return 0;
}