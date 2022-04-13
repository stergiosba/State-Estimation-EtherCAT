clear all
close all
clc

file = "test_1.csv";
[T,AX,AY,AZ,GX,GY,GZ,n] = IMUdata(file);
%% Acceleration Plots
figure
subplot(3,1,1)
plot(T,AX,"r","linewidth",2)
ylabel('$X_{acc}$ ($\mathbf{g}$)','Interpreter','latex','fontsize',14);
title('Z-Axis Acceleration Test','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,2)
plot(T,AY,"g","linewidth",2)
ylabel('$Y_{acc}$ ($\mathbf{g}$)','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,3)
plot(T,AZ,"b","linewidth",2)
ylabel('$Z_{acc}$ ($\mathbf{g}$)','Interpreter','latex','fontsize',14);
grid on
xlabel('Time ($\mathbf{s}$)','Interpreter','latex','fontsize',14);


%% Gyroscope Rate Plots
figure
subplot(3,1,1)
plot(T,GX,"r","linewidth",2)
ylabel('$\omega_x$ ($\mathbf{dps}$)','Interpreter','latex','fontsize',14);
title('Gyroscopes Test','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,2)
plot(T,GY,"g","linewidth",2)
ylabel('$\omega_y$ ($\mathbf{dps}$)','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,3)
plot(T,GZ,"b","linewidth",2)
ylabel('$\omega_z$ ($\mathbf{dps}$)','Interpreter','latex','fontsize',14);
grid on
xlabel('Time ($\mathbf{s}$)','Interpreter','latex','fontsize',14);