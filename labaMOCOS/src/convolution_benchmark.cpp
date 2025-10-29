#include "fft.hpp" // Ваш заголовочный файл со всеми функциями
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <random>
#include <fstream> // Для записи в файлы

// --- Копируем сюда реализации обеих сверток ---
Vector direct_convolution(const Vector& x, const Vector& y);
Vector fft_convolution(Vector x, Vector y);
int next_power_of_2(int n);

// Функция для генерации случайного комплексного сигнала
Vector generate_random_signal(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    Vector signal(size);
    for (int i = 0; i < size; ++i) {
        signal[i] = Complex(dis(gen), dis(gen));
    }
    return signal;
}


int main() {
    // --- СЛУЧАЙ 1: Одна последовательность фиксированной длины (512) ---
    std::cout << "Запуск бенчмарка для Случая 1 (один сигнал фиксирован = 512)..." << std::endl;
    std::ofstream file1("fixed_length_benchmark.csv");
    file1 << "N_variable,DirectConv_ms,FFTConv_ms" << std::endl;
    
    int fixed_size = 512;
    Vector signal_fixed = generate_random_signal(fixed_size);

    for (int n = 6; n <= 12; ++n) {
        int variable_size = static_cast<int>(pow(2, n));
        Vector signal_variable = generate_random_signal(variable_size);

        // Измеряем время быстрой свертки
        auto start_fft = std::chrono::high_resolution_clock::now();
        fft_convolution(signal_fixed, signal_variable);
        auto end_fft = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_fft = end_fft - start_fft;

        // Измеряем время прямой свертки (только для небольших N, чтобы не ждать вечно)
        double duration_direct_ms = 0.0;
        if (n <= 11) { // Ограничим, т.к. 512*4096 очень долго
            auto start_direct = std::chrono::high_resolution_clock::now();
            direct_convolution(signal_fixed, signal_variable);
            auto end_direct = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration_direct = end_direct - start_direct;
            duration_direct_ms = duration_direct.count();
        }
        
        file1 << variable_size << "," << duration_direct_ms << "," << duration_fft.count() << std::endl;
        std::cout << "  N=" << variable_size << " готово." << std::endl;
    }
    file1.close();
    std::cout << "Результаты сохранены в fixed_length_benchmark.csv" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;


    // --- СЛУЧАЙ 2: Длины обеих последовательностей варьируются ---
    std::cout << "Запуск бенчмарка для Случая 2 (оба сигнала одинаковой длины)..." << std::endl;
    std::ofstream file2("variable_length_benchmark.csv");
    file2 << "N,DirectConv_ms,FFTConv_ms" << std::endl;

    for (int n = 6; n <= 12; ++n) {
        int size = static_cast<int>(pow(2, n));
        Vector x = generate_random_signal(size);
        Vector y = generate_random_signal(size);

        // Измеряем время быстрой свертки
        auto start_fft = std::chrono::high_resolution_clock::now();
        fft_convolution(x, y);
        auto end_fft = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_fft = end_fft - start_fft;

        // Измеряем время прямой свертки (только для небольших N)
        double duration_direct_ms = 0.0;
        if (n <= 11) { // Ограничим, т.к. 4096*4096 очень долго
            auto start_direct = std::chrono::high_resolution_clock::now();
            direct_convolution(x, y);
            auto end_direct = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration_direct = end_direct - start_direct;
            duration_direct_ms = duration_direct.count();
        }

        file2 << size << "," << duration_direct_ms << "," << duration_fft.count() << std::endl;
        std::cout << "  N=" << size << " готово." << std::endl;
    }
    file2.close();
    std::cout << "Результаты сохранены в variable_length_benchmark.csv" << std::endl;

    return 0;
}

// --- Не забудьте вставить сюда реализации функций ---
Vector direct_convolution(const Vector& x, const Vector& y) {
    int M = x.size(); int L = y.size(); if (M == 0 || L == 0) return {};
    int result_size = M + L - 1; Vector u(result_size, {0.0, 0.0});
    for (int n = 0; n < result_size; ++n) {
        for (int k = 0; k < M; ++k) {
            if (n - k >= 0 && n - k < L) u[n] += x[k] * y[n - k];
        }
    } return u;
}
int next_power_of_2(int n) { int p = 1; while (p < n) p <<= 1; return p; }
Vector fft_convolution(Vector x, Vector y) {
    int M = x.size(); int L = y.size(); if (M == 0 || L == 0) return {};
    int result_size = M + L - 1; int fft_size = next_power_of_2(result_size);
    x.resize(fft_size, {0.0, 0.0}); y.resize(fft_size, {0.0, 0.0});
    Vector X = fft(x); Vector Y = fft(y); Vector U(fft_size);
    for (int i = 0; i < fft_size; ++i) U[i] = X[i] * Y[i];
    Vector u_padded = ifft(U); u_padded.resize(result_size);
    return u_padded;
}