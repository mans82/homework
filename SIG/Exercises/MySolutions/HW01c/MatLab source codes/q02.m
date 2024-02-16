%% Question 2.1
figure;

n = 0:5;
stem(n, 2.^n);

xlim([-20, 20]);
title('Question 2.1');

%% Question 2.2
figure;

stem(-20:20, [zeros(1, 10), sin(-10:10), zeros(1, 10)]);

xlim([-20, 20]);
title('Question 2.2');

