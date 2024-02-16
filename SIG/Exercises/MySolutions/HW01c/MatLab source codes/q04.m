close all

%% Question 4.2

figure;
n = -10:10;

subplot(3, 1, 1);
stem(n, x(n));
title('x[n]');

subplot(3, 1, 2);
stem(n, unitimpulse(n));
title('\delta[n]');

subplot(3, 1, 3);
stem(my_conv(x(n), unitimpulse(n)));
title('x[n] * \delta[n] using my\_conv()');

%% Question 4.3

figure;

subplot(2, 1, 1);

stem(my_conv(x(n), unitimpulse(n)));
title("x[n] * \delta[n] using my\_conv()");

subplot(2, 1, 2);

stem(conv(x(n), unitimpulse(n)));
title("x[n] * \delta[n] using MatLab's conv()");

%% Functions

function out = x(n)
    out = sin(3 .* n) - cos(4 .* n) + 2;
end

function out = my_conv(x1, x2)
    out = zeros(1, length(x1) + length(x2) - 1);
    for n = 1:length(out)
        for k = 1:length(x1)
            if n - k + 1 >= 1 && n - k + 1 <= length(x2)
                out(n) = out(n) + (x1(k) * x2(n - k + 1));
            end
        end
    end
end