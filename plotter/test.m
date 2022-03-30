clear all
clc
syms p q r
psi = evalin(symengine, '`ψ`');
theta= evalin(symengine, '`θ`');
phi= evalin(symengine, '`ϕ`');
assume(psi,'real');
assume(theta,'real');
assume(phi,'real');
assume(p,'real');
assume(q,'real');
assume(r,'real');

Rx = Rotation(phi,'x');
Ry = Rotation(theta,'y');
Rz = Rotation(psi,'z');

%%
clc
close all
A = Rx*Ry*Rz;

X = vector3D(1,1,0);
number_of_points = 1000;
linewidth = 2;
color = 'r';

F = [1,tan(theta)*sin(phi),tan(theta)*cos(phi);
    0,cos(phi),-sin(phi);
    0,sin(phi)/cos(theta),cos(phi)/cos(theta)]

pqr = vector3D([p;q;r]);

f = F*pqr.v;

Jf = jacobian(f,[phi; theta; psi])


%F = double(subs(F,[phi,theta,psi],[0*pi/180,0*pi/180,0*pi/180]))

%Y = F*X
%X.show(number_of_points,linewidth)
%hold on
%Y.show(number_of_points,linewidth)
