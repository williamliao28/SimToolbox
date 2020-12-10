clear;
clc;

% load matrices
mtx_name = 'DMatTrans_TCMAT.mtx';

Dt = mmread(mtx_name);
D = Dt';

mtx_name = 'MobMat_TCMAT.mtx';
M = mmread(mtx_name);

a = Dt*M*D;

n = length(a);
b = -1+2.*rand(n,1);

% block-wise Cholesky
%{
R = spchol(M);
A1 = R*D;

[m1,m2] = size(A1);
y = rand(m1,1);
b = A1'*y;
%}

if all(b>0)
    fprintf("b>0: TRUE\n");
else
    fprintf("b>0: FALSE\n");
end

% qpOASES (online active set)
lb = zeros(n,1);
ub = inf(n,1);
%options = qpOASES_options('default','printLevel', 0, 'maxIter', 1e8, 'maxCpuTime', 60,'initialStatusBounds', 0);
options =  qpOASES_options( 'printLevel',2, 'maxIter', 5000);
startTime = tic;
[x,fval,exitflag,iter,lambda,auxOutput] = qpOASES(a,b,lb,[],options);
elapsedTime = toc(startTime);
fprintf('\n%6s %6s %5s %7s %15s %9s\n','nvar', 'ncon', 'eflag', 'iter', 'fval', 'time [s]');
fprintf('%6d %6d %5d %7d %15g %9g\n',size(a,2), size(a,1), exitflag, iter, fval, elapsedTime);
disp(auxOutput)

if all(x>=0)
    fprintf("x>=0: TRUE\n");
else
    fprintf("x>=0: FALSE\n");
end