import os
import matplotlib.pyplot as plt

# Путь до папки part_1, где лежат small_tests, big_tests и т.д.
base_dir = "tests_results/part_1"

# Словарик с твоими шагами из C-кода, чтобы ось X была правильной
# Если папки тут нет, по оси X будет просто номер замера
steps = {
    "small_tests": 50,
    "big_tests": 10000,
    "test_most_dublicates": 10000
}

# Проходим по всем элементам в base_dir
for folder_name in os.listdir(base_dir):
    folder_path = os.path.join(base_dir, folder_name)

    # Работаем только с папками
    if os.path.isdir(folder_path):
        plt.figure(figsize=(10, 6)) # Создаем новый график
        has_data = False
        
        # Узнаем шаг для текущей папки, по умолчанию 1
        current_step = steps.get(folder_name, 1)

        # Читаем все файлы внутри папки (buble_sort, insertion_sort...)
        for file_name in os.listdir(folder_path):
            file_path = os.path.join(folder_path, file_name)

            if os.path.isfile(file_path):
                times = []
                with open(file_path, 'r') as f:
                    for line in f:
                        try:
                            # Читаем числа, игнорируя пустые строки
                            times.append(float(line.strip()))
                        except ValueError:
                            pass # Если попадется мусор, скипаем
                
                if times:
                    # Генерируем ось X (размер массива)
                    x_axis = [i * current_step for i in range(len(times))]
                    
                    # Рисуем линию для текущей сортировки
                    plt.plot(x_axis, times, label=file_name, marker='.', markersize=5, linewidth=2)
                    has_data = True

        # Если в папке были данные, оформляем и сохраняем график
        if has_data:
            plt.title(f"Сравнение сортировок: {folder_name}", fontsize=14, fontweight='bold')
            plt.xlabel("Количество элементов (N)", fontsize=12)
            plt.ylabel("Время выполнения (секунды)", fontsize=12)
            
            plt.legend() # Добавляем плашку с названиями сортировок
            plt.grid(True, linestyle='--', alpha=0.7) # Кайфовая сеточка

            # Сохраняем картинку прямо в part_1
            save_path = os.path.join(base_dir, f"{folder_name}_graph.png")
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
            print(f"График сохранен: {save_path} kek")

        plt.close() # Очищаем холст для следующей папки