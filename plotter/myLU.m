function [L, invL] = myLU(A)

n = size(A,1);
L=zeros(n);

for j=1:n
    for i=j:n
        if i==j
            L(i,j)=sqrt(A(i,j)-sum(L(i,1:j).^2));
        else
            L(i,j)=(A(i,j)-sum(L(i,1:j).*L(j,1:j)))/L(j,j);
        end
    end
end

invL = L;

for i=1:n 
    invL(i,i) = 1 / L(i,i);
    for j=1:i-1
        sums = 0;
        for k=j:i-1
            sums = sums + (invL(i,k) * invL(k,j));
        end
        invL(i,j) = -sums / L(i,i);
    end
end
