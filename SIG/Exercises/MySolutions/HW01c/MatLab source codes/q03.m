%% Question 3.1

n = 0:20;
figure;

stem(n, x(n));

title('Input signal x[n]');
xlabel('n');
ylabel('x[n]');

figure;

stem(n, h(n));
title('Impulse response signal h[n]');
xlabel('n');
ylabel('h[n]');

%% Question 3.3

y = conv(x(n), h(n));
stem(0:size(y,2)-1, y);

%% Functions

function out = h(n)
    out = (0.9 .^ n) .* unitstep(n);
end

function out = x(n)
    out = unitstep(n) - unitstep(n - 10);
end