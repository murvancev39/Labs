import os
import matplotlib.pyplot as plt

# Теперь указываем корневую папку, откуда начинаем поиск
base_dir = "tests_results"

# Словарик с твоими шагами из C-кода
steps = {
    "small_tests": 50,
    "big_tests": 10000,
    "test_most_dublicates": 10000
}

# os.walk рекурсивно проходит по всем папкам внутри base_dir
for root, dirs, files in os.walk(base_dir):
    
    # Отфильтровываем файлы: нам нужны только файлы с тестами.
    # Игнорируем картинки (png), скрытые файлы и системный мусор.
    data_files = [f for f in files if not f.endswith('.png') and not f.startswith('.')]

    # Если в текущей папке есть файлы с данными, значит это папка с тестами
    if data_files:
        folder_name = os.path.basename(root) # Имя папки с тестами (например, big_tests)
        parent_dir = os.path.dirname(root)   # Родительская папка (например, part_4)
        
        plt.figure(figsize=(10, 6))
        has_data = False
        
        # Узнаем шаг для текущей папки, по умолчанию 1
        current_step = steps.get(folder_name, 1)

        # Читаем все файлы с тестами внутри этой папки
        for file_name in data_files:
            file_path = os.path.join(root, file_name)
            times = []
            
            with open(file_path, 'r') as f:
                for line in f:
                    try:
                        times.append(float(line.strip()))
                    except ValueError:
                        pass # Скипаем мусор
            
            if times:
                x_axis = [i * current_step for i in range(len(times))]
                plt.plot(x_axis, times, label=file_name, marker='.', markersize=5, linewidth=2)
                has_data = True

        # Если данные успешно считались, рисуем и сохраняем
        if has_data:
            plt.title(f"Сравнение сортировок: {folder_name}", fontsize=14, fontweight='bold')
            plt.xlabel("Количество элементов (N)", fontsize=12)
            plt.ylabel("Время выполнения (секунды)", fontsize=12)
            
            plt.legend()
            plt.grid(True, linestyle='--', alpha=0.7)

            # Формируем путь для сохранения: родительская папка + имя_папки_graph.png
            save_name = f"{folder_name}_graph.png"
            save_path = os.path.join(parent_dir, save_name)
            
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
            print(f"График сохранен: {save_path} kek")

        plt.close() # Очищаем холст, чтобы графики не накладывались друг на друга