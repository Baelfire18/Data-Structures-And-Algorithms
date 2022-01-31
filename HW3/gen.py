import os
__author__ = 'Jose Antonio Castro'
__github__ = 'Baelfire18'

# Create directory
os.makedirs(f'output') if not os.path.exists(f'output') else None

for i in range(1, 14):
    i = f'0{i}' if i < 10 else str(i)
    print(f'Running {i}')
    # Create test cases
    os.system(f'./dewey tests/test_{i}.txt output/test_{i}.txt')
