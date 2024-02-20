#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <time.h>

using namespace std;

int main()
{
    int x,y;
    //int a=3432, b=25887, M=9973;
    int a=16333, b=25887, M=32768;
    int x0 = 666, y0 = 1;
    x=x0, y=y0;
    int imax=1000;

    double u, p;
    u=(double)x/(double)M;

    srand(time(NULL));
    double u1, u2;

    double a1=0, b1=0;
    fstream plik;
    plik.open("result.txt",ios::out);

    for(int i=0; i<imax; i++)
    {
        //Pseudonumber generator Oakenfull method
        x=(a*x+b)%M;
        y=x;
        x=(a*x+b)%M;
        u=(double)x/(double)M;
        p=(double)y/(double)M;
        plik<<fixed<<setprecision(8)<<i<<"\t"<<u<<"\t"<<p<<endl;
        cout<<fixed<<setprecision(8)<<i<<"\t"<<u<<"\t"<<p<<endl;

        //Pseudonumber generator using rand command
        /*x=rand()%RAND_MAX;
        y=rand()%RAND_MAX;
        u1=(double)x/(double)RAND_MAX;
        u2=(double)y/(double)RAND_MAX;
        plik<<fixed<<setprecision(8)<<i<<"\t"<<u1<<"\t"<<u2<<endl;
        cout<<fixed<<setprecision(8)<<i<<"\t"<<u1<<"\t"<<u2<<endl;*/

        //Pseudonumber generator with a two-dimensional normal distribution
        /*x=rand()%RAND_MAX;
        y=rand()%RAND_MAX;
        u1=(double)x/(double)RAND_MAX;
        u2=(double)y/(double)RAND_MAX;
        a1 = sqrt(-2*log(u1))*cos(2*M_PI*u2);
        b1 = sqrt(-2*log(u1))*sin(2*M_PI*u2);
        // a1 = tan(M_PI*(u1-0.5))*cos(2*M_PI*u2);
        // b1 = tan(M_PI*(u1-0.5))*sin(2*M_PI*u2);
        plik<<fixed<<setprecision(15)<<a<<"\t"<<b<<endl;
        cout<<fixed<<setprecision(15)<<a<<"\t"<<b<<endl*/
    }


plik.close();
return 0;
}
