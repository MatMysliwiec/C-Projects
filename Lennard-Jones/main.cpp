#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
double U(double x)
{
    double x2=x*x;
    double x6=x2*x2*x2;
    return 4.0*(1.0-x6)/(x6*x6);
}
double F(double x)
{
    double x2=x*x;
    double x6=x2*x2*x2;
    return -24.0*(-2.0+x6)/(x6*x6*x);
}
double random(double a,double b)
{
    double u=(double)(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
}
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    ALLEGRO_DISPLAY *display=al_create_display(1200, 600);
    bool redraw=true;
    const float FPS=600;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    int N=100.0;
    double L=100.0;
    double rho=(double)N/L;
    double x0[N];
    double x1[N];
    double x2[N];
    int counter;
    x0[0]=0.0;
    x0[N-1]=L;
    x1[0]=0.0;
    x1[N-1]=L;
    x2[0]=0.0;
    x2[N-1]=L;
    for(int i=0; i<N; i++)
        x0[i]=L*(double)i/((double)N-1.0);
    double v[N];
    for(int i=0; i<N; i++)
        v[i]=random(-0.5,0.5);
    double dt=0.01;
    double sF[100];
    double v2[N];
    for(int i=0; i<N; i++)
    {
        sF[i]=0.0;
        for(int j=0; j<N; j++)
            if(i!=j)
                sF[i]+=F(x0[i]-x0[j]);
    }
    for(int i=1; i<N-1; i++)
    {
        v[i]=v[i]+sF[i]/1.0*dt;
        v2[i]=v[i]*v[i];
        x1[i]=x0[i]+v[i]*dt;
    }


    double v2sum,v2av;
    for(int i=0; i<N; i++)
        v2sum+=v2[i];
    std::cout<<v2sum<<std::endl;
    double T;
    T = v2sum/(2.0*N);
    printf("%.15lf\n",T);

    int histogram[100];
    for(int i=0; i<100; i++)
        histogram[i]=0;
    double histogrammax;

    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_TIMER)
        {
            redraw=true;
        }
        else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            for(int i=0; i<N; i++)
            {
                sF[i]=0.0;
                for(int j=0; j<N; j++)
                    if(i!=j)
                        sF[i]+=F(x1[i]-x1[j]);
            }
            for(int i=1; i<N-1; i++)
            {
                x2[i]=2.0*x1[i]-x0[i]+sF[i]/1.0*dt*dt;
            }
            for(int i=1; i<N-1; i++)
                x0[i]=x1[i];
            for(int i=1; i<N-1; i++)
                x1[i]=x2[i];
            for(int i=0; i<N; i++)
                al_draw_filled_circle(100+1000.0*x0[i]/L,500,500.0/L,al_map_rgb(255,255,255));
            for(int i=1; i<N-1; i++)
            {
                int bin=x0[i]/L*99.0;
                histogram[bin]++;
            }
            histogrammax=histogram[0];
            for(int i=1; i<100; i++)
            {
                if(histogram[i]>histogrammax)
                    histogrammax=histogram[i];
            }

            for(int i=0; i<99; i++)
            {
                al_draw_line(100+i*10,400-300.0*histogram[i]/histogrammax,100+i*10+10,
                             400-300.0*histogram[i+1]/histogrammax,al_map_rgb(255,0,0),2);
            }
            al_draw_line(100,100,1100,100,al_map_rgb(255,255,255),1);
            al_draw_line(100,400,1100,400,al_map_rgb(255,255,255),1);
            al_draw_line(100,100,100,400,al_map_rgb(255,255,255),1);
            al_draw_line(1100,100,1100,400,al_map_rgb(255,255,255),1);
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
