import os
import sys
import matplotlib.pyplot as plt

def generate_plots():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    res_dir = os.path.join(base_dir, 'res')
    plot_dir = os.path.join(base_dir, 'plot')

    if not os.path.exists(res_dir):
        print(f"Error: Folder '{res_dir}' does not exist.")
        sys.exit(1)

    list_folder = os.path.join(res_dir, 'list')
    arr_folder = os.path.join(res_dir, 'arr')

    if not os.path.exists(list_folder) or not os.path.exists(arr_folder):
        print("Error: Required folders 'list' or 'arr' are missing.")
        sys.exit(1)

    l_files = sorted([f for f in os.listdir(list_folder) if f.endswith('.txt')])
    a_files = sorted([f for f in os.listdir(arr_folder) if f.endswith('.txt')])

    if not l_files or not a_files:
        print("Error: One of the folders is empty.")
        sys.exit(1)

    if not os.path.exists(plot_dir):
        os.makedirs(plot_dir)

    def read_data(path):
        x, y = [], []
        with open(path, 'r') as f:
            for line in f:
                parts = line.split()
                if len(parts) == 2:
                    x.append(float(parts[0]))
                    y.append(float(parts[1]))
        return x, y

    processed = False
    for l_name, a_name in zip(l_files, a_files):
        test_label = l_name.split('_')[0]
        
        lx, ly = read_data(os.path.join(list_folder, l_name))
        ax, ay = read_data(os.path.join(arr_folder, a_name))

        if not lx or not ax:
            continue

        plt.figure(figsize=(10, 6))
        plt.plot(lx, ly, label='Linked List Stack', color='blue', linewidth=1.5)
        plt.plot(ax, ay, label='Dynamic Array Stack', color='red', linewidth=1.5)

        plt.title(f'Stack Performance Comparison: {test_label.capitalize()}')
        plt.xlabel('Number of Elements')
        plt.ylabel('Time (ms/s)')
        plt.legend()
        plt.grid(True, linestyle='--', alpha=0.7)
        
        plt.savefig(os.path.join(plot_dir, f'{test_label}_comparison.png'))
        plt.close()
        print(f"Plot saved for: {test_label}")
        processed = True

    if not processed:
        print("Error: No valid data found in files.")
        sys.exit(1)

if __name__ == "__main__":
    generate_plots()