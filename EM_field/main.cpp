#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
class compleks
{
private:
    double Re,Im;
public:
    compleks ():Re(0),Im(0){}
    compleks (double Re,double Im):Re(Re),Im(Im){}
    double r()const{return Re;}
    double i()const{return Im;}
    friend compleks operator*(const compleks &, const compleks &);
    friend compleks operator*(const double &, const compleks &);
    friend compleks operator+(const compleks &, const compleks &);
    friend compleks operator-(const compleks &, const compleks &);
};

compleks operator*(const compleks &a,const compleks &b)
{
    double R,U;
    R=a.r()*b.r()-a.i()*b.i();
    U=a.r()*b.i()+a.i()*b.r();
    return compleks(R,U);
}

compleks operator*(const double &a,const compleks &b)
{
    double R,U;
    R=a*b.r();
    U=a*b.i();
    return compleks(R,U);
}

compleks operator+(const compleks &a,const compleks &b)
{
    double R,U;
    R=a.r()+b.r();
    U=a.i()+b.i();
    return compleks(R,U);
}

compleks operator-(const compleks &a,const compleks &b)
{
    double R,U;
    R=a.r()-b.r();
    U=a.i()-b.i();
    return compleks(R,U);
}
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

    compleks r(0,0);
    compleks v(1,0);
    double e=1,c=1,m=1,Bz=1;
    double omega = e*Bz/(m*c);
    double dt=0.1,t = 0.0;
    double alpha= 0.5*dt*omega;
    compleks skalav((1-alpha*alpha)/(1+alpha*alpha),-2*alpha/(1+alpha*alpha));
    compleks pomoc;

    compleks E(-0.75,-0.5);
    compleks dE(0,0);
    compleks a1(1,-alpha);
    dE=e/m*a1*E;

    FILE *plik = fopen("result.txt", "w");
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

            pomoc=v;
            v=dt*dE+skalav*v;
            r=r+0.5*dt*(v+pomoc);
            t = t + dt;
            double Ek, Ep, Et;
            Ek = 0.5 * m * (v.r() * v.r() + v.i() * v.i());

            Ep = -e * Bz * (r.r() * v.i() - r.i() * v.r());

            Et = Ek + Ep;
            fprintf(plik, "%lf\t%lf\t%lf\t%lf\n", t,Ek, Ep, Et);
            //al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_filled_circle(400+r.r()*25,400+r.i()*25,2,al_map_rgb(255,255,255));
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
