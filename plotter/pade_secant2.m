function EKE=pade_secant2(r,q,phi,th)

    cosphi = cos(phi);
    sinphi = sin(phi);
    A = q*cosphi-r*sinphi;
    B = q*sinphi-r*cosphi;
    secth = 1/cos(th);
    tanth = sin(th)*secth;

    EKE(1) = tanth*A;
    EKE(2) = secth*secth*B;
    EKE(3) = 0;
    EKE(4) = -B;
    EKE(5) = 0;
    EKE(6) = 0;
    EKE(7) = secth*A;
    EKE(8) = tanth*secth*B;
    EKE(9) = 0;
end