function [T,AX,AY,AZ,GX,GY,GZ,data_n] = IMUdata(file,window)

    DATA = table2array(readtable(file));
    [r,~]=find(isnan(DATA));
    n = size(DATA,1);
    DATA = DATA(max(r)+1:n,:);
    n = size(DATA,1);
    
    if nargin<2
        data_n = n;
        T=linspace(1,n,n)'/100;
        % Accelerometer Data
        AX=DATA(:,2)/1000;
        AY=DATA(:,4)/1000;
        AZ=DATA(:,6)/1000;

        % Gyro Data
        GX=DATA(:,8);
        GY=DATA(:,10);
        GZ=DATA(:,12);
    else
        if max(size(window)) == 1
            data_n = n-window+1;
            T=linspace(window,n,n-window+1)'/100;
            
            AX=DATA(window:n,2)/1000;
            AY=DATA(window:n,4)/1000;
            AZ=DATA(window:n,6)/1000;

            % Gyro Data
            GX=DATA(window:n,8);
            GY=DATA(window:n,10);
            GZ=DATA(window:n,12);
        
        elseif max(size(window)) == 2
            data_n = window(2)-window(1)+1;
            T=linspace(window(1),window(2),data_n)'/100;
            
            AX=DATA(window(1):window(2),2)/1000;
            AY=DATA(window(1):window(2),4)/1000;
            AZ=DATA(window(1):window(2),6)/1000;

            % Gyro Data
            GX=DATA(window(1):window(2),8);
            GY=DATA(window(1):window(2),10);
            GZ=DATA(window(1):window(2),12);
        else
            disp('ERRORWindow argument can only be a 2D vector of timestamps: (data_start,data_end)')
        end
    end
    T = T - T(1);
end