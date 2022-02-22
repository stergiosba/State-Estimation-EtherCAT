clear all
close all
clc

file = "gyro_test_3.csv";
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

%% Simple Integration Scheme for Gyro

IGX = zeros(n,1);
IGX(1) = GX(1);

IGY = zeros(n,1);
IGY(1) = GY(1);

IGZ = zeros(n,1);
IGZ(1) = GZ(1);

for i=2:n
    dt = T(i)-T(i-1);
    IGX(i) = IGX(i-1) + dt*GX(i);
    IGY(i) = IGY(i-1) + dt*GY(i);
    IGZ(i) = IGZ(i-1) + dt*GZ(i);
end

disp('Done')


%% Gyroscope Plots
figure
subplot(3,1,1)
plot(T,IGX,"r","linewidth",2)
ylabel('$\theta_x$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
title('Gyroscopes Test','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,2)
plot(T,IGY,"g","linewidth",2)
ylabel('$\theta_y$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,3)
plot(T,IGZ,"b","linewidth",2)
ylabel('$\theta_z$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on
xlabel('Time ($\mathbf{s}$)','Interpreter','latex','fontsize',14);



