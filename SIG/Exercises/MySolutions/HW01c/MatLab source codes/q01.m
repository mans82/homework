close all

%% Question 1.a
figure;

n = -20:20;
stem(n, x(n));

xlabel('n');
ylabel('x[n]');
title('Question 1.a');

%% Question 1.b
figure;

stem(n, y(n));

xlabel('n');
ylabel('y[n]');
title('Question 1.b');

%% Question 1.c
figure;

stem(n, z(n));

xlabel('n');
ylabel('z[n]');
title('Question 1.c');

%% Functions

function out = z(n)
    out = cos((2*pi).*n).*x(n);
end

function out = y(n)
    out = 2.*x(n) - x(2.*n);
end

function out = x(n)
    out = unitstep(n + 3) - unitstep(n - 3) + 2.*unitimpulse(n + 3) + 3.*unitimpulse(n + 2);
end