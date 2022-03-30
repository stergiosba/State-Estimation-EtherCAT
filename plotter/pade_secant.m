function y=pade_secant(x)
    pi_fd = 3.141592653589793;
    x = x-floor(x/(2*pi_fd))*2*pi_fd;
    if (x>pi_fd)
        x = x-2*pi_fd;
    end
    x2 = x*x;
    x4 = x2*x2;
    A = 15120+660*x2+13*x4;
    B = 15120-6900*x2+313*x4;
    y = B/A;
end