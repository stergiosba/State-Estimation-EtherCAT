clear all
%close all
clc

file = "gyro_test_3.csv";
[T,AX,AY,AZ,GX,GY,GZ,n] = IMUdata(file);
gyro_measurements = [GX GY GZ];

IGX = zeros(n,1);
IGX(1) = 0;

IGY = zeros(n,1);
IGY(1) = 0;

IGZ = zeros(n,1);
IGZ(1) = 0;

for t=2:n
    pqr = gyro_measurements(t,:)';
    psi = IGX(t-1)*pi/180;
    theta = IGY(t-1)*pi/180;

    F = [1,tan(theta)*sin(psi),tan(theta)*cos(psi);
    0,cos(psi),-sin(psi);
    0,sin(psi)/cos(theta),cos(psi)/cos(theta)];
    
    ang_vel = F*pqr;
    
    dt = T(t)-T(t-1);
    IGX(t) = IGX(t-1) + dt*ang_vel(1);
    IGY(t) = IGY(t-1) + dt*ang_vel(2);
    IGZ(t) = IGZ(t-1) + dt*ang_vel(3);
end

%% Gyroscope Plots
figure
subplot(3,1,1)
plot(T,IGX,"r","linewidth",2)
ylabel('$\mathbf{\psi}\ (\mathbf{deg}$)','Interpreter','latex','fontsize',14);
title('Gyroscopes Test Euler Angles','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,2)
plot(T,IGY,"g","linewidth",2)
ylabel('$\mathbf{\theta}\ (\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,3)
plot(T,IGZ,"b","linewidth",2)
ylabel('$\mathbf{\phi}\ (\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on
xlabel('Time ($\mathbf{s}$)','Interpreter','latex','fontsize',14);
