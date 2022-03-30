clear all
clc

f=1;
testValues = linspace(-f*3.141593,f*3.141593,500)';

for i=1:size(testValues,1)
    SEC(i) = 1/cos(testValues(i));
end

for i=1:size(testValues,1)
    SEC2(i) = pade_secant(testValues(i));
end

for i=1:size(testValues,1)
    SEC3(i) = pade_secant2(testValues(i));
end


plot(testValues,SEC)
hold on
plot(testValues,SEC3)

figure
plot(testValues,SEC3-SEC)

    