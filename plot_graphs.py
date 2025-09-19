import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

# Dados empíricos
bubble_sort_n = np.array([100, 500, 1000, 2000, 5000, 10000, 20000, 50000])
bubble_sort_time_ns = np.array([66191, 1653781, 6872720, 28655572, 181073500, 728574212, 2906868420, 18115488084])

insertion_sort_n = np.array([100, 500, 1000, 2000, 5000, 10000, 20000, 50000])
insertion_sort_time_ns = np.array([20207, 504977, 2012897, 7971401, 49872720, 201548557, 799421673, 4750069995])

sequential_search_n = np.array([100, 500, 1000, 2000, 5000, 10000, 20000, 50000])
sequential_search_time_ns = np.array([315, 1191, 1251, 4167, 3505, 11056, 41521, 76137])

binary_search_n = np.array([100, 500, 1000, 2000, 5000, 10000, 20000, 50000])
binary_search_time_ns = np.array([157, 171, 187, 213, 254, 296, 314, 357])

# Converte para ms
bubble_sort_time_ms = bubble_sort_time_ns / 1_000_000
insertion_sort_time_ms = insertion_sort_time_ns / 1_000_000
sequential_search_time_ms = sequential_search_time_ns / 1_000_000
binary_search_time_ms = binary_search_time_ns / 1_000_000

plt.figure(figsize=(14,8))

# Dados empíricos
plt.plot(bubble_sort_n, bubble_sort_time_ms, label='Bubble Sort (Empírico)', marker='o', linestyle=':', color='red')
plt.plot(insertion_sort_n, insertion_sort_time_ms, label='Insertion Sort (Empírico)', marker='x', linestyle=':', color='orange')
plt.plot(sequential_search_n, sequential_search_time_ms, label='Busca Sequencial (Empírico)', marker='s', linestyle=':', color='blue')
plt.plot(binary_search_n, binary_search_time_ms, label='Busca Binária (Empírico)', marker='d', linestyle=':', color='green')

# Curvas teóricas para n no intervalo dos dados
n_theoretical = np.linspace(100, 50000, 500)

def func_on(n, k): return k * n
def func_onlogn(n, k): return k * n * np.log(n)
def func_on2(n, k): return k * n ** 2
def func_on3(n, k): return k * n ** 3
def func_logn(n, k): return k * np.log(n)

# Ajusta as curvas teóricas (fit nos dados reais)
k_on, _    = curve_fit(func_on, sequential_search_n, sequential_search_time_ms)
k_onlogn, _ = curve_fit(func_onlogn, insertion_sort_n, insertion_sort_time_ms)
k_on2, _   = curve_fit(func_on2, bubble_sort_n, bubble_sort_time_ms)
k_on3, _   = curve_fit(func_on3, bubble_sort_n, bubble_sort_time_ms)
k_logn, _  = curve_fit(func_logn, binary_search_n, binary_search_time_ms)

# Plota curvas teóricas ajustadas
plt.plot(n_theoretical, func_on(n_theoretical, k_on[0]), label="O(n) Teórico", linestyle="--", color="gray")
plt.plot(n_theoretical, func_onlogn(n_theoretical, k_onlogn[0]), label="O(n log n) Teórico", linestyle="--", color="purple")
plt.plot(n_theoretical, func_on2(n_theoretical, k_on2[0]), label="O(n²) Teórico", linestyle="--", color="brown")
plt.plot(n_theoretical, func_on3(n_theoretical, k_on3[0]), label="O(n³) Teórico", linestyle="--", color="black")
plt.plot(n_theoretical, func_logn(n_theoretical, k_logn[0]), label="O(log n) Teórico", linestyle="--", color="cyan")

plt.title("Comparação de Desempenho de Algoritmos de Ordenação e Busca")
plt.xlabel("Tamanho da Entrada (n)")
plt.ylabel("Tempo de Execução (ms)")
plt.legend()
plt.grid(True)
plt.xscale("log")
plt.yscale("log")
plt.tight_layout()
plt.savefig("algorithms_performance_with_logn.png")
plt.close()

print("Gráfico gerado: algorithms_performance_with_logn.png")
