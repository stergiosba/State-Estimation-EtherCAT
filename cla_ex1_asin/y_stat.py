from timeit import default_timer as timer
import numpy as np
print('Give Size of the test and randoms:')
n,f = input().split()
n = int(n)
f = int(f)
x=np.round(f*np.random.rand(n,n),2)
y=np.round(f*np.random.rand(n,n),2)
z=x@y
with open('setvalue.c', 'w') as f:
    f.write('#include "setvalue.h"\n\n')
    f.write('void setvalues(m_elem x[][N], m_elem y[][N], m_elem z[][N]){\n')
    for i in range(n):
        for j in range(n):
            f.write(f'\tx[{i}][{j}] = {x[i][j]};\n')
    f.write('\n')
    for i in range(n):
        for j in range(n):
            f.write(f'\ty[{i}][{j}] = {y[i][j]};\n')
    f.write('\n')
    for i in range(n):
        for j in range(n):
            f.write(f'\tz[{i}][{j}] = {z[i][j]};\n')
    f.write('}\n')
print('Done')