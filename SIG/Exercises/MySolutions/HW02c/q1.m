%% Initialization
T = 2;
A = 1.5;
D = 1/3;

t = linspace(-T, T, 1000);

%% Part 1

m = 100;

y_func = my_square_wave(T, A, D);
y_approx = fourier_approx(t, m, y_func, T);

figure;
plot(t, real(y_approx));

hold on;
plot(t, y_func(t));

title(strcat('Fourier approximation of periodic square wave function with m= ', num2str(m)))
legend('Fourier approximation','Actual function')

%% Part 2

m = 1000;

y_func = my_sawtooth(T, A);
y_approx = fourier_approx(t, m, y_func, T);

figure;
plot(t, real(y_approx));

hold on;
plot(t, y_func(t));

title(strcat('Fourier approximation of periodic sawtooth function with m= ', num2str(m)))
legend('Fourier approximation','Actual function')


%% Functions

function out = fourier_approx(t, m, func, T)
    omega_0 = (2*pi)/T;
    
    out = zeros(size(t));

    for k = -m:m
        out = out + ((fourier_coeff_at(k, func, T) .* exp(1i*omega_0*k*t)));
    end
end

function out = fourier_coeff_at(k, func, T)
    omega_0 = (2*pi)/T;

    integrand = @(t) (func(t) .* exp(-1i*k*omega_0*t));
    out = (1/T) * integral(integrand, 0, T);
end

function out = my_square_wave(T, A, D)
    scaledDutyCycle = D * 100;
    newOmega_0 = (2*pi)/T;
    dutyCycleShift = (T*D)/2;
    out = @(t) square(newOmega_0*(t+dutyCycleShift), scaledDutyCycle) * (A/2) + (A/2);
end

function out = my_sawtooth(T, A)
    newOmega_0 = (2*pi)/T;
    shift = T/2;
    out = @(t) sawtooth(newOmega_0*(t+shift), 1) * A;
end