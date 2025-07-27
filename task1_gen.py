import numpy as np

N = 1024
t = np.linspace(0, 1, N, endpoint=False)
signal = np.cos(2 * np.pi * 50 * t) + 1j * np.sin(2 * np.pi * 120 * t)

with open("input_1.txt", "w") as f:
    for z in signal:
        f.write(f"{z.real:.10f} {z.imag:.10f}\n")
