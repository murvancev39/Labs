import matplotlib.pyplot as plt
import os

def load_data(file_path):
    x, y = [], []
    if not os.path.exists(file_path):
        return None, None
    try:
        with open(file_path, 'r') as f:
            for line in f:
                if line.startswith('#') or not line.strip():
                    continue
                parts = line.split()
                if len(parts) >= 2:
                    x.append(int(parts[0]))
                    y.append(float(parts[1]))
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
    return x, y

def create_plot(title, files, log_folder='log', save_folder='plt'):
    if not files:
        return

    plt.figure(figsize=(10, 6))
    found_any = False
    
    # Сортируем файлы, чтобы легенда была по алфавиту (bin, binom, fib)
    for file in sorted(files):
        path = os.path.join(log_folder, file)
        x, y = load_data(path)
        if x and y:
            # Красивое имя для легенды
            label = file.replace('.log', '').replace('_DENSE', '').replace('_SPARSE', '')
            plt.plot(x, y, marker='o', markersize=5, label=label)
            found_any = True
    
    if found_any:
        plt.title(title, fontsize=14)
        plt.xlabel('Number of Vertices (V)', fontsize=12)
        plt.ylabel('Time (seconds)', fontsize=12)
        plt.grid(True, linestyle='--', alpha=0.6)
        plt.legend()
        
        os.makedirs(save_folder, exist_ok=True)
        save_path = os.path.join(save_folder, f"{title.replace(' ', '_').lower()}.png")
        plt.savefig(save_path, dpi=300) # dpi=300 для четкости в отчете
        print(f"Saved: {save_path}")
        # plt.show() # Раскомментируй, если хочешь, чтобы графики всплывали при запуске
        plt.close()

# Основная логика
log_folder = 'log'
all_files = [f for f in os.listdir(log_folder) if f.endswith('.log')]

# Группировка по твоим новым именам
dense_files = [f for f in all_files if '_DENSE' in f]
sparse_files = [f for f in all_files if '_SPARSE' in f]

# Для простых тестов берем только те, где НЕТ слова dijkstra и НЕТ суффиксов
simple_files = [f for f in all_files if 'dijkstra' not in f.lower() and '_DENSE' not in f and '_SPARSE' not in f]

print("--- Generating Plots ---")
create_plot("Dijkstra Performance on Dense Graphs", dense_files)
create_plot("Dijkstra Performance on Sparse Graphs", sparse_files)
create_plot("Heap Implementation Core Tests", simple_files)

print("\nSuccess! PNG files are in the 'plt' folder.")