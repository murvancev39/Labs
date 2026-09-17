import os
import pandas as pd
import matplotlib.pyplot as plt
import glob

SOURCE_DIR = 'time_res'
TARGET_DIR = 'plots'
FILE_EXT = '.txt'

TEST_PREFIXES = [
    'big_tests',
    'most_dub_tests',
    'small_tests'
]

def parse_filename(filename):
    clean_name = os.path.splitext(filename)[0]
    
    for prefix in TEST_PREFIXES:
        if clean_name.startswith(prefix + '_'):
            algo_name = clean_name[len(prefix)+1:]
            return prefix, algo_name
            
    parts = clean_name.split('_')
    if len(parts) > 1:
        return parts[0], '_'.join(parts[1:])
    
    return 'unknown_test', clean_name

def load_data(file_path):
    try:
        df = pd.read_csv(file_path, sep=r'\s+', names=['size', 'time'], engine='python')
        df = df.dropna()
        df['size'] = pd.to_numeric(df['size'])
        df['time'] = pd.to_numeric(df['time'])
        df = df.sort_values(by='size')
        return df
    except Exception as e:
        print(f"  [!] Ошибка чтения файла {os.path.basename(file_path)}: {e}")
        return None

def create_group_plot(part_name, test_type, algos_data):
    plt.figure(figsize=(12, 7))
    plt.style.use('seaborn-v0_8-whitegrid') 
    
    for algo_name, df in algos_data.items():
        plt.plot(df['size'], df['time'], marker='o', markersize=4, label=algo_name, linewidth=2)

    pretty_test_type = test_type.replace('_', ' ').title()
    plt.title(f'Сравнение производительности ({part_name}) - {pretty_test_type}', fontsize=14, pad=20)
    plt.xlabel('Размер массива (n)', fontsize=12)
    plt.ylabel('Время выполнения (сек)', fontsize=12)
    
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend(title="Алгоритмы", bbox_to_anchor=(1.05, 1), loc='upper left')
    
    plt.tight_layout()

    save_path = os.path.join(TARGET_DIR, part_name)
    os.makedirs(save_path, exist_ok=True)
    
    file_name = f"{test_type}_comparison.png"
    full_save_path = os.path.join(save_path, file_name)
    
    plt.savefig(full_save_path, dpi=300)
    plt.close()
    print(f"  [+] График сохранен: {full_save_path}")

def main():
    print(f"=== Запуск построения графиков из {SOURCE_DIR} ===")
    
    if not os.path.exists(SOURCE_DIR):
        print(f"Ошибка: Директория с данными '{SOURCE_DIR}' не найдена.")
        return

    part_dirs = [d for d in os.listdir(SOURCE_DIR) if os.path.isdir(os.path.join(SOURCE_DIR, d))]
    
    if not part_dirs:
        print("В папке 'time_res' не найдено подпапок с данными (part_N).")
        return

    for part in part_dirs:
        part_path = os.path.join(SOURCE_DIR, part)
        print(f"\nОбработка {part}...")
        
        grouped_data = {}
        files = glob.glob(os.path.join(part_path, f"*{FILE_EXT}"))
        
        if not files:
            print(f"  [-] В {part} нет файлов .txt")
            continue

        for file_path in files:
            filename = os.path.basename(file_path)
            test_type, algo_name = parse_filename(filename)
            df = load_data(file_path)
            
            if df is not None:
                if test_type not in grouped_data:
                    grouped_data[test_type] = {}
                grouped_data[test_type][algo_name] = df

        if not grouped_data:
            print(f"  [-] Не удалось собрать данные для графиков в {part}")
            continue

        for test_type, algos_data in grouped_data.items():
            if len(algos_data) < 1:
                print(f"  [-] Пропуск {test_type} (мало данных)")
                continue
            create_group_plot(part, test_type, algos_data)

    print("\n=== Все графики построены! ===")

if __name__ == "__main__":
    main()