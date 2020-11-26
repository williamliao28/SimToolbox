% NNQP Algorithm
% Problem: min(0.5*x'Ax+b'x) subject to x>=0
function x = nnqp(A,b)
% initialize parameters
tol = 1e-3;
blen = length(b);
err = 1;
iter = 1;

x = rand(blen,1);
D = diag(diag(A));
M = A - D;
Dinv = 1./diag(A);

zero_count = 0;

% start iteration
fprintf("iter            res\n");
while err>tol
    xprev = x;
    
    for k = 1:blen
        dum = Dinv(k)*(-M(k,:)*x-b(k));
        fprintf("dum=%f\n",dum)
        x(k) = max(dum,0);
    end
    
    ind = find(xprev>0,1);
    
    if isempty(ind)
        if zero_count == 0
            err = 1;
            zero_count = zero_count + 1;
        else
            err = 0;
        end
    else
        err = max(abs(x-xprev)/abs(xprev));
    end
    
    fprintf("%d            %e\n",iter,err);
    
    if iter > 10000
        break
    end
    
    iter = iter + 1;
end
fprintf("No convergence\n");