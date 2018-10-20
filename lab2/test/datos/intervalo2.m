x=[];
x=load('intervalosf1.txt');
y1=[];
y=load('MinCuadradosF1_10.txt');
y2=load('splineF1_10.txt');
y3=load('divididasF1_10.txt');
y4=load('dFinitasF1_10.txt');
hold on

plot(x,y,'--');
plot(x,y2);
plot(x,y3);
plot(x,y4,'--');
