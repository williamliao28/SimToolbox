clear;
clc;

% read and construct matrices
mtx_name = 'DMatTrans_TCMAT.mtx';

Dt = mmread(mtx_name);
D = Dt';

mtx_name = 'MobMat_TCMAT.mtx';
M = mmread(mtx_name);

a = Dt*M*D;

% block-wise Cholesky
R = spchol(M);
A1 = R*D;

% generate random vectors
n = length(a);
[m1,m2] = size(A1);
y = rand(m1,1);
b = A1'*y;

% nonnegative least square 
[x1,resnorm,residual,exitflag,output,lambda] = lsqnonneg(A1,y);
if exitflag == 1
    fprintf("lsqnonneg converged with a solution X\n\n");
else
    fprintf("Iteration count was exceeded. Increasing the tolerance (OPTIONS.TolX) may lead to a solution\n\n");
end
disp(output)