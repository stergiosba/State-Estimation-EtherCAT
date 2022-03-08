clear all
close all
clc

file = "gyro_test_3.csv";
[T,AX,AY,AZ,GX,GY,GZ,n] = IMUdata(file);
z = [GX GY GZ];

%%

Q = [100 50 25;
    50 100 50;
    25 50 100];
R = [10 5 5;
    5 10 5;
    5 5 10];
ni = 5*ones(3,1);
x0 = zeros(3,1);
P0 = [10000 5000 5000;
    5000 10000 5000;
    5000 5000 10000];
[states,P] = kalmanf(z,Q,R,ni,x0,P0,n);

figure
plot(T,z(:,1),"r","linewidth",2)
hold on
plot(T,states(:,1),"b","linewidth",2)
title("X")
grid on

figure
plot(T,z(:,2),"r","linewidth",2)
hold on
plot(T,states(:,2),"b","linewidth",2)
title("Y")
grid on

figure
plot(T,z(:,3),"r","linewidth",2)
hold on
plot(T,states(:,3),"b","linewidth",2)
title("Z")
grid on