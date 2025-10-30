import numpy as np
import os

def generate_sin_signal_bin(filename, length, frequency, sampling_rate):
    """
    Сгенерируем реальный синусоидальный сигнал с заданной частотой и сохраним его в
    двоичный файл, где мнимая часть равна нулю.
    """
    # 1. Создаем временную шкалу
    # Длительность сигнала в секундах
    duration = length / sampling_rate
    # Массив временных отсчетов от 0 до duration
    t = np.linspace(0, duration, length, endpoint=False)

    # 2. Генерируем синусоиду (вещественная часть)
    real_part = np.sin(2 * np.pi * frequency * t).astype(np.float64)
    # Мнимая часть для вещественного сигнала равна нулю
    imag_part = np.zeros(length).astype(np.float64)

    # 3. Подготавливаем данные для записи (чередуем real и imag)
    data_to_write = np.zeros(2 * length, dtype=np.float64)
    data_to_write[0::2] = real_part
    data_to_write[1::2] = imag_part

    # 4. Записываем в бинарный файл
    with open(filename, 'wb') as f:
        data_to_write.tofile(f)

    print(f"Generated sine signal ({frequency} Hz) in {filename} with {length} elements")

# --- Параметры сигнала ---
FIXED_SIZE = 512       # Количество отсчетов
SAMPLING_RATE = 128    # Частота дискретизации, Гц 
FREQUENCY = 3          # Частота нашей синусоиды, Гц

# --- Создание файла ---
# Создаем директорию, если ее нет
target_dir = '../other_files'

# Создаем директорию, если ее нет
if not os.path.exists(target_dir):
    os.makedirs(target_dir)

# Имя файла с правильным путем
fixed_file = f'{target_dir}/signal_{FREQUENCY}Hz_{FIXED_SIZE}pts.bin'

# Генерируем и сохраняем сигнал
generate_sin_signal_bin(fixed_file, FIXED_SIZE, FREQUENCY, SAMPLING_RATE)

print(f"\nSignal generation complete. Use the file '{fixed_file}' in your C++ application.")