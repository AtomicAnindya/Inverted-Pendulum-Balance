%measured quantities in SI units
m=0.164;%pendulum mass
M=0.617;%cart mass %0.120
l=0.425/2; %pendulum length is 2l
I=(m*l^2)/3;%pendulum moi about com
b=0.43073;
Im=0.17315;
Kt=77.703;
Ke=0.64995;
Lm=3.8872;
Rm=136.25;
r=0.032;
g=9.8;

d=(((M+m)*r^2+Im)*I)+(M*m*(r^2)*(l^2))+(m*Im*(l^2));%this is  D in calculation, determinant of that matrix
a1=(-(I+m*(l^2))*(((Kt*Ke)/Rm)+b))/d;
a2=(-(m^2)*(l^2)*g*(r^2))/d;
a3=((((Kt*Ke)/Rm)+b)*m*l)/d;
a4=(((M+m)*r^2+Im)*m*l*g)/d;
A=[0 1 0 0; 0 a1 a2 0;0 0 0 1;0 a3 a4 0];

B=[0; ((I+m*l^2)*Kt*r)/(d*Rm); 0; (-m*l*r*Kt)/(d*Rm)];

C=[0 0 1 0];

D=0;% this is D of state-space

%% LQR ka parameters
Q=[1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1];

R=10000;

K=lqr(A,B,Q,R);



A_=A-B*K;
%% Build System
Sys= ss(A,B,C,D);

%% Discretization
Ts=0.03;
Sys_d=c2d(Sys,Ts);

Ad=Sys_d.a;
Bd=Sys_d.b;
Cd=Sys_d.c;
Dd=Sys_d.d;
N=zeros(length(Bd),1);

[K_d,~,~]=dlqr(Ad,Bd,Q,R,N);

%% initial condition
x0=[0; 0; 0.05; 0.1];
%% motor matrices
%A_m=[0 1 0;
    %0 0 1;
    %0 -41 -14];
%B_m=[0;
   % 0;
    %1];
%C_m=[10 0 0];
%I_m=0.32;
%r=0.423;
%Bnew=B*(I_m*9/r);
%NewK=lqr(A,Bnew,Q,R);
%K_m=acker(A_m,B_m,[-30 -2-j*2 -2+j*2]);
