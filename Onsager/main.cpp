#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

double random(double a,double b)
{
    double u = (double)(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
}
int main()
{
    int N=360;
    double f[N],fpom[N];
    double dtheta=2.0*M_PI/(double)N;
    double rho;
    FILE *plik=fopen("result.txt","w");
    for(rho=0.1;rho<=10.0;rho+=0.1)
    {
        for(int i=0;i<N;i++)
            f[i]=random(0.0,1.0);
        double fsuma=.0;
        for(int i=0;i<N;i++)
            fsuma+=f[i]*dtheta;
        for(int i=0;i<N;i++)
            f[i]/=fsuma;
        int itermax=1000;
        for(int iter=0;iter<itermax;iter++)
        {
            for(int i=0;i<N;i++)
            {
                double suma=0.0;
                double thetai=(double)i/(double)N*2.0*M_PI;
                for(int j=0;j<N;j++)
                {
                    double thetaj=(double)j/(double)N*2.0*M_PI;
                    suma += fabs(sin(thetai-thetaj))*f[j]*dtheta;
                }

                fpom[i]=exp(-rho*suma);
            }
            fsuma=0.0;
            for(int i=0;i<N;i++)
                fsuma+=fpom[i]*dtheta;
            for(int i=0;i<N;i++)
                fpom[i]/=fsuma;
            for(int i=0;i<N;i++)
                f[i]=fpom[i];
        }
        int indexmax=0;
        double maks=0.0;
        for(int i=0;i<N;i++)
        {
            if(f[i]>maks)
            {
                maks=f[i];
                indexmax = i;
            }
        }
        double S=0.0;
        for(int i=0;i<N;i++)
            S+=cos(2.0*(double)(i-indexmax)/(double)N*2.0*M_PI)*f[i]*dtheta;
        fprintf(plik,"%.2lf\t%.2lf\n",rho,S);
    }
    fclose(plik);
    return 0;
}
