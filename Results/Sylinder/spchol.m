function R = spchol(A)
[m,n] = size(A);
numblocks = n/6;
for k = 1:numblocks
    R((6*k-5):(6*k),(6*k-5):(6*k)) = chol(A((6*k-5):(6*k),(6*k-5):(6*k)));
end