%% Question 6

t = linspace(-10*pi, 10*pi);

phase_x = angle(x(t));
abs_x = abs(x(t));


subplot(2, 2, 1);
plot(t, phase_x);
title('Phase of x(t)');

subplot(2, 2, 3);
plot(t, abs_x);
title('|x(t)|');

subplot(2, 2, 2);
plot(t, real(x(t)))
title('Re\{x(t)\}');

subplot(2, 2, 4);
plot(t, imag(x(t)))
title('Im\{x(t)\}');

%% Functions

function out = x(t)
    out = exp(3j.*t) + exp(5j.*t);
end