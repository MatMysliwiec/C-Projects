#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
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
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    int imax=800;
    double *u,*pom;
    u = new double[imax];
    pom = new double[imax];

    double v=1;
    double h=0.01;
    double t=0;
    double dt=0.005;
    double maks;

    double x0,x;
    x0=1.0;
    double sigma=0.5;
    for(int i=0; i<imax; i++)
    {
        x=h*(double)i;
        u[i]=exp(-(x-x0)*(x-x0)/(2*sigma*sigma));
    }

    int iter=0;
    FILE *plik=fopen("result.txt","w");

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

            pom[0] = 0.5*(u[1]+u[imax-1])-v*dt/(2.0*h)*(u[1]-u[imax-1]);
            for(int i=1; i<imax-1; i++)
            {
                pom[i]=0.5*(u[i+1]+u[i-1])-v*dt/(2*h)*(u[i+1]-u[i-1]);
            }
            pom[imax-1]= 0.5*(u[0]+u[imax-2])-v*dt/(2.0*h)*(u[0]-u[imax-2]);

            for(int i=0; i<imax-1; i++)
            {
                u[i]=pom[i];
            }
            for(int i=0; i<imax-1; i++)
            {
                al_draw_line(i,600-u[i]*600,i+1,600-u[i+1]*600,al_map_rgb(255,0,0),5);
            }


            if(iter%100==0)
            {
                maks=u[0];
                for(int i = 1; i<imax; i++)
                {
                    if(u[i]>maks)
                        maks=u[i];
                }
                fprintf(plik,"%.15lf\t%.15lf\n",t,fabs(1-maks));
            }

            t = t + dt;
            iter++;
            al_flip_display();
        }
    }
    delete[] u;
    delete[] pom;
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    fclose(plik);
    return 0;
}
