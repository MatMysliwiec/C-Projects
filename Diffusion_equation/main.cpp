#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display=al_create_display(800, 600);

    bool redraw=true;
    const float FPS=600;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    double D=1;
    double h=0.1;
    double dt=0.001;
    double t=0;
    int imax=80;
    int jmax=80;

    double **u=new double *[imax];
    for(int i = 0; i<imax; i++)
    {
        u[i]=new double[jmax];
    }

    double **pom=new double *[imax];
    for(int i = 0; i<imax; i++)
    {
        pom[i]=new double[jmax];
    }

    for(int i = 0; i<imax; i++)
    {
        for(int j=0; j<jmax; j++)
        {
            u[i][j]=0;
        }
    }
    u[(int)(imax/2)][(int)(jmax/2)]=1/(h*h);
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

            //u[10][78]=1+cos(8*t);
            //u[65][47]=2+sin(8*t);
            //u[43][12]=3+sin(5*t);

            t = t + dt;

            for(int i = 1; i<imax-1; i++)
            {
                for(int j=1; j<jmax-1; j++)
                {
                    pom[i][j]=u[i][j]+D*dt/(h*h)*(u[i+1][j]-2*u[i][j]+u[i-1][j]+u[i][j+1]-2*u[i][j]+u[i][j-1]);
                }
            }
            //bourdary conditions
            for(int j=1; j<jmax-1; j++)
            {
                pom[0][j]=u[0][j]+D*dt/(h*h)*(u[1][j]-2*u[0][j]+u[imax-1][j]+u[0][j+1]-2*u[0][j]+u[0][j-1]);
            }
            for(int j=1; j<jmax-1; j++)
            {
                pom[imax-1][j]=u[imax-1][j]+D*dt/(h*h)*(u[0][j]-2*u[imax-1][j]+u[imax-2][j]+u[imax-1][j+1]-2*u[imax-1][j]+u[imax-1][j-1]);
            }
            for(int i=1; i<imax-1; i++)
            {
                pom[i][0]=u[i][0]+D*dt/(h*h)*(u[i+1][0]-2*u[i][0]+u[i-1][0]+u[i][1]-2*u[i][0]+u[i][jmax-1]);
            }
            for(int i=1; i<imax-1; i++)
            {
                pom[i][jmax-1]=u[i][jmax-1]+D*dt/(h*h)*(u[i+1][jmax-1]-2*u[i][jmax-1]+u[i-1][jmax-1]+u[i][0]-2*u[i][jmax-1]+u[i][jmax-2]);
            }

            pom[0][0]=u[0][0]+D*dt/(h*h)*(u[1][0]-2*u[0][0]+u[imax-1][0]+u[0][1]-2*u[0][0]+u[0][jmax-1]);
            pom[imax-1][jmax-1]=u[imax-1][jmax-1]+D*dt/(h*h)*(u[0][jmax-1]-2*u[imax-1][jmax-1]+u[imax-2][jmax-1]+u[imax-1][0]-2*u[imax-1][jmax-1]+u[imax-1][jmax-2]);
            pom[0][jmax-1]=u[0][jmax-1]+D*dt/(h*h)*(u[1][jmax-1]-2*u[0][jmax-1]+u[imax-1][jmax-1]+u[0][0]-2*u[0][jmax-1]+u[0][jmax-2]);
            pom[imax-1][0]=u[imax-1][0]+D*dt/(h*h)*(u[0][0]-2*u[imax-1][0]+u[imax-2][0]+u[imax-1][1]-2*u[imax-1][0]+u[imax-1][jmax-1]);
            for(int i = 1; i<imax-1; i++)
            {
                for(int j=1; j<jmax-1; j++)
                {
                    u[i][j]=pom[i][j];
                }
            }

            double maks=u[0][0];
            for(int i = 0; i<imax; i++)
            {
                for(int j=0; j<jmax; j++)
                {
                    if(u[i][j]>maks)
                        maks=u[i][j];
                }
            }
            for(int i = 0; i<imax; i++)
            {
                for(int j=0; j<jmax; j++)
                {
                    al_draw_filled_rectangle(i*800/imax,j*800/jmax,(i+1)*800/imax,(j+1)*800/jmax,al_map_rgb(255*u[i][j]/maks,0,255-255*u[i][j]/maks));
                }
            }
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
