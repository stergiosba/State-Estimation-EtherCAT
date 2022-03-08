function [states,P] = kalmanf(z,Q,R,ni,x0,P0,n)

states = zeros(n,3);
x__ = x0;
states(1,:) = x__';
P__ = P0;
for i=1:n
    x_ = x__+ni;
    P_ = P__+Q;
    K = P_/(P_+R)
    x__ = x_ +K*(z(i,:)-x_')';
    P__ =(eye(3)-K)*P_;
    states(i,:) = x__';
end
P = P__;

end