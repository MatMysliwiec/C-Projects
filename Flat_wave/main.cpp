#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    ALLEGRO_DISPLAY *display=al_create_display(800, 600);
    bool redraw=true;
    const float FPS=60;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    int imax=800;

    double *E,*B,*Epom,*Bpom;
    E=new double[imax];
    B=new double[imax];
    Epom=new double[imax];
    Bpom=new double[imax];

    double t=0.0;
    double v=1.0;
    double h=0.01;
    double dt=0.005;
    double x,x0;
    x0=0.5*h*(double)imax;
    double sigma=0.2;
    for(int i=0; i<imax; i++)
    {
        x=h*(double)i;
        //E[i]=cos(4*M_PI*x);
        //B[i]=sin(4*M_PI*x);
        //E[i]=1.0*sin(2.0*M_PI*x);
        //B[i]=1.0*sin(2.0*M_PI*x+M_PI);
        E[i]=1.0 * exp(-(x - x0)*(x - x0) / (2 * 1.0));
        B[i]=0.0;
    }
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

            for(int i=1;i<imax;i++)
            {
                Epom[i]=0.5*(E[i+1]+E[i-1])-0.5*v*dt/h*(B[i+1]-B[i-1]);
                Bpom[i]=0.5*(B[i+1]+B[i-1])-0.5*v*dt/h*(E[i+1]-E[i-1]);
            }

            Epom[0]=0.5*(E[1]+E[imax-1])-0.5*v*dt/h*(B[1]-B[imax-1]);
            Bpom[0]=0.5*(B[1]+B[imax-1])-0.5*v*dt/h*(E[1]-E[imax-1]);

            Epom[imax-1]=0.5*(E[0]+E[imax-2])-0.5*v*dt/h*(B[0]-B[imax-2]);
            Bpom[imax-1]=0.5*(B[0]+B[imax-2])-0.5*v*dt/h*(E[0]-E[imax-2]);

            for(int i=0;i<imax;i++)
            {
                E[i]=Epom[i];
                B[i]=Bpom[i];
            }

            t=t+dt;
            for(int i=0; i<imax-1; i++)
                {
                    al_draw_line(i,300.0-E[i]*300.0,i+1,300.0-E[i+1]*300.0,al_map_rgb(0,0,255),4);
                    al_draw_line(i,300.0-B[i]*300.0,i+1,300.0-B[i+1]*300.0,al_map_rgb(255,0,0),4);
                }
            al_flip_display();
        }
    }
    delete[] E;
    delete[] Epom;
    delete[] B;
    delete[] Bpom;
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
