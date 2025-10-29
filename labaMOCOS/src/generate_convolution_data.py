import numpy as np
import os

def save_complex_vector(data, filename):
    """Сохраняет комплексный вектор в бинарный файл [real, imag, real, imag, ...]."""
    # Преобразуем в комплексный тип, если еще не так
    data = data.astype(np.complex128)
    
    data_to_write = np.zeros(2 * len(data), dtype=np.float64)
    data_to_write[0::2] = data.real
    data_to_write[1::2] = data.imag
    
    with open(filename, 'wb') as f:
        data_to_write.tofile(f)
    print(f"Сохранен вектор в {filename}")

# --- Параметры ---
M = 50 # Длина первой последовательности
L = 30 # Длина второй последовательности

# --- Создание директории ---
if not os.path.exists('convolution_data'):
    os.makedirs('convolution_data')

# 1. Генерируем два тестовых сигнала
# Первый сигнал - прямоугольный импульс
x_sequence = np.ones(M)

# Второй сигнал - нарастающая последовательность
y_sequence = np.arange(L)

# 2. Сохраняем исходные сигналы в файлы
x_file = 'convolution_data/x_sequence.bin'
y_file = 'convolution_data/y_sequence.bin'
save_complex_vector(x_sequence, x_file)
save_complex_vector(y_sequence, y_file)

# 3. Вычисляем эталонную свертку с помощью NumPy
numpy_convolution = np.convolve(x_sequence, y_sequence)

# 4. Сохраняем эталонную свертку в файл для проверки в C++
numpy_conv_file = 'convolution_data/numpy_convolution.bin'
save_complex_vector(numpy_convolution, numpy_conv_file)

print("\nФайлы для вычисления свертки успешно сгенерированы.")