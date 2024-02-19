#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

double random_naab(double a,double b)
{
    double u=(double)(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
}

typedef struct
{
    double theta;
    double dx;
    double dy;
    double x1l;
    double y1l;
    double x2l;
    double y2l;
    double x1w;
    double y1w;
    double x2w;
    double y2w;
} line;

int main(int argc, char **argv)
{
    srand(time(NULL));
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *display=al_create_display(960,960);

    bool redraw=true;
    const float FPS=600;

    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    line *lines;
    int nmax=1000;
    int counter=0;
    lines = (line*)malloc(nmax*sizeof(line));

    for(int i=0; i<nmax; i++)
    {
        lines[i].x1w=0.0;
        lines[i].y1w=-0.5;
        lines[i].x2w=0.0;
        lines[i].y2w=0.5;
    }

    double L=10.0;
    double V= L*L;
    int n=0;
    FILE* plik = fopen("result.txt","w");

    for(int i=0; i<1; i++)
    {
        lines[i].theta=random_naab(0.0,2.0*M_PI);
        lines[i].dx=random_naab(0.0,L);
        lines[i].dy=random_naab(0.0,L);
        lines[i].x1l=lines[i].x1w*cos(lines[i].theta)-lines[i].y1w*sin(lines[i].theta)+lines[i].dx;
        lines[i].y1l=lines[i].x1w*sin(lines[i].theta)+lines[i].y1w*cos(lines[i].theta)+lines[i].dy;
        lines[i].x2l=lines[i].x2w*cos(lines[i].theta)-lines[i].y2w*sin(lines[i].theta)+lines[i].dx;
        lines[i].y2l=lines[i].x2w*sin(lines[i].theta)+lines[i].y2w*cos(lines[i].theta)+lines[i].dy;
    }
    n=1;

    while(n<nmax)
    {
        int cover=0;

        lines[n].theta=random_naab(0.0,2.0*M_PI);
        lines[n].dx=random_naab(0.0,L);
        lines[n].dy=random_naab(0.0,L);
        lines[n].x1l=lines[n].x1w*cos(lines[n].theta)-lines[n].y1w*sin(lines[n].theta)+lines[n].dx;
        lines[n].y1l=lines[n].x1w*sin(lines[n].theta)+lines[n].y1w*cos(lines[n].theta)+lines[n].dy;
        lines[n].x2l=lines[n].x2w*cos(lines[n].theta)-lines[n].y2w*sin(lines[n].theta)+lines[n].dx;
        lines[n].y2l=lines[n].x2w*sin(lines[n].theta)+lines[n].y2w*cos(lines[n].theta)+lines[n].dy;

        for(int i=0; i<n; i++)
        {
            double s=(lines[n].x1l*(lines[i].y1l-lines[i].y2l)
                      +lines[i].x1l*(lines[i].y2l-lines[n].y1l)
                      +lines[i].x2l*(lines[n].y1l-lines[i].y1l))
                     /((lines[n].x1l-lines[n].x2l)*(lines[i].y1l-lines[i].y2l)
                       -(lines[i].x1l-lines[i].x2l)*(lines[n].y1l-lines[n].y2l));

            double t=(lines[n].x1l*(lines[n].y2l-lines[i].y1l)
                      +lines[n].x2l*(lines[i].y1l-lines[n].y1l)
                      +lines[i].x1l*(lines[n].y1l-lines[n].y2l))
                     /((lines[i].x1l-lines[i].x2l)*(lines[n].y1l-lines[n].y2l)
                       -(lines[n].x1l-lines[n].x2l)*(lines[i].y1l-lines[i].y2l));
            if(s>=0.0 && s<=1.0 && t>=0.0 && t<=1.0)
                cover++;
            if(cover>0)
            {
                break;
            }
        }
        if(cover==0)
        {
            n++;
            printf("%d\t%.5lf\n",n,n/V);
        }
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
            for(int iter=0; iter<n; iter++)
            {

                int randomparticle=rand()%nmax;
                double deltax=random_naab(-0.1,0.1);
                double deltay=random_naab(-0.1,0.1);
                double deltatheta=random_naab(-0.1,0.1);

                if(lines[randomparticle].dx+deltax>=0 &&
                        lines[randomparticle].dx+deltax<=L &&
                        lines[randomparticle].dy+deltay>=0 &&
                        lines[randomparticle].dy+deltay<=L)
                {
                    lines[randomparticle].dx+=deltax;
                    lines[randomparticle].dy+=deltay;
                    lines[randomparticle].theta+=deltatheta;
                    lines[randomparticle].x1l=lines[randomparticle].x1w*cos(lines[randomparticle].theta)-lines[randomparticle].y1w*sin(lines[randomparticle].theta)+lines[randomparticle].dx;
                    lines[randomparticle].y1l=lines[randomparticle].x1w*sin(lines[randomparticle].theta)+lines[randomparticle].y1w*cos(lines[randomparticle].theta)+lines[randomparticle].dy;
                    lines[randomparticle].x2l=lines[randomparticle].x2w*cos(lines[randomparticle].theta)-lines[randomparticle].y2w*sin(lines[randomparticle].theta)+lines[randomparticle].dx;
                    lines[randomparticle].y2l=lines[randomparticle].x2w*sin(lines[randomparticle].theta)+lines[randomparticle].y2w*cos(lines[randomparticle].theta)+lines[randomparticle].dy;

                    int cover=0;
                    for(int i=0; i<n; i++)
                        if(i!=randomparticle)
                        {
                            double s=(lines[randomparticle].x1l*(lines[i].y1l-lines[i].y2l)
                                      +lines[i].x1l*(lines[i].y2l-lines[randomparticle].y1l)
                                      +lines[i].x2l*(lines[randomparticle].y1l-lines[i].y1l))
                                     /((lines[randomparticle].x1l-lines[randomparticle].x2l)*(lines[i].y1l-lines[i].y2l)
                                       -(lines[i].x1l-lines[i].x2l)*(lines[randomparticle].y1l-lines[randomparticle].y2l));

                            double t=(lines[randomparticle].x1l*(lines[randomparticle].y2l-lines[i].y1l)
                                      +lines[randomparticle].x2l*(lines[i].y1l-lines[randomparticle].y1l)
                                      +lines[i].x1l*(lines[randomparticle].y1l-lines[randomparticle].y2l))
                                     /((lines[i].x1l-lines[i].x2l)*(lines[randomparticle].y1l-lines[randomparticle].y2l)
                                       -(lines[randomparticle].x1l-lines[randomparticle].x2l)*(lines[i].y1l-lines[i].y2l));
                            if(s>=0.0 && s<=1.0 && t>=0.0 && t<=1.0)
                                cover++;
                            if(cover>0)
                                break;
                        }
                    if(cover>0)
                    {
                        lines[randomparticle].dx-=deltax;
                        lines[randomparticle].dy-=deltay;
                        lines[randomparticle].theta-=deltatheta;
                        lines[randomparticle].x1l=lines[randomparticle].x1w*cos(lines[randomparticle].theta)-lines[randomparticle].y1w*sin(lines[randomparticle].theta)+lines[randomparticle].dx;
                        lines[randomparticle].y1l=lines[randomparticle].x1w*sin(lines[randomparticle].theta)+lines[randomparticle].y1w*cos(lines[randomparticle].theta)+lines[randomparticle].dy;
                        lines[randomparticle].x2l=lines[randomparticle].x2w*cos(lines[randomparticle].theta)-lines[randomparticle].y2w*sin(lines[randomparticle].theta)+lines[randomparticle].dx;
                        lines[randomparticle].y2l=lines[randomparticle].x2w*sin(lines[randomparticle].theta)+lines[randomparticle].y2w*cos(lines[randomparticle].theta)+lines[randomparticle].dy;
                    }
                }
            }
            counter++;
            std::cout<<counter<<std::endl;

            al_clear_to_color(al_map_rgb(0,0,0));

            for(int i=0; i<n; i++)
            {
                al_draw_line(100.0*lines[i].x1l,100.0*lines[i].y1l,100.0*lines[i].x2l,100.0*lines[i].y2l,al_map_rgb(255,0,0),1.0);
            }

            al_flip_display();
        }
    }
    double Qxx=0.0;
    double Qxy=0.0;
    double Qyy=0.0;

    int k;
    for(k=0; k<n; k++)
    {
        Qxx+=(1.0/n)*((lines[k].x2l-lines[k].x1l)*(lines[k].x2l-lines[k].x1l)-0.5);
        Qyy+=(1.0/n)*((lines[k].y2l-lines[k].y1l)*(lines[k].y2l-lines[k].y1l)-0.5);
        Qxy+=(1.0/n)*((lines[k].x2l-lines[k].x1l)*(lines[k].y2l-lines[k].y1l));
    }
    fprintf(plik,"%i\t%lf\t%lf\t%lf\t%lf\t%lf\n",k,Qxx,Qxy,Qyy,sqrt(Qxx*Qxx+Qxy*Qxy),n/V);
    fclose(plik);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
