#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>
#include <iostream>
using namespace std;
double U(double x, double y)
{
    double x2=x*x,y2=y*y;
    return x2*y2*exp(-x2-y2);
}
double Fx(double x, double y)
{
    double x2=x*x,y2=y*y;
    return -2.0*x*y2*(1.0-x2)*exp(-x2-y2);
}
double Fy(double x, double y)
{
    double x2=x*x,y2=y*y;
    return -2.0*y*x2*(1.0-y2)*exp(-x2-y2);
}
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    ALLEGRO_DISPLAY *display=al_create_display(800,800);
    bool redraw=true;
    const float FPS=1000;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0,0,0));
// m=1;
    double dt=0.01;
    double x0,y0,v0x,v0y,v0,kat0;
    double x1,x2,y1,y2,vx,vy;
    int histogram[100];
    for(int i=0; i<100; i++)
        histogram[i]=0;
    for(int i=0; i<10000; i++)
    {
        //x0=-10.0;
        //y0=0.0;
        x0=0.0;
        y0=0.0;
        double u=(double)(rand()%RAND_MAX)/(double)RAND_MAX;
        //v0=0.5;
        double v0 = 0.1 + 0.4 * ((double)(rand() % RAND_MAX) / (double)RAND_MAX);
        //kat0=0.05+0.1*u;
        //kat0=2.0 * M_PI * u;
        kat0=u*((2.0 * M_PI) / 10.0);
        v0x=v0*cos(kat0);
        v0y=v0*sin(kat0);
        vx=v0x;
        vy=v0y;
        x1=x0+v0x*dt;
        y1=y0+v0y*dt;
        double k1=255.0*(double)(rand()%RAND_MAX)/(double)RAND_MAX;
        double k2=255.0*(double)(rand()%RAND_MAX)/(double)RAND_MAX;
        do
        {
            x2=2.0*x1-x0+Fx(x1,y1)/1.0*dt*dt;
            y2=2.0*y1-y0+Fy(x1,y1)/1.0*dt*dt;
            x0=x1;
            y0=y1;
            x1=x2;
            y1=y2;
            al_draw_line(400+40.0*x1,400+40.0*y1,400+40.0*x0,400+40.0*y0,
                         al_map_rgb(255-k1,k1,k2),2.0);
        }
        while(x2*x2+y2*y2<=100.0);
        al_flip_display();
        vx=(x1-x0)/dt;
        vy=(y1-y0)/dt;
        double kat=atan2(vy,vx);
        histogram[(int)((kat+M_PI)/(2.0*M_PI)*99.0)]++;
        std::cout<<i<<std::endl;
    }
    FILE *plik=fopen("result.txt","w");
    for(int i=0; i<100; i++)
        fprintf(plik,"%d\t%d\n",i,histogram[i]);
    fclose(plik);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
