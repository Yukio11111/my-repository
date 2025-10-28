#ifndef FFT_DIF_HPP
#define FFT_DIF_HPP

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>

// Используем псевдоним для удобства
using Complex = std::complex<double>;
using Vector = std::vector<Complex>;

// Константа PI для вычислений
const double PI = 3.14159265358979323846;

/**
 * @brief Выполняет двоично-инверсную перестановку элементов вектора.
 * Это необходимо для итеративного алгоритма БПФ, чтобы результат был в правильном порядке.
 * @param data Вектор комплексных чисел (изменяется по месту).
 */
void bit_reversal_permutation(Vector& data) {
    int n = data.size();
    if (n <= 1) return;

    // Вычисляем количество бит, необходимых для представления индексов
    int log2_n = 0;
    while ((1 << log2_n) < n) {
        log2_n++;
    }

    for (int i = 0; i < n; ++i) {
        int reversed_i = 0;
        for (int j = 0; j < log2_n; ++j) {
            if ((i >> j) & 1) {
                reversed_i |= 1 << (log2_n - 1 - j);
            }
        }
        // Меняем местами элементы, если текущий индекс меньше инвертированного,
        // чтобы избежать двойного обмена.
        if (i < reversed_i) {
            std::swap(data[i], data[reversed_i]);
        }
    }
}

/**
 * @brief Основная функция для вычисления БПФ (прямого и обратного).
 * Реализует итеративный алгоритм с прореживанием по частоте (DIF).
 * @param data Вектор комплексных чисел (изменяется по месту).
 * @param inverse Если false - прямое БПФ, если true - обратное БПФ.
 */
void fft_core(Vector& data, bool inverse) {
    int n = data.size();
    if (n <= 1) return;

    // Шаг 1: Двоично-инверсная перестановка на входе
    bit_reversal_permutation(data);

    // Шаг 2: Итеративное вычисление "бабочек"
    // Внешний цикл по стадиям (log2(N) стадий)
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (inverse ? 1.0 : -1.0);
        Complex wlen(cos(angle), sin(angle)); // Поворачивающий множитель W_len

        // Внутренний цикл по блокам
        for (int i = 0; i < n; i += len) {
            Complex w(1);
            // Цикл по "бабочкам" внутри блока
            for (int j = 0; j < len / 2; ++j) {
                Complex u = data[i + j];
                Complex v = data[i + j + len / 2] * w;
                data[i + j] = u + v;
                data[i + j + len / 2] = u - v;
                w *= wlen; // Обновляем поворачивающий множитель для следующей бабочки
            }
        }
    }

    // Шаг 3: Масштабирование для обратного БПФ
    if (inverse) {
        for (int i = 0; i < n; ++i) {
            data[i] /= n;
        }
    }
}


/**
 * @brief Прямое быстрое преобразование Фурье (обертка над fft_core).
 * @param data Вектор комплексных чисел.
 * @return Результирующий вектор после преобразования.
 */
Vector fft(const Vector& data) {
    Vector result = data;
    fft_core(result, false);
    return result;
}

/**
 * @brief Обратное быстрое преобразование Фурье (обертка над fft_core).
 * @param data Вектор комплексных чисел.
 * @return Результирующий вектор после обратного преобразования.
 */
Vector ifft(const Vector& data) {
    Vector result = data;
    fft_core(result, true);
    return result;
}

/**
 * @brief Загружает комплексный сигнал из бинарного файла.
 * Файл должен быть сгенерирован Python-скриптом, где действительные
 * и мнимые части (double) чередуются.
 * @param filename Имя файла.
 * @return Вектор комплексных чисел.
 */
Vector load_signal_from_bin(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    // Определяем размер файла
    file.seekg(0, std::ios::end);
    long long file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Количество значений double (real, imag, real, imag, ...)
    int num_doubles = file_size / sizeof(double);
    if (num_doubles % 2 != 0) {
        std::cerr << "Warning: The file contains an odd number of double values." << std::endl;
    }

    // Количество комплексных чисел
    int num_samples = num_doubles / 2;
    Vector signal(num_samples);
    
    // Читаем чередующиеся double и формируем комплексные числа
    std::vector<double> buffer(num_doubles);
    file.read(reinterpret_cast<char*>(buffer.data()), file_size);
    
    for (int i = 0; i < num_samples; ++i) {
        signal[i] = Complex(buffer[2 * i], buffer[2 * i + 1]);
    }

    file.close();
    return signal;
}

#endif // FFT_DIF_HPP