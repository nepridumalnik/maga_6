import numpy as np

N = 2048
t = np.linspace(0, 1, N, endpoint=False)
signal = np.cos(2 * np.pi * 40 * t) + 1j * np.sin(2 * np.pi * 90 * t)

with open("input_2.txt", "w") as f:
    f.write(",".join(f"{z.real:.10f} {z.imag:.10f}" for z in signal))
