#include "fft.hpp"
#include <iostream>
#include <iomanip>

// Функция для печати вектора
void print_vector(const std::string& title, const Vector& vec) {
    std::cout << title << std::endl;
    for (const auto& c : vec) {
        std::cout << std::fixed << std::setprecision(4) << c << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

int main() {

    // 2. Пример с загрузкой из файла
    std::cout << "\n--- File Loading Example ---" << std::endl;
    
    // Укажите путь к вашему бинарному файлу. 
    // Рекомендуется использовать файл с синусоидой для проверки.
    std::string filename = "performance_signals/signal_3Hz_512pts.bin"; 
    
    Vector file_signal = load_signal_from_bin(filename);
    
    std::cout << "Successfully loaded " << file_signal.size() << " samples from " << filename << std::endl;
    
    std::cout << "Performing FFT on file data..." << std::endl;
    Vector file_spectrum = fft(file_signal);
    
    std::cout << "Performing IFFT to restore signal..." << std::endl;
    Vector file_restored = ifft(file_spectrum);

    // Проверка, что сигнал восстановился (с небольшой погрешностью)
    double error = 0.0;
    for(size_t i = 0; i < file_signal.size(); ++i) {
        // Считаем сумму абсолютных разностей между исходным и восстановленным сигналом
        error += std::abs(file_signal[i] - file_restored[i]);
    }
    std::cout << "Total restoration error after IFFT: " << std::scientific << error << std::endl;


    return 0;
}