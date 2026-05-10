import os
import matplotlib.pyplot as plt
import numpy as np

def read_time_only(file_path):
    times = []
    if not os.path.exists(file_path):
        return times
    with open(file_path, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                try:
                    times.append(float(line))
                except ValueError:
                    continue
    return times

def plot_performance(filename_to_seek, title, output_name, is_delete=False):
    plt.figure(figsize=(12, 7))
    res_path = 'res'
    plots_dir = 'plots'
    
    # Создаем папку plots, если её нет
    if not os.path.exists(plots_dir):
        os.makedirs(plots_dir)
        print(f"Папка '{plots_dir}' создана.")

    found = False
    
    # Список папок в res
    folders = [f for f in os.listdir(res_path) if os.path.isdir(os.path.join(res_path, f))]
    
    for i, folder in enumerate(folders):
        # Игнорируем BST (оба варианта: рандомный и сортированный)
        if 'BST' in folder.upper():
            continue
            
        file_path = os.path.join(res_path, folder, filename_to_seek)
        y_values = read_time_only(file_path)
        
        if y_values:
            num_points = len(y_values)
            x_values = np.linspace(100000, 1000000, num_points)
            
            label = folder
            if is_delete:
                label += " (0.5 size)"
                
            plt.plot(x_values, y_values, label=label, marker='.', markersize=4, linewidth=1.5)
            found = True
    
    if found:
        plt.title(title, fontsize=14)
        plt.xlabel('Количество элементов (N)', fontsize=12)
        plt.ylabel('Время выполнения (сек)', fontsize=12)
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.legend()
        plt.ticklabel_format(style='plain', axis='x')
        
        # Сохраняем в папку plots
        full_output_path = os.path.join(plots_dir, output_name)
        plt.savefig(full_output_path, dpi=300)
        print(f"График сохранен: {full_output_path}")
    else:
        print(f"Данные для {filename_to_seek} не найдены.")
    plt.close()

if __name__ == "__main__":
    if not os.path.exists('res'):
        print("Ошибка: папка 'res' не найдена!")
    else:
        # Рисуем для добавлений
        plot_performance('add.txt', 'Сравнение скорости вставки (Add: 100k - 1M)', 'all_add_performance.png')
        
        # Рисуем для удалений
        plot_performance('delete.txt', 'Сравнение скорости удаления (Delete: N/2)', 'all_delete_performance.png', is_delete=True)