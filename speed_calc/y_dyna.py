from timeit import default_timer as timer
import numpy as np
print('Give Size of the test:')
n = int(input())
print('Give Size of the randoms:')
f= int(input())
x=f*np.random.rand(n,n)
y=f*np.random.rand(n,n)
z=x@y
with open('test.txt', 'w') as f:
    f.write('#include "setvalue.h"\n\n')
    f.write('void setvalues(m_elem** x, m_elem** y, m_elem**z){\n')
    for i in range(n):
        for j in range(n):
            f.write(f'x[{i}][{j}] = {x[i][j]};\n')
    f.write('\n')
    for i in range(n):
        for j in range(n):
            f.write(f'y[{i}][{j}] = {y[i][j]};\n')
    f.write('\n')
    for i in range(n):
        for j in range(n):
            f.write(f'z[{i}][{j}] = {z[i][j]};\n')
    f.write('}')
print('Done')