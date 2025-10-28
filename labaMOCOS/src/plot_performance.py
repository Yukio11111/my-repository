import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 1. Читаем данные из CSV файла, сгенерированного C++ программой
try:
    data = pd.read_csv('performance_data.csv')
except FileNotFoundError:
    print("Ошибка: файл 'performance_data.csv' не найден.")
    print("Пожалуйста, сначала запустите C++ программу: ./performance_tester > performance_data.csv")
    exit()

# 2. Создаем график
plt.figure(figsize=(10, 6))

# 3. Строим графики для БПФ и ДПФ
plt.loglog(data['N'], data['FFT_time_ms'], 'o-', label='БПФ (FFT) - O(N log N)', color='blue')
plt.loglog(data['N'], data['DFT_time_ms'], 's-', label='Прямое ДПФ (DFT) - O(N²)', color='red')



# 5. Оформляем график
plt.title('Сравнение производительности БПФ и прямого ДПФ')
plt.xlabel('Длина сигнала (N)')
plt.ylabel('Время выполнения (миллисекунды, логарифмическая шкала)')
plt.legend()
plt.grid(True, which="both", linestyle='--')
plt.xticks(data['N'], rotation=45) # Отмечаем все точки N на оси X

# 6. Сохраняем график в файл и показываем его
plt.tight_layout()
plt.savefig('performance_graph.png')
plt.show()

print("График сохранен в файл 'performance_graph.png'")