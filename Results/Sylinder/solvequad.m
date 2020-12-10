clear;
clc;

% load matrices
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

n = length(a);
b = -1+2*rand(n,1);

% block-wise Cholesky
%{
R = spchol(M);
A1 = R*D;


[m1,m2] = size(A1);
y = rand(m1,1);
b = A1'*y;
%}

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

% test coordinate descent
%x = nnqp(a,b);

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
