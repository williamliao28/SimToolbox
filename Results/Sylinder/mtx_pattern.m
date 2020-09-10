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

b1 = 214;
b2 = 2888;
D1 = D(:,b1+1:b2-1);
D1t = D1.';
a = Dt*M*D;
figure(5);
spy(a,'r');
figure(6);
spy(D1,'r');
figure(7)
spy(D1t,'r');