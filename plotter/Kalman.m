clear all
close all
clc

file = "gyro_test_3.csv";
load('gyro_bias.mat')
gyro_bias = [bias_gx, bias_gy, bias_gz];
[T,AX,AY,AZ,GX,GY,GZ,n] = IMUdata(file);
gyro_me = [GX GY GZ];
acc_me = [AX AY AZ];

%%

Q = [1.9600e-04 0 0;
    0 1.9600e-04 0;
    0 0 1.9600e-04];
R = [0.1 0 0
    0 0.1 0;
    0 0 0.1];
x0 = zeros(3,1);
P0 = [100 0 0;
    0 100 0;
    0 0 100];
[states,P] = kalmanf(gyro_me,acc_me,Q,R,x0,P0,n);
[states2,P2] = kalmanf_unbias(gyro_me,acc_me,Q,R,x0,P0,n,gyro_bias);


figure
plot(T,states(:,1),"b","linewidth",2)
hold on
plot(T,states2(:,1),"r","linewidth",2)
title("X")
grid on

figure
plot(T,states(:,2),"b","linewidth",2)
hold on
plot(T,states2(:,2),"r","linewidth",2)
title("Y")
grid on

figure
plot(T,states(:,3),"b","linewidth",2)
hold on
plot(T,states2(:,3),"r","linewidth",2)
title("Z")
grid on