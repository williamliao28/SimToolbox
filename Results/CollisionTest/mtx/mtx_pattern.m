clear;
clc;
mtx_size = 1500;
mtx_name = ['Amat_TCMAT' num2str(mtx_size) '.mtx'];

a = mmread(mtx_name);
spy(a,);