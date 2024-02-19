#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double random(double a,double b)
{
    double u=(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
}
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display=al_create_display(800, 800);

    bool redraw=true;
    const float FPS=1000;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    int imax=80,jmax=80;
    double **U,**pom;

    U=new double*[imax];
    for(int i=0; i<imax; i++)
        U[i]=new double[jmax];

    pom=new double*[imax];
    for(int i=0; i<imax; i++)
        pom[i]=new double[jmax];

    for(int i=1; i<imax-1; i++)
        for(int j=1; j<jmax-1; j++)
            U[i][j]=random(-200.0,200.0);

    double **rij;
    rij=new double*[imax];
    for(int i=0;i<imax;i++)
    {
        rij[i]=new double [jmax];
    }

    for(int i=0;i<imax;i++)
        for(int j=0;j<jmax;j++)
            {
                rij[i][j]=0;
            }

    double h=1.5;
    /*rij[20][20]=1/(h*h);
    rij[50][40]=1/(h*h);
    rij[70][10]=1/(h*h);*/

    rij[20][10]=1/(h*h);
    rij[35][10]=1/(h*h);
    rij[50][10]=1/(h*h);
    rij[70][10]=1/(h*h);

    rij[20][70]=1/(h*h);
    rij[35][70]=1/(h*h);
    rij[50][70]=1/(h*h);
    rij[70][70]=1/(h*h);

    rij[10][20]=1/(h*h);
    rij[10][35]=1/(h*h);
    rij[10][50]=1/(h*h);
    rij[10][70]=1/(h*h);
    for(int i=0; i<imax; i++)
        U[i][0]=-(cos(2.0*M_PI*(double)i/(double)imax)
                *cosh(2.0*M_PI*(double)0/(double)jmax)+cosh(2.0*M_PI));
        //U[i][0] = cos(2.0*M_PI*(double)i/(double)imax)
          //           *cosh(2.0*M_PI*(double)(jmax-1)/(double)jmax)+cosh(2.0*M_PI);;
        //U[i][0]=sin(2.0*M_PI*(double)i/(double)imax)
                //*sinh(2.0*M_PI*(double)0/(double)jmax)+sinh(2.0*M_PI);

    for(int i=0; i<imax; i++)
        U[i][jmax-1]=cos(2.0*M_PI*(double)i/(double)imax)
                     *cosh(2.0*M_PI*(double)(jmax-1)/(double)jmax)+cosh(2.0*M_PI);
       // U[i][jmax-1]=sin(2.0*M_PI*(double)i/(double)imax)
         //            *sinh(2.0*M_PI*(double)(jmax-1)/(double)jmax);
        //U[i][jmax-1]=sin(2.0*M_PI*(double)i/(double)imax)
           //          *sinh(2.0*M_PI*(double)(jmax-1)/(double)jmax)+sinh(2.0*M_PI);

    for(int j=0; j<jmax; j++)
        U[0][j]=sin(2.0*M_PI*(double)0/(double)imax)
                *cosh(2.0*M_PI*(double)j/(double)jmax)+cosh(2.0*M_PI);
        //U[0][j]=sin(2.0*M_PI*(double)0/(double)imax)
                //*sinh(2.0*M_PI*(double)j/(double)jmax)+sinh(2.0*M_PI);
        //U[0][j]=sin(2.0*M_PI*(double)0/(double)imax)
         //       *sinh(2.0*M_PI*(double)j/(double)jmax)+sinh(2.0*M_PI);

    for(int j=0; j<jmax; j++)
        U[imax-1][j]=sin(2.0*M_PI*(double)(imax-1)/(double)imax)
                     *sinh(2.0*M_PI*(double)j/(double)jmax)+sinh(2.0*M_PI);
       // U[imax-1][j]=-(sin(2.0*M_PI*(double)(imax-1)/(double)imax)
         //            *sinh(2.0*M_PI*(double)j/(double)jmax)+sinh(2.0*M_PI));
        // U[imax-1][j]=sin(2.0*M_PI*(double)(imax-1)/(double)imax)
         //            *sinh(2.0*M_PI*(double)j/(double)jmax)+sinh(2.0*M_PI);

    double color,colormin,colormax;
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
                for(int j=1; j<jmax-1; j++)
                    pom[i][j]=0.25*(U[i+1][j]+U[i-1][j]+U[i][j+1]+U[i][j-1]+h*h*rij[i][j]);

            for(int i=1; i<imax-1; i++)
                for(int j=1; j<jmax-1; j++)
                    U[i][j]=pom[i][j];

            colormin=U[0][0];
            colormax=U[0][0];

            for(int i=0; i<imax; i++)
                for(int j=0; j<jmax; j++)
                {
                    if(U[i][j]<colormin)
                        colormin=U[i][j];
                    if(U[i][j]>colormax)
                        colormax=U[i][j];
                }

            for(int i=0; i<imax; i++)
                for(int j=0; j<jmax; j++)
                {
                    color=(U[i][j]-colormin)/(colormax-colormin)*255.0;
                    al_draw_filled_rectangle(i*(800.0/(double)imax),j*(800.0/(double)jmax),
                                             (i+1.0)*(800.0/(double)imax),(j+1.0)*(800.0/(double)jmax),
                                             al_map_rgb(color,0,255-color));
                }
            al_flip_display();
        }
    }
    for(int i=0; i<imax; i++)
        delete[] U[i];
    delete[] U;
    for(int i=0; i<imax; i++)
        delete[] pom[i];
    delete[] pom;
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
