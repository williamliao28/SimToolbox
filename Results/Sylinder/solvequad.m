clear;
clc;

mtx_name = 'DMatTrans_TCMAT.mtx';

Dt = mmread(mtx_name);
D = Dt.';
figure(1);
spy(D,'r');
figure(2);
spy(Dt,'r');

mtx_name = 'MobMat_TCMAT.mtx';
M = mmread(mtx_name);
figure(3);
spy(M(1:100,1:100),'r');
figure(4);
spy(M,'r');

a = Dt*M*D;
figure(5);
spy(a,'r');

n = length(a);
b = rand(n,1);
all(b>0)
options = optimoptions('quadprog','Display','iter','Algorithm','interior-point-convex');
x = quadprog(a,b,[],[],[],[],zeros(n,1),inf(n,1),[],options);
all(x>=0)