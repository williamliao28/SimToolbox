clear;
clc;

mtx_name = 'DMatTrans_TCMAT.mtx';

Dt = mmread(mtx_name);
D = Dt';

mtx_name = 'MobMat_TCMAT.mtx';
M = mmread(mtx_name);

a = Dt*M*D;

R = spchol(M);
A1 = R*D;

n = length(a);
[m1,m2] = size(A1);
y = rand(m1,1);
b = A1'*y;

save("testvars");