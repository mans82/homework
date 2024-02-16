%% Question 5
figure;

n = 0:20;
stem(n, x(n));

figure;
y_rep = repmat(x(n), 1, 3);
stem(y_rep);

%% Functions

function out = x(n)
    out = sin(2*pi*n) .* (unitstep(n) - unitstep(n - 10));
end