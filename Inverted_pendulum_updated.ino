
float M=0.497,m=0.164,r=0.032;

double t,pret=0,deltaT=30000;
float vol=0;
float V=0,X=0,Xprev=0,theta_p=0,X_tem=0;
//float k_1=-7.8419,k_2=-47.4885,k_3=-140.1782,k_4=-17.7331;
float k_1=-0.0838,k_2=-45.3809,k_3=-156.9463,k_4=-26.6846;//option1withLongrod
//float k_1=-0.08371,k_2=-45.7938,k_3=-157.9566,k_4=-26.8818;//secondoption
//float k_1=-0.7685,k_2=-48.2373,k_3=-171.6100,k_4=-32.0702;
//float k_1=-75.9243,k_2=-82.5383,k_3=-238.5990,k_4=-40.4582;//simulstable
//float k_1=-62.4479,k_2=-76.1868,k_3=-224.8658,k_4=-38.1542;//simulstable2
//float k_1=-0.0838,k_2=-45.3810,k_3=-156.9455,k_4=-26.6846;//we know Q R
//float k_1=-1104.5,k_2=-524.3,k_3=-1156.4,k_4=-196.3;//overdamped
//float k_1=-2,k_2=-1.1,k_3=-1,k_4=-1.2;//underdamped not moving
//float k_1=-20.4,k_2=-7.48,k_3=-6.8,k_4=-8.16;//poles for discrete near unit circle
//float k_1=-26.0451,k_2=-58.5861,k_3=-186.3847,k_4=-31.6738;

//float k_1=-7.8303,k_2=-51.1605,k_3=-177.2316,k_4=-32.0668;
//float k_1=-103.9865,k_2=-99.8176,k_3=-279.4933,k_4=-47.5216;//new
float theta=0,theta_prev=0,omega=0,theta_tem=0;
double pi=3.1415926535;
volatile long counter1 = 0,counter2=0;
float th[5],x[5];
#define motor 6
#define in1 4
#define in2 5

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP); 
  pinMode(11, INPUT_PULLUP);
  pinMode(in1, INPUT); 
  pinMode(in2, INPUT);
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  pinMode(motor,OUTPUT);
  
}

void loop() {
 t=micros();

theta_tem=((counter1*pi)/300)-pi;
//theta=(counter1*pi)/300;
theta_p=(counter2*2*pi*1.49)/(12*174);
//Serial.println(theta_p);
X_tem=theta_p*r;
//Serial.println(t-pret);
 
 if(((t-pret)<=(deltaT+10000))&&((t-pret)>=(deltaT-10000)))
 {
  
if(pret==0)
{
  for(int i=0;i<=4;i++)
  {
    x[i]=X_tem;
    th[i]=theta_tem;
  }
}

x[4]=x[3];
x[3]=x[2];
x[2]=x[1];
x[1]=x[0];
x[0]=X_tem;
th[4]=th[3];
th[3]=th[2];
th[2]=th[1];
th[1]=th[0];
th[0]=theta_tem;
theta=(th[0]+th[1]+th[2]+th[3]+th[4])/5;
X=(x[0]+x[1]+x[2]+x[3]+x[4])/5;
  
  omega=(theta-theta_prev)/(deltaT/1000000);
  theta_prev=theta;
  //X=theta_p*r;
  V=(X-Xprev)/(deltaT/1000000);
  Xprev=X;
  //if((theta<(0.05)&&theta>(-0.05))&&((X>-0.2)&&(X<0.2)))
  if(theta<(pi/9)&&theta>(-pi/9)&&omega<2&&omega>-2)
  {
  vol=(-(k_1*X+k_2*V+k_3*theta+k_4*omega));
  }
  else
  {
    vol=0;
  }
//vol=(-(k_1*X+k_2*V+k_3*theta+k_4*omega));
  if(vol>=12)
  {
    vol=12;
  }
  else if(vol<=-12)
  {
    vol=-12;
  }
  //analogWrite(motor,((255*vol)/12));
  if(vol>=0){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(motor,((255*vol)/12));
  }
  else
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(motor,(-(255*vol)/12));
  }
  Serial.print(X);
  Serial.print(",");
  Serial.print(V);
  Serial.print(",");
  Serial.print(theta);
  Serial.print(",");
  Serial.print(omega);
  Serial.print(",");
  Serial.println(vol);
  
  pret=t;
 }

 

//theta=(counter*pi)/600;

//accel.getEvent(&event);
}

void ai0() {
  if(digitalRead(10)==LOW) {
  counter1++;
  }else{
  counter1--;
  }
  }
   
  void ai1() {
  if(digitalRead(11)==LOW) {
  counter2--;
  }else{
  counter2++;
  }
  }
