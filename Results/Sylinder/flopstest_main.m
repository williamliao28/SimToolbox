clear;
clc;

load testvars
xb = zeros(n,1);
options = optimoptions('quadprog','Display','iter','Algorithm','interior-point-convex');

profile on
<<<<<<< HEAD
quadprog(a,b,[],[],[],[],xb,inf(n,1),[],options);
%lsqnonneg(A1,y);
=======
%quadprog(a,b,[],[],[],[],xb,inf(n,1),[],options);
lsqnonneg1(A1,y);
>>>>>>> d4c3be0bd8bd37838fe09ba533738a402a96845d
profileStruct = profile('info');
[flopTotal,Details]  = FLOPS('quadprog','flopstestMAT',profileStruct);

fprintf("Total number of flops: %d\n",flopTotal);
Details

profile off