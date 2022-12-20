import os

__author__ = "Jose Antonio Castro"
__github__ = "Baelfire18"

for j in range(1, 14):
    j = f"0{j}" if j < 10 else str(j)
    print(f"Comparing {j}")
    # Check testcases
    with open(f"solutions/test_{j}.txt") as file_1:
        with open(f"output/test_{j}.txt") as file_2:
            print(f"{j} is not correct\n") if not file_1.readlines()[
                0
            ].strip() == file_2.readlines()[0].strip() else None
