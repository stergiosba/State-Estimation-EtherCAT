function [T,AX,AY,AZ,GX,GY,GZ,n] = IMUdata(file)

    A = table2array(readtable(file));
    [r,~]=find(isnan(A));
    n = size(A,1);
    A = A(max(r)+1:n,:);
    n = size(A,1);
    T=linspace(1,n,n)'/100;
    
    % Accelerometer Data
    AX=A(:,2)/1000;
    AY=A(:,4)/1000;
    AZ=A(:,6)/1000+0.981;
    
    % Gyro Data
    GX=A(:,8);
    GY=A(:,10);
    GZ=A(:,12);
end