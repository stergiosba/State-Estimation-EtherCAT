from timeit import default_timer as timer
import numpy as np
print('Give Size of the test and randoms:')
n = input()
n = int(n)

with open(f'matmul.c', 'w') as f:
    f.write(f'#include "matmul.h"\n\n')
    f.write(f'static inline void matmul(m_elem A[][N], m_elem B[][N], m_elem C[][N])')
    f.write('\n{\n')
    for i in range(n):
        for j in range(n):
            string = f'\tC[{i}][{j}] = '
            for k in range(n):
                if k != n-1:
                    string += f'A[{i}][{k}]*B[{k}][{j}] + '
                else:
                    string += f'A[{i}][{k}]*B[{k}][{j}]'
            string += ';'
            f.write(string)
            f.write('\n')
    f.write('}\n')

with open(f'transpose.c', 'w') as f:
    f.write(f'static inline void transpose(m_elem A[][N], m_elem AT[][N])')
    f.write('\n{\n')
    for i in range(n):
        for j in range(n):
            string = f'\tAT[{i}][{j}] = A[{j}][{i}]'
            string += ';'
            f.write(string)
            f.write('\n')
    f.write('}\n')
