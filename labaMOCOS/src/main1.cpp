#include "fft.hpp" // Ваш заголовочный файл с БПФ
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric> // для std::inner_product

// --- ПУНКТ 3.2: Реализация прямого (медленного) ДПФ ---
// Прямое ДПФ по формуле (1)
Vector dft_direct(const Vector& signal) {
    int N = signal.size();
    Vector spectrum(N);
    const Complex J(0, 1);

    for (int k = 0; k < N; ++k) {
        Complex sum(0.0, 0.0);
        for (int n = 0; n < N; ++n) {
            double angle = 2 * PI * k * n / N;
            sum += signal[n] * std::exp(-J * angle);
        }
        spectrum[k] = sum;
    }
    // В задании есть множитель 1/sqrt(N), но в numpy.fft.fft его нет.
    // Чтобы сравнение было корректным, мы не будем его использовать.
    // Если он нужен, нужно раскомментировать строку ниже и добавить его в БПФ.
    // for(int i=0; i<N; ++i) spectrum[i] /= sqrt(N);
    
    return spectrum;
}


int main() {
    // --- Загрузка сигнала для проверки ---
    std::string signal_filename = "../other_files/signal_1024.bin";
    Vector signal = load_signal_from_bin(signal_filename);

    if (signal.empty()) {
        std::cerr << "Failed to load signal from " << signal_filename << ". Exiting." << std::endl;
        return 1;
    }
    std::cout << "Successfully loaded " << signal.size() << " samples from " << signal_filename << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;


    // --- Пункт 3.1: Проверка X = ОБПФ(БПФ(X)) ---
    std::cout << "Task 3.1: Verifying X = IFFT(FFT(X))" << std::endl;
    Vector spectrum_fft = fft(signal);
    Vector restored_signal = ifft(spectrum_fft);
    double restoration_error = calculate_difference_norm(signal, restored_signal);
    std::cout << "Restoration error (L2 norm): " << std::scientific << restoration_error << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;


    // --- Пункт 3.2: Сравнение ДПФ и БПФ ---
    std::cout << "Task 3.2: Comparing custom DFT and FFT results" << std::endl;
    std::cout << "Calculating direct DFT (O(N^2)). This may take a moment..." << std::endl;
    // ВНИМАНИЕ: Для N=1024 это будет работать заметно дольше, чем БПФ!
    Vector spectrum_dft = dft_direct(signal);
    double dft_fft_diff = calculate_difference_norm(spectrum_dft, spectrum_fft);
    std::cout << "Difference norm between DFT and FFT: " << std::scientific << dft_fft_diff << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;


    // --- Пункт 3.3: Сравнение с numpy.fft.fft ---
    std::cout << "Task 3.3: Comparing custom FFT with numpy.fft.fft" << std::endl;
    std::string numpy_fft_filename = "../other_files/numpy_fft_1024.bin";
    Vector numpy_spectrum = load_signal_from_bin(numpy_fft_filename);
    
    if (numpy_spectrum.empty()) {
        std::cerr << "Failed to load numpy spectrum. Exiting." << std::endl;
        return 1;
    }
    
    double numpy_fft_diff = calculate_difference_norm(spectrum_fft, numpy_spectrum);
    std::cout << "Difference norm between custom FFT and NumPy FFT: " << std::scientific << numpy_fft_diff << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    return 0;
}