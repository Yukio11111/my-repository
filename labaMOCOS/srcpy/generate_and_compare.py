import numpy as np
import os

def save_complex_vector(data, filename):
    """Сохраняет комплексный вектор в бинарный файл [real, imag, real, imag, ...]."""
    data_to_write = np.zeros(2 * len(data), dtype=np.float64)
    data_to_write[0::2] = data.real
    data_to_write[1::2] = data.imag
    
    with open(filename, 'wb') as f:
        data_to_write.tofile(f)
    print(f"Saved vector to {filename}")

# --- Параметры --- 
N = 1024  # Длина сигнала 2^10
SAMPLING_RATE = 4096 # Частота дискретизации
FREQUENCY = 100 # Частота синусоиды для теста, Гц

# --- Создание директории ---
target_dir = '../other_files'

# Создаем директорию, если ее нет
if not os.path.exists(target_dir):
    os.makedirs(target_dir)

# 1. Генерируем тестовый сигнал (комплексная экспонента)
# Комплексный сигнал лучше подходит для общей проверки
t = np.linspace(0, N / SAMPLING_RATE, N, endpoint=False)
signal = np.exp(1j * 2 * np.pi * FREQUENCY * t).astype(np.complex128)

# 2. Сохраняем исходный сигнал в файл
signal_file = f'{target_dir}/signal_1024.bin'
save_complex_vector(signal, signal_file)

# 3. Вычисляем эталонный спектр с помощью NumPy
numpy_spectrum = np.fft.fft(signal)

# 4. Сохраняем эталонный спектр в файл
numpy_spectrum_file = f'{target_dir}/numpy_fft_1024.bin'
save_complex_vector(numpy_spectrum, numpy_spectrum_file)

print("\nVerification files have been generated successfully.")