function [L, invL] = myCHOLMATLAB(A)

n = size(A,1);
L=zeros(n);

L = chol(A,'lower');

invL = inv(L);