import os
__author__ = 'Jose Antonio Castro'
__github__ = 'Baelfire18'

# HINT: pip install pillow

# Checkes them using check.py file given in clasess
for i in ('Easy', 'Medium', 'Hard', 'Lunatic'):
    for j in range(1, 7):
        print(f'\nCHEQUEANDO {i} NUMERO {j}')
        os.system(f'python3 check.py {i} {j} -i')
