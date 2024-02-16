function out = unitstep(n)
    out = zeros(size(n));
    out(n >= 0) = 1;
end

