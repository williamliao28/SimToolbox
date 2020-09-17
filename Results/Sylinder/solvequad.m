clear;
clc;

mtx_name = 'DMatTrans_TCMAT.mtx';

Dt = mmread(mtx_name);
D = Dt.';
%figure(1);
%spy(D,'r');
%figure(2);
%spy(Dt,'r');

mtx_name = 'MobMat_TCMAT.mtx';
M = mmread(mtx_name);
%figure(3);
%spy(M(1:100,1:100),'r');
%figure(4);
%spy(M,'r');

a = Dt*M*D;
%figure(5);
%spy(a,'r');

% get lower bounds
mtx_name = 'invKappa_TV.mtx';
invKappa = mmread(mtx_name);
mtx_name = 'lb0_TV.mtx';
lb0 = mmread(mtx_name);
mtx_name = 'lb_TV.mtx';
lb = mmread(mtx_name);
mtx_name = 'biFlag_TV.mtx';
biFlag = mmread(mtx_name);

n = length(a);
b = rand(n,1);
b1 = 214;
b2 = 2888;

if all(b>0)
    fprintf("b>0: TRUE\n");
else
    fprintf("b>0: FALSE\n");
end

xb = zeros(n,1);
xb(1:b1) = -inf;
xb(b2:end) = -inf;
options = optimoptions('quadprog','Display','iter','Algorithm','interior-point-convex');
x = quadprog(a,b,[],[],[],[],zeros(n,1),inf(n,1),[],options);
if all(x>=0)
    fprintf("x>=0: TRUE\n");
else
    fprintf("x>=0: FALSE\n");
end

% cvx toolbox
H = (a+a')/2;
cvx_begin
    cvx_solver sedumi
    variable x(n)
    minimize ( (1/2)*quad_form(x,a) + b'*x)
    x >= 0;
cvx_end

% nonnegative least square solvers
H = (a+a')/2;
[R,flag] = chol(H);