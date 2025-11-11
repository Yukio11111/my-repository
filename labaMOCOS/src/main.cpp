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
    
    std::string filename = "../other_files/signal_3Hz_512pts.bin"; 
    
    Vector file_signal = load_signal_from_bin(filename);
    
    std::cout << "Успешно загружен " << file_signal.size() << " образцы из " << filename << std::endl;
    
    Vector file_spectrum = fft(file_signal);
    
    Vector file_restored = ifft(file_spectrum);

    // Проверка, что сигнал восстановился (с небольшой погрешностью)
    double error = 0.0;
    for(size_t i = 0; i < file_signal.size(); ++i) {
        // Считаем сумму абсолютных разностей между исходным и восстановленным сигналом
        error += std::abs(file_signal[i] - file_restored[i]);
    }
    std::cout << "Полная ошибка восстановления после IFFT: " << std::scientific << error << std::endl;


    return 0;
}