#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct fibrinogen
{
    double x[23],y[23];
    double r[23];
    double dx,dy,theta;
    double x_rt[23],y_rt[23];
} fibrinogen;
double randomnaab(double a, double b)
{
    double u=(double)(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
}
void embed(fibrinogen *fb, int where,fibrinogen &fb2)
{
    for(int i=0; i<23; i++)
    {
        fb[where].x[i]=fb2.x[i];
        fb[where].y[i]=fb2.y[i];
        fb[where].x_rt[i]=fb2.x_rt[i];
        fb[where].y_rt[i]=fb2.y_rt[i];
        fb[where].r[i]=fb2.r[i];
    }
    fb[where].dx=fb2.dx;
    fb[where].dy=fb2.dy;
    fb[where].theta=fb2.theta;
}
bool cross_over(fibrinogen *fb,int absorbed, fibrinogen fb2)
{
    double dx,dy,dr2;
    double dxs,dys,drs2;
    for(int k=0; k<absorbed; k++)
    {
        dxs=fb[k].x_rt[11]-fb2.x_rt[11];
        dys=fb[k].y_rt[11]-fb2.y_rt[11];
        drs2=dxs*dxs+dys*dys;
        if(drs2<48.7*48.7)
            for(int i=0; i<23; i++)
                for(int j=0; j<23; j++)
                {
                    dx=fb[k].x_rt[j]-fb2.x_rt[i];
                    dy=fb[k].y_rt[j]-fb2.y_rt[i];
                    dr2=dx*dx+dy*dy;
                    if(dr2<(fb[k].r[j]+fb2.r[i])*(fb[k].r[j]+fb2.r[i]))
                        return true;
                }
    }
    return false;
}
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    ALLEGRO_DISPLAY *display=al_create_display(1000, 1000);
    bool redraw=true;
    const float FPS=60;

    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    fibrinogen fb1;
    fibrinogen fb2;
    fibrinogen *fb=(fibrinogen*)malloc(10000*sizeof(fibrinogen));
    fb1.r[0]=6.7/2.0;
    fb1.r[11]=5.3/2.0;
    fb1.r[22]=6.7/2.0;
    for(int i=1; i<11; i++)
        fb1.r[i]=1.5/2.0;
    for(int i=12; i<22; i++)
        fb1.r[i]=1.5/2.0;
    for(int i=0; i<23; i++)
        fb1.y[i]=0.0;
    for(int i=0; i<10; i++)
        fb1.x[i+1]=-5.3/2.0-1.5*i-1.5/2.0;
    for(int i=0; i<10; i++)
        fb1.x[i+12]=5.3/2.0+1.5*i+1.5/2.0;
    fb1.x[0]=-21.0;
    fb1.x[11]=0.0;
    fb1.x[22]=21.0;
    for(int i=0; i<23; i++)
        fb1.x_rt[i]=fb1.x[i];
    for(int i=0; i<23; i++)
        fb1.y_rt[i]=fb1.y[i];
    embed(fb,0,fb1);
    int deposited=1;
    double L=2500.0;
    double substrate_field=L*L;
    double fibrinogen_area=127.91779887;
    double coverage;
    int time=0;
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
            for(int iter=0; iter<100; iter++)
            {
                for(int i=0; i<23; i++)
                {
                    fb2.x[i]=fb1.x[i];
                    fb2.y[i]=fb1.y[i];
                    fb2.r[i]=fb1.r[i];
                    fb2.x_rt[i]=fb1.x_rt[i];
                    fb2.y_rt[i]=fb1.y_rt[i];
                }
                fb2.dx=randomnaab(-L/2.0,L/2.0);
                fb2.dy=randomnaab(-L/2.0,L/2.0);
                fb2.theta=randomnaab(0,2.0*M_PI);
                double sintheta=sin(fb2.theta);
                double costheta=cos(fb2.theta);
                for(int i=0; i<23; i++)
                {
                    fb2.x_rt[i]=fb2.x[i]*costheta-fb2.y[i]*sintheta;
                    fb2.y_rt[i]=fb2.y[i]*costheta+fb2.x[i]*sintheta;
                }
                for(int i=0; i<23; i++)
                {
                    fb2.x_rt[i]+=fb2.dx;
                    fb2.y_rt[i]+=fb2.dy;
                }
                if((cross_over(fb,deposited,fb2)==false)
                        &&(deposited<10000))
                {
                    embed(fb,deposited,fb2);
                    deposited++;
                }
                time++;
            }
            coverage=deposited*fibrinogen_area/substrate_field;

            if(time%100==0)
            {
                fprintf(plik,"%d\t%lf\n",time,coverage);
                std::cout<<time<<"\t"<<coverage<<std::endl;
            }
            al_clear_to_color(al_map_rgb(0,0,0));

            for(int j=0; j<deposited; j++)
                for(int i=0; i<23; i++)
                    al_draw_filled_circle(400+fb[j].x_rt[i],300+1.0*fb[j].y_rt[i],1.0*fb[j].r[i],al_map_rgb(255,255,255));

            al_flip_display();
        }
    }
    fclose(plik);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}

