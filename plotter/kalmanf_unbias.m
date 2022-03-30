function [states,P] = kalmanf_unbias(gyro_me,acc_me,Q,R,x0,P0,n,gyro_bias)
x = x0;
states(1,:) = x';
P = P0;
for i=2:n
    phi = states(i-1,1)*pi/180;
    theta = states(i-1,2)*pi/180;
    psi = states(i-1,3)*pi/180;
    p = (gyro_me(i,1)-gyro_bias(1))*pi/180;
    q = (gyro_me(i,2)-gyro_bias(2))*pi/180;
    r = (gyro_me(i,3)-gyro_bias(3))*pi/180;
    
    cosphi = cos(phi);
    sinphi = sin(phi);
    secth = sec(theta);
    tanth = tan(theta);

    F = [ 1, tanth*sinphi tanth*cosphi;
          0,   cosphi,         -sinphi;
          0,   sinphi*secth,   cosphi*secth ];
      
    A = q*cosphi-r*sinphi;
    B = q*sinphi-r*cosphi;
    
    Jf = [tanth*A secth*secth*B 0;
    -B 0 0;
    secth*A tanth*secth*B 0];

    ang_vel = F*(gyro_me(i,:)');
    dt = 1/819.2;
    x(1,1) = phi + dt*ang_vel(1);
    x(2,1) = theta + dt*ang_vel(2);
    x(3,1) = psi + dt*ang_vel(3);
    
    ni=-0.005 + (0.01)*rand(3,1);
    x_ = x+ni;
    
    phi = x_(1,1);
    theta = x_(2,1);
    psi = x_(3,1);
    
    cosphi = cos(phi);
    sinphi = sin(phi);
    costh = cos(theta);
    sinth = sin(theta);
    secth = sec(theta);
    tanth = tan(theta);
    
    P_ = Jf*P*Jf'+Q;
    

    
    H = [0 costh 0;
        -costh*cosphi sinth*sinphi 0;
        costh*sinphi sinth*cosphi 0];
    
    hx_ = [sinth;-costh*sinphi;-costh*cosphi];
    
    K = (P_*H')*inv((H*P_*H'+R));
    x = x_ +K*(acc_me(i,:)'-hx_);
    P =(eye(3)-K*H)*P_;
    states(i,:) = x';
end
states = states*180/pi;

end