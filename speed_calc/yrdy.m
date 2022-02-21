clear all
clc

n=3;
S = sym('S', [n n],'real');
%S = tril(S,0) + tril(S,-1).';
Df = sym('Df', [n n],'real');

A = Df*S*Df';

for i=1:n
    for j=1:n
        simplify(A(i,j))
    end
end