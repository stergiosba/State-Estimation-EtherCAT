import re
from timeit import default_timer as timer
import numpy as np
from sym import sym
print('Give Size of the test and randoms:')
n = input()
n = int(n)

offset = 0

def symmetricsymArray(size, symbol, offset=0):
    symarray = np.ndarray(shape=(size,size),dtype=sym)
    if symbol=='':
        for i in range(offset,size+offset):
            for j in range(offset,size+offset):
                symarray[i-offset][j-offset] = sym(f'') 
    else:
        k=0
        s=0
        for i in range(offset,size+offset):
            for j in range(offset,size+offset):
                if j<i:
                    s+=1
                    symarray[i-offset][j-offset] = symarray[j-offset][i-offset] 
                else:
                    symarray[i-offset][j-offset] = sym(f'{symbol}[{k-s}]')
                k+=1
    return symarray

def symArray(size, symbol, offset=0):
    symarray = np.ndarray(shape=(size,size),dtype=sym)
    if symbol=='':
        for i in range(offset,size+offset):
            for j in range(offset,size+offset):
                symarray[i-offset][j-offset] = sym(f'') 
    else:
        for i in range(offset,size+offset):
            for j in range(offset,size+offset):
                symarray[i-offset][j-offset] = sym(f'{symbol}[{i}][{j}]') 
    return symarray

def symtranspose(symlst,size=n,offset=0):
    trans = symArray(n, "", offset)
    for i in range(size):
        for j in range(size):
            trans[j][i] = symlst[i][j]
    return trans

def printsymArray(symlst,size=n):
    for i in range(size):
        for j in range(size):
            print(f'symlist[{i}][{j}] = {symlst[i][j]}')

S = symmetricsymArray(n, "A", offset)
Df = symArray(n, "B", offset)
DfT = symtranspose(Df)
A = symArray(n, "", offset)
B = symArray(n, "", offset)

printsymArray(S)

for i in range(n):
    for j in range(n):
        temp = sym(f'')
        for k in range(n):
            temp+=S[i][k]*DfT[k][j]
        A[i][j] = temp

for i in range(n):
    for j in range(n):
        temp = sym(f'')
        for k in range(n):
            temp+=Df[i][k]*A[k][j]
        B[i][j] = temp

with open(f'matmul.c', 'w') as f:
    f.write(f'#include "matmul.h"\n\n')
    f.write(f'static inline void matmul(m_elem A[M], m_elem B[][N], m_elem C[M], m_elem D[M])')
    f.write('\n{\n')
    k=0
    for i in range(n):
        for j in range(i,n):
            string = f'\tD[{k}] = C[{k}] + {B[i][j]};'
            k+=1
            f.write(string)
            f.write('\n')
    f.write('}\n')


