import os

__author__ = "Jose Antonio Castro"

for j in range(1, 7):
    print(f"\nC_{j}:")
    os.system(f"time ./kevin-21 performance/test_{j}.txt out.txt")
    print(f"\nPython_{j}")
    os.system(f"time python3 ./python/main.py performance/test_{j}.txt outpy.txt")
