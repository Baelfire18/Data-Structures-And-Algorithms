import os

__author__ = "Jose Antonio Castro"

for i in ("Easy", "Medium", "Hard"):
    for j in range(1, 7):
        print(f"Comparing {i} {j}")
        os.system(
            f"diff --strip-trailing-cr solutions/{i}/test_{j}.txt output/{i}/test_{j}.txt"
        )
