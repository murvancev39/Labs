import matplotlib.pyplot as plt
import numpy as np
import os

def process_file(filename):
    if not os.path.exists(filename):
        print(f"Файл {filename} не найден!")
        return

    with open(filename, 'r', encoding='utf-8') as f:
        content = f.read()

    blocks = content.split('### TEST: ')
    
    for block in blocks:
        lines = block.strip().split('\n')
        if not lines or not lines[0]:
            continue
            
        test_name = lines[0].strip()
        indices = []
        counts = []

        for line in lines[1:]:
            parts = line.split()
            if len(parts) == 2:
                try:
                    indices.append(int(parts[0]))
                    counts.append(int(parts[1]))
                except ValueError:
                    continue

        if indices:
            draw_plot(test_name, indices, counts)

def draw_plot(name, x, y):
    # Превращаем в массив numpy для быстрой математики
    y_array = np.array(y)
    
    # Дисперсия (Variance)
    # Если в таблице 1000 бакетов, а данных меньше, 
    # нужно учитывать нулевые бакеты для честной дисперсии
    variance = np.var(y_array) 

    plt.figure(figsize=(12, 6))
    
    plt.bar(x, y, color='blue', width=1.0)
    
    plt.xlim(0, 1000) 
    
    # Выводим дисперсию в заголовок
    plt.title(f"Test: {name}\nVariance: {variance:.2f}")
    plt.xlabel("Bucket Index")
    plt.ylabel("Count")
    plt.grid(True, alpha=0.3)

    if not os.path.exists('plots'):
        os.makedirs('plots')

    filename = f"plots/{name}.png"
    plt.savefig(filename)
    plt.close()
    print(f"Создан график: {filename} (Dispersion: {variance:.2f})")

if __name__ == "__main__":
    results_files = ["res/results_float.txt", "res/results_string.txt", "res/results_unsigned.txt"]
    for f in results_files:
        process_file(f)