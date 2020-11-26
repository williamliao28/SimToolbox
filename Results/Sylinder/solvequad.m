clear;
clc;

mtx_name = 'DMatTrans_TCMAT.mtx';

Dt = mmread(mtx_name);
D = Dt';

mtx_name = 'MobMat_TCMAT.mtx';
M = mmread(mtx_name);

a = Dt*M*D;

%{
mtx_name = 'invKappa_TV.mtx';
invKappa = mmread(mtx_name);
mtx_name = 'lb0_TV.mtx';
lb0 = mmread(mtx_name);
mtx_name = 'lb_TV.mtx';
lb = mmread(mtx_name);
mtx_name = 'biFlag_TV.mtx';
biFlag = mmread(mtx_name);
%}

% block-wise Cholesky
R = spchol(M);
A1 = R*D;

n = length(a);
[m1,m2] = size(A1);
y = rand(m1,1);
b = A1'*y;

%{
b1 = 214;
b2 = 2888;
%}

if all(b>0)
    fprintf("b>0: TRUE\n");
else
    fprintf("b>0: FALSE\n");
end 

xb = zeros(n,1);

%{
xb(1:b1) = -inf;
xb(b2:end) = -inf;
%}

options = optimoptions('quadprog','Display','iter','Algorithm','interior-point-convex');
[x,fval,exitflag,output] = quadprog(a,b,[],[],[],[],xb,inf(n,1),[],options);
if all(x>=0)
    fprintf("x>=0: TRUE\n");
else
    fprintf("x>=0: FALSE\n");
end
disp(output)

% nonnegative least square 
[x1,resnorm,residual,exitflag1,output1,lambda] = lsqnonneg(A1,y);
%fprintf("||x-x1|| = %f\n",norm(x-x1));
fprintf("resnorm = %f\n",resnorm);
if exitflag1 == 1
    fprintf("lsqnonneg converged with a solution X\n");
else
    fprintf("Iteration count was exceeded. Increasing the tolerance (OPTIONS.TolX) may lead to a solution\n");
end
disp(output1)

% test coordinate descent
x = nnqp(a,b);


if all(x1>=0)
    fprintf("x1>=0: TRUE\n");
else
    fprintf("x1>=0: FALSE\n");
end


% cvx toolbox
%{
H = (a+a')/2;
cvx_begin
    cvx_solver sedumi
    variable w(n)
    minimize( norm(y-A1*w))
    w >= 0;
cvx_end
%}