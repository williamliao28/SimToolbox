clear;
clc;

load testvars
xb = zeros(n,1);
options = optimoptions('quadprog','Display','iter','Algorithm','interior-point-convex');

profile on
%quadprog(a,b,[],[],[],[],xb,inf(n,1),[],options);
lsqnonneg(A1,y);
profileStruct = profile('info');
[flopTotal,Details]  = FLOPS('lsqnonneg','flopstestMAT',profileStruct);

fprintf("Total number of flops: %lf\n",flopTotal);
Details

profile off