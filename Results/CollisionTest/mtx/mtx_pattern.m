clear;
clc;
mtx_size = 500;
mtx_name = ['Amat_TCMAT' num2str(mtx_size) '.mtx'];

a = mmread(mtx_name);
figure(1);
%spy(a);
%figure(2);
imagesc(a);
colorbar;

b = load("bmat");
figure(2);
imagesc(b);
colorbar;

d = load("Dmat");
figure(3);
imagesc(d);
colorbar;