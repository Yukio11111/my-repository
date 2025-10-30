#include "fft.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono> // Для измерения времени
#include <cmath>  // Для pow()
#include <random> // Для генерации случайных чисел

// Копируем сюда реализацию прямого ДПФ из предыдущего задания
Vector dft_direct(const Vector& signal) {
    int N = signal.size();
    Vector spectrum(N);
    const Complex J(0, 1);
    for (int k = 0; k < N; ++k) {
        Complex sum(0.0, 0.0);
        for (int n = 0; n < N; ++n) {
            double angle = -2 * PI * k * n / N;
            sum += signal[n] * std::exp(J * angle);
        }
        spectrum[k] = sum;
    }
    return spectrum;
}

// Функция для генерации случайного комплексного сигнала
Vector generate_random_signal(int size) {
    // Используем современный генератор случайных чисел C++
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
    // Печатаем заголовок для CSV файла
    std::cout << "N,FFT_time_ms,DFT_time_ms" << std::endl;

    // Цикл по степеням от 6 до 12
    for (int n = 6; n <= 12; ++n) {
        int N = static_cast<int>(pow(2, n));

        // Генерируем новый случайный сигнал для каждого размера
        Vector signal = generate_random_signal(N);

        // --- Измеряем время БПФ ---
        auto start_fft = std::chrono::high_resolution_clock::now();
        Vector spectrum_fft = fft(signal);
        auto end_fft = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_fft = end_fft - start_fft;

        // --- Измеряем время ДПФ ---
        std::cout << std::flush; // Сбрасываем буфер вывода, чтобы видеть прогресс
        
        auto start_dft = std::chrono::high_resolution_clock::now();
        Vector spectrum_dft = dft_direct(signal);
        auto end_dft = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_dft = end_dft - start_dft;

        // Выводим результат в формате CSV
        std::cout << N << "," << duration_fft.count() << "," << duration_dft.count() << std::endl;
    }

    return 0;
}