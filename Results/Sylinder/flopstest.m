load testvars

xb = zeros(n,1);
x = zeros(n,1);

options = optimoptions('quadprog','Display','iter','Algorithm','interior-point-convex');
[x,fval,exitflag,output] = quadprog(a,b,[],[],[],[],xb,inf(n,1),[],options);

save("flopstestMAT",'-append');