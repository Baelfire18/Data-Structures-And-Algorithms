import os
__author__ = 'Jose Antonio Castro'
__github__ = 'Baelfire18'

# Create directory
os.makedirs(f'output') if not os.path.exists(f'output') else None

for j in range(1, 14):
    j = f'0{j}' if j < 10 else str(j)
    print(f'Running {j}')
    # Create test cases
    os.system(f'./dewey tests/test_{j}.txt output/test_{j}.txt')
