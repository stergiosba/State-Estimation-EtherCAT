from timeit import default_timer as timer
import numpy as np
print('Give Size of the test and randoms:')
n = input()
n = int(n)

with open(f'matmul.c', 'w') as f:
    f.write(f'#include "matmul.h"\n\n')
    f.write('void matmul(m_elem A[][N], m_elem B[][N], m_elem C[][N])\n{\n')
    f.write('\tint i,j;\n')
    f.write('\tfor(i=0;i<N;i++)\n\t{\n\t\tfor(j=0;j<N;j++)\n\t\t{\n')
    string = f'\t\t\tC[i][j] = '
    for k in range(n):
        if k % 5 == 0 and k != 0:
            string += f'A[i][{k}]*B[{k}][j] + \n\t\t\t\t\t  '
        else:
            if k != n-1:
                string += f'A[i][{k}]*B[{k}][j] + '
            else:
                string += f'A[i][{k}]*B[{k}][j]'
    string += ';'
    f.write(string)
    f.write('\n')
    f.write('\t\t}\n')
    f.write('\t}\n')
    f.write('}\n')
