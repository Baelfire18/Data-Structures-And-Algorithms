import os
__author__ = 'Jose Antonio Castro'
__github__ = 'Baelfire18'

# Create directory
os.makedirs(f'output') if not os.path.exists(f'output') else None

# Create test cases
for i in ('Easy', 'Medium', 'Hard'):
    # Create subdirectories
    os.makedirs(f'output/{i}') if not os.path.exists(f'output/{i}') else None
    for j in range(1, 7):
        print(f'Running {i} {j}')
        os.system(f'./kevin-21 tests/{i}/test_{j}.txt output/{i}/test_{j}.txt')
