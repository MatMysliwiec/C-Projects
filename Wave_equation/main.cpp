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
    const float FPS=240;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    int imax=800;
    double *u,*u_adv,*u_start;
    u=new double[imax];
    u_adv=new double[imax];
    u_start=new double[imax];
    double *pr;
    pr=new double[imax];
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
        pr[i]=2.0*cos(8.0*x);
    }
    for(int i=0; i<imax; i++)
    {
        x=h*(double)i;
        u_start[i]=exp(-(x-x0)*(x-x0)/(2.0*sigma*sigma)); //t=n-1
        //u_adv[i]=exp(-(x-x0)*(x-x0)/(2.0*sigma*sigma)); //t=n
        u_adv[i]=u_start[i]+pr[i]*dt;
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
            for(int i=1; i<imax-1; i++)
                u[i]=(v*dt/h)*(v*dt/h)*(u_adv[i+1]-2*u_adv[i]+u_adv[i-1])+2*u_adv[i]-u_start[i];

            u[0]=(v*dt/h)*(v*dt/h)*(u_adv[1]-2*u_adv[0]+u_adv[imax-1])+2*u_adv[0]-u_start[0];

            u[imax-1]=(v*dt/h)*(v*dt/h)*(u_adv[0]-2*u_adv[imax-1]+u_adv[imax-2])+2*u_adv[imax-1]-u_start[imax-1];


            for(int i=0; i<imax; i++)
                u_start[i]=u_adv[i];
            for(int i=0; i<imax; i++)
                u_adv[i]=u[i];
            t=t+dt;

            for(int i=0; i<imax-1; i++)
                al_draw_line(i,600.0-u[i]*600.0,i+1,600.0-u[i+1]*600.0,
                             al_map_rgb(255*u[i],0,255-u[i]*255),4);
            al_flip_display();
        }
    }
    delete[] u;
    delete[] u_adv;
    delete[] u_start;
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
