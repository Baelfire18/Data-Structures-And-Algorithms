import os

__author__ = "Jose Antonio Castro"
__github__ = "Baelfire18"

for i in range(0, 4):
    os.chdir(f"HW{i}")
    os.system("sudo make && python3 gen.py && python3 compare.py")
    os.chdir("..")
