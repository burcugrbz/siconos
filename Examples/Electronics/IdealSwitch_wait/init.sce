R1=1e-3;
R2=1e3;
h=1e-7;
sL = 200e-6;


X_k=0.0;
X_alpha=X_k;
L_alpha=[20.0/(R1+R2);
-20.0/(R1+R2);
20.0-20.0*(R1/(R1+R2));
0.0;
7.5;
0.0;
0.0;
20.0-20.0*(R1/(R1+R2));
R2-R1];

st=7.5;


