clear all
%close all
clc

file = "gyro_test.csv";
[T,AX,AY,AZ,GX,GY,GZ,n] = IMUdata(file,22780);
bias_gx = mean(GX);
bias_gy = mean(GY);
bias_gz = mean(GZ);
save('gyro_bias','bias_gx','bias_gy','bias_gz')

gyro_measurements = [GX GY GZ];

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
hold on
plot(T,bias_gx*ones(n,1),"--k","linewidth",2)
ylabel('$\omega_x$ ($\mathbf{dps}$)','Interpreter','latex','fontsize',14);
title('Gyroscopes Test','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,2)
plot(T,GY,"g","linewidth",2)
hold on
plot(T,bias_gy*ones(n,1),"--k","linewidth",2)
ylabel('$\omega_y$ ($\mathbf{dps}$)','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,3)
plot(T,GZ,"b","linewidth",2)
hold on
plot(T,bias_gz*ones(n,1),"--k","linewidth",2)
ylabel('$\omega_z$ ($\mathbf{dps}$)','Interpreter','latex','fontsize',14);
grid on
xlabel('Time ($\mathbf{s}$)','Interpreter','latex','fontsize',14);

%% Simple Integration Scheme for Gyro
f = 1;
T = linspace(1,f*n,f*n)'/100;
IGX = zeros(f*n,1);
IGX(1) = 0;

IGY = zeros(f*n,1);
IGY(1) = 0;

IGZ = zeros(f*n,1);
IGZ(1) = 0;

for i=2:f*n
    dt = T(i)-T(i-1);
    phi = IGX(i-1)*pi/180;
    theta = IGY(i-1)*pi/180;
    pqr = (gyro_measurements(i,:)-[bias_gx bias_gy bias_gz])';
    
    F = [1,tan(theta)*sin(phi),tan(theta)*cos(phi);
        0,cos(phi),-sin(phi);
        0,sin(phi)/cos(theta),cos(phi)/cos(theta)];

    ang_vel = F*pqr;
    IGX(i) = IGX(i-1) + dt*ang_vel(1);
    IGY(i) = IGY(i-1) + dt*ang_vel(2);
    IGZ(i) = IGZ(i-1) + dt*ang_vel(3);
end
%% Least Squares Detrending
wx=(T'*T)\T'*IGX;
wy=(T'*T)\T'*IGY;
wz=(T'*T)\T'*IGZ;
save('ls_weights','wx','wy','wz')
disp('Done')


%% Gyroscope Plots
figure
subplot(3,1,1)
plot(T,IGX,"r","linewidth",2)
hold on
plot(T,IGX-wx*T,"m","linewidth",2)
ylabel('$\theta_x$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
title('Gyroscopes Test Body Rates','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,2)
plot(T,IGY,"g","linewidth",2)
hold on
plot(T,IGY-wy*T,"m","linewidth",2)
ylabel('$\theta_y$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,3)
plot(T,IGZ,"b","linewidth",2)
hold on
plot(T,IGZ-wz*T,"m","linewidth",2)
ylabel('$\theta_z$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on
xlabel('Time ($\mathbf{s}$)','Interpreter','latex','fontsize',14);





