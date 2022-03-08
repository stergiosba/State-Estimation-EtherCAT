clear all
%close all
clc

file = "gyro_test_3.csv";
[T,AX,AY,AZ,GX,GY,GZ,n] = IMUdata(file);
load('gyro_bias')

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
IIGX = zeros(f*n,1);
IIGX(1) = 0;

IGY = zeros(f*n,1);
IGY(1) = 0;
IIGY = zeros(f*n,1);
IIGY(1) = 0;

IGZ = zeros(f*n,1);
IGZ(1) = 0;
IIGZ = zeros(f*n,1);
IIGZ(1) = 0;

load('ls_weights')
window_size = 39;
k=1;
wx3(1)=wx;
m_wx(1) = wx;
ema_wx(1) = wx;
wy3(1)=wy;
m_wy(1) = wy;
ema_wy(1) = wy;
wz3(1)=wz;
m_wz(1) = wz;
ema_wz(1) = wz;
for i=2:f*n
    dt = T(i)-T(i-1);
    phi = IGX(i-1)*pi/180;
    theta = IGY(i-1)*pi/180;
    pqr = (gyro_measurements(i,:)-[bias_gx bias_gy bias_gz])';
    
    F = [1,tan(theta)*sin(phi),tan(theta)*cos(phi);
        0,cos(phi),-sin(phi);
        0,sin(phi)/cos(theta),cos(phi)/cos(theta)];
    ang_vel = F*pqr;
    IGX(i) = IGX(i-1) + dt*ang_vel(1)-ema_wx(k)*dt;
    IGY(i) = IGY(i-1) + dt*ang_vel(2)-ema_wy(k)*dt;
    IGZ(i) = IGZ(i-1) + dt*ang_vel(3)-ema_wz(k)*dt;
    if mod(i,window_size)==0
        k=k+1;
        t = T(i-window_size+1:i);
        wx3(k)=(t'*t)\t'*IGX(i-window_size+1:i);
        m_wx(k) = mean(wx3);
        a = 0.1
        ema_wx(k)= a*wx3(k)+(1-a)*ema_wx(k-1);
        wy3(k)=(t'*t)\t'*IGY(i-window_size+1:i);
        m_wy(k) = mean(wy3);
        ema_wy(k)= a*wy3(k)+(1-a)*ema_wy(k-1);
        wz3(k)=(t'*t)\t'*IGZ(i-window_size+1:i);
        m_wz(k) = mean(wz3);
        ema_wz(k)= a*wz3(k)+(1-a)*ema_wz(k-1);
    end
end

for i=2:f*n
    dt = T(i)-T(i-1);
    phi = IIGX(i-1)*pi/180;
    theta = IIGY(i-1)*pi/180;
    pqr = (gyro_measurements(i,:)-[bias_gx bias_gy bias_gz])';
    
    F = [1,tan(theta)*sin(phi),tan(theta)*cos(phi);
        0,cos(phi),-sin(phi);
        0,sin(phi)/cos(theta),cos(phi)/cos(theta)];

    ang_vel = F*pqr;
    IIGX(i) = IIGX(i-1) + dt*ang_vel(1);
    IIGY(i) = IIGY(i-1) + dt*ang_vel(2);
    IIGZ(i) = IIGZ(i-1) + dt*ang_vel(3);    
end
%% Least Squares Detrending

wx_optimal=(T'*T)\T'*IIGX;
wy_optimal=(T'*T)\T'*IIGY;
wz_optimal=(T'*T)\T'*IIGZ;

disp('Done')

%% Gyroscope Plots
figure
subplot(3,1,1)
plot(T,IGX,"r","linewidth",2)
hold on
plot(T,IIGX,"m","linewidth",2)
plot(T,IIGX-wx_optimal*T,"k","linewidth",2)
ylabel('$\theta_x$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
title('Gyroscopes Test Body Rates','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,2)
plot(T,IGY,"g","linewidth",2)
hold on
plot(T,IIGY,"m","linewidth",2)
plot(T,IIGY-wy_optimal*T,"k","linewidth",2)
ylabel('$\theta_y$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on

subplot(3,1,3)
plot(T,IGZ,"b","linewidth",2)
hold on
plot(T,IIGZ,"m","linewidth",2)
plot(T,IIGZ-wz_optimal*T,"k","linewidth",2)
ylabel('$\theta_z$ ($\mathbf{deg}$)','Interpreter','latex','fontsize',14);
grid on
xlabel('Time ($\mathbf{s}$)','Interpreter','latex','fontsize',14);

%%
close all
figure
plot([1:1:k],wx3,"linewidth",2)
hold on
plot([1:1:k],m_wx',"linewidth",2)
plot([1:1:k],ema_wx',"linewidth",2)
plot([1:1:k],wx_optimal*ones(k,1),"linewidth",2)
grid on
title('X','Interpreter','latex','fontsize',14);

figure
plot([1:1:k],wy3,"linewidth",2)
hold on
plot([1:1:k],m_wy',"linewidth",2)
plot([1:1:k],ema_wy',"linewidth",2)
plot([1:1:k],wy_optimal*ones(k,1),"linewidth",2)
grid on
title('Y','Interpreter','latex','fontsize',14);

figure
plot([1:1:k],wz3,"linewidth",2)
hold on
plot([1:1:k],m_wz',"linewidth",2)
plot([1:1:k],ema_wz',"linewidth",2)
plot([1:1:k],wz_optimal*ones(k,1),"linewidth",2)
grid on
title('Z','Interpreter','latex','fontsize',14);
