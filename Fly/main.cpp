#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

double random_naab(double a,double b)
{
    double u=(double)(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
}

typedef struct fly
{
    double x, y;
    double beta,theta;
    double v0;
}fly;

void actualization(fly &m, double alpha,double sigma,double kappa,double dt)
{
    double eps=0.0000001;
    double U1=random_naab(0.0+eps,1.0-eps);
    double U2=random_naab(0.0+eps,1.0-eps);
    double V = M_PI*(U1-0.5);
    double W = -log(U2);
    double X = sin(alpha*V)/pow(cos(V),1.0/alpha)*pow(cos((alpha-1.0)*V)/W,(1.0-alpha)/alpha);

    m.beta=atan2(m.y,m.x);
    m.theta=m.theta+kappa*sin(m.theta-m.beta)*dt+sigma/m.v0*X*pow(dt,1.0/alpha);
    m.x=m.x+m.v0*cos(m.theta)*dt;
    m.y=m.y+m.v0*sin(m.theta)*dt;
}

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

    ALLEGRO_DISPLAY *display=al_create_display(1280,720);

    bool redraw=true;
    const float FPS=1000;

    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    fly muszka;
    muszka.x=0.5;
    muszka.y=0.5;
    muszka.v0=1.0;
    muszka.theta=1.0;

    double dt=0.01;
    double kappa=0.9;
    double sigma=0.1;
    double alpha=1.9;

    ALLEGRO_BITMAP *flybmp=al_load_bitmap("mucha.jpg");
    ALLEGRO_BITMAP *sugarbmp=al_load_bitmap("cukier.jpg");

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

            actualization(muszka,alpha,sigma,kappa,dt);
            al_draw_bitmap(sugarbmp,640-153.0/2.0,360,0-102.0/2.0);

            al_draw_tinted_rotated_bitmap(flybmp,al_map_rgba_f(1,1,1,0),153.0/2.0,102.0/2.0,640+muszka.x*50.0,360+muszka.y*50.0,muszka.theta+0.5*M_PI,0);
            //al_draw_filled_circle(640+muszka.x*10.0,360+muszka.y*10.0,2,al_map_rgb(255,255,255));

            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}

