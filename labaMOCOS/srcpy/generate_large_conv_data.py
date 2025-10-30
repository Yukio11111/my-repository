import numpy as np
import os

def save_complex_vector(data, filename):
    """Сохраняет комплексный вектор в бинарный файл [real, imag, real, imag, ...]."""
    data = data.astype(np.complex128)
    data_to_write = np.zeros(2 * len(data), dtype=np.float64)
    data_to_write[0::2] = data.real
    data_to_write[1::2] = data.imag
    
    with open(filename, 'wb') as f:
        data_to_write.tofile(f)
    print(f"Сохранен вектор в {filename}")

# --- Параметры ---
M = 1024 # Длина первой последовательности (2^10)
L = 1024 # Длина второй последовательности (2^10)

# --- Создание директории ---
target_dir = '../other_files'

# Создаем директорию, если ее нет
if not os.path.exists(target_dir):
    os.makedirs(target_dir)

# 1. Генерируем два случайных сигнала
print(f"Генерация двух случайных сигналов длиной {M}...")
x_sequence = np.random.randn(M)
y_sequence = np.random.randn(L)

# 2. Сохраняем исходные сигналы в файлы
x_file = f'{target_dir}/x_1024.bin'
y_file = f'{target_dir}/y_1024.bin'
save_complex_vector(x_sequence, x_file)
save_complex_vector(y_sequence, y_file)

# 3. Вычисляем эталонную свертку с помощью NumPy
print("Вычисление эталонной свертки с помощью numpy.convolve...")
numpy_convolution = np.convolve(x_sequence, y_sequence)

# 4. Сохраняем эталонную свертку в файл для проверки в C++
numpy_conv_file = f'{target_dir}/numpy_conv_1024.bin'
save_complex_vector(numpy_convolution, numpy_conv_file)

print("\nФайлы для верификации свертки успешно сгенерированы.")
