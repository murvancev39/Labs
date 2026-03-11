import matplotlib.pyplot as plt
import os

def draw_separate_plots():
    filenames = [
        "first_test.txt", 
        "second_test.txt", 
        "third_test.txt", 
        "fourth_test.txt"
    ]
    
    test_names = [
        "Test 1: Mixed Push-Pop (Half-Quarter)",
        "Test 2: Large Blocks Push-Pop",
        "Test 3: Random Operations",
        "Test 4: Pure Push"
    ]

    print("\n--- Анализ производительности ---")

    for i, fname in enumerate(filenames):
        if not os.path.exists(fname):
            print(f"Пропускаю: {fname} не найден.")
            continue

        n_values = []
        times = []

        # Читаем данные
        with open(fname, 'r') as f:
            for line in f:
                parts = line.split()
                if len(parts) == 2:
                    n_values.append(int(parts[0]))
                    times.append(float(parts[1]))

        # Разделяем на массив и список (пополам)
        mid = len(n_values) // 2
        
        n_arr = n_values[:mid]
        t_arr = times[:mid]
        
        n_list = n_values[mid:]
        t_list = times[mid:]

        # --- СЧИТАЕМ РАЗНИЦУ В СКОРОСТИ ---
        # Берем вторую половину данных (самые большие n), чтобы исключить 
        # микро-погрешности и нули на старте графика
        calc_start = len(t_arr) // 2
        sum_arr = sum(t_arr[calc_start:])
        sum_list = sum(t_list[calc_start:])

        if sum_arr > 0:
            ratio = sum_list / sum_arr
            stat_text = f"Массив быстрее в ~{ratio:.1f} раз"
        else:
            stat_text = "Данные слишком малы для сравнения"
            
        # Вывод в консоль
        print(f"{test_names[i]}: {stat_text}")

        # Создаем НОВЫЙ отдельный график
        plt.figure(figsize=(10, 6))
        
        plt.plot(n_arr, t_arr, label='Array Stack', color='#1f77b4', linewidth=2)
        plt.plot(n_list, t_list, label='List Stack', color='#ff7f0e', linewidth=2)
        
        plt.title(test_names[i], fontsize=14)
        plt.xlabel('Number of elements (n)', fontsize=12)
        plt.ylabel('Time (seconds)', fontsize=12)
        plt.grid(True, linestyle=':', alpha=0.7)
        plt.legend(loc="upper right")

        # Рисуем плашку с текстом на графике (слева вверху)
        plt.annotate(
            stat_text, 
            xy=(0.02, 0.95), xycoords='axes fraction',
            fontsize=12, fontweight='bold', color='darkred',
            bbox=dict(boxstyle="round,pad=0.4", fc="#ffe6e6", ec="darkred", alpha=0.9),
            verticalalignment='top'
        )

        # Сохраняем каждый тест в свой файл
        output_name = f"plot_test_{i+1}.png"
        plt.savefig(output_name, dpi=300, bbox_inches='tight')
        
        # Закрываем текущий график
        plt.close()
        
    print("---------------------------------\nГрафики успешно сохранены!")

if __name__ == "__main__":
    draw_separate_plots()