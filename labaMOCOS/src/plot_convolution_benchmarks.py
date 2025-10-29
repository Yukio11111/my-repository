import pandas as pd
import matplotlib.pyplot as plt

def plot_benchmark(csv_file, title, x_label, output_filename):
    """Функция для чтения CSV и построения графика производительности."""
    try:
        data = pd.read_csv(csv_file)
    except FileNotFoundError:
        print(f"Ошибка: файл '{csv_file}' не найден.")
        return

    # Заменяем 0 на None для прямой свертки, чтобы не рисовать точку, где замер не производился
    data['DirectConv_ms'] = data['DirectConv_ms'].replace(0, None)

    plt.figure(figsize=(10, 6))

    # Строим графики
    plt.loglog(data.iloc[:, 0], data['FFTConv_ms'], 'o-', label='Свертка через БПФ', color='blue')
    plt.loglog(data.iloc[:, 0], data['DirectConv_ms'], 's-', label='Прямая свертка', color='red')

    # Логарифмическая шкала для Y
    plt.yscale('log')

    # Оформление
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel('Время выполнения (миллисекунды, лог. шкала)')
    plt.legend()
    plt.grid(True, which="both", linestyle='--')
    plt.xticks(data.iloc[:, 0].unique()) # Устанавливаем метки на оси X

    plt.tight_layout()
    plt.savefig(output_filename)
    print(f"График сохранен в файл '{output_filename}'")
    plt.show()

# --- Построение графиков для обоих случаев ---
# Случай 1
plot_benchmark(
    'fixed_length_benchmark.csv',
    'Производительность свертки (один сигнал M=512, второй - N)',
    'Длина второго сигнала (N_variable)',
    'convolution_fixed_length.png'
)

# Случай 2
plot_benchmark(
    'variable_length_benchmark.csv',
    'Производительность свертки (оба сигнала одинаковой длины N)',
    'Длина сигналов (N)',
    'convolution_variable_length.png'
)