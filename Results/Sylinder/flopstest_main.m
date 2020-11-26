clear;
clc;

load testvars
%xb = zeros(n,1);
%options = optimoptions('quadprog','Display','iter','Algorithm','interior-point-convex');

profile clear
profile on
%quadprog(a,b,[],[],[],[],xb,inf(n,1),[],options);
x = lsqnonneg(A1,y);

profileStruct = profile('info');
[flopTotal,Details]  = FLOPS('lsqnonneg','testvars',profileStruct);

fprintf("Total number of flops: %d\n",flopTotal);
Details

profile off