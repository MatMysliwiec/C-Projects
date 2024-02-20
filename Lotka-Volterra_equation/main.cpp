#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

double omega = 1.0, a=1, b=1, c=0.4, d=0.4;
double xa(double t, double omega, double x0, double v0)
{
    return x0*cos(omega*t)+v0/omega*sin(omega*t);
}
double f(double x, double v, double t)
{
    return (a-b*v)*x;
}
double g(double x, double v, double t)
{
    return (c*x-d)*v;
}
int main()
{
    double x0=0.5,v0=0.5;
    double x=x0, v=v0;

    int n, N=100000;
    double t, dt = 0.001, error;
    double k1,k2,k3,k4;
    double l1,l2,l3,l4;
    fstream plik;
    plik.open("result.txt", ios::out);
    if(plik.good()==true)
    {
            for(n=0;n<N;n++)
            {
                k1=f(x,v,t);
                l1=g(x,v,t);
                k2=f(x+0.5*dt*k1, v+0.5*dt*l1, t+0.5*dt);
                l2=g(x+0.5*dt*k1, v+0.5*dt*l1, t+0.5*dt);
                k3=f(x+0.5*dt*k2, v+0.5*dt*l2, t+0.5*dt);
                l3=g(x+0.5*dt*k2, v+0.5*dt*l2, t+0.5*dt);
                k4=f(x+dt*k3,v+dt*l3,t+dt);
                l4=g(x+dt*k3,v+dt*l3,t+dt);
                x=x+dt/6*(k1+2*k2+2*k3+k4);
                v=v+dt/6*(l1+2*l2+2*l3+l4);
                t=t+dt;
                error = fabs(x-xa(t,omega,x0,v0));
                if(n%100==0)plik<<fixed<<setprecision(15)<<t<<"\t"<<x<<"\t"<<v<<endl;
                if(n%100==0)cout<<fixed<<setprecision(15)<<t<<"\t"<<x<<"\t"<<v<<endl;
            }
        plik.close();
    }
    return 0;
}
