#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    ALLEGRO_DISPLAY *display=al_create_display(1280, 720);

    bool redraw=true;
    const float FPS=600;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    double **funfal;
    funfal=(double**)malloc(320*sizeof(double*));
    for(int i=0; i<320; i++)
        funfal[i]=(double *)malloc(180*sizeof(double));

    double **pom;
    pom=(double**)malloc(320*sizeof(double*));
    for(int i=0; i<320; i++)
        pom[i]=(double *)malloc(180*sizeof(double));

    double x,y;
    double ax=-6.4,bx=6.4;
    double ay=-3.6,by=3.6;
    double u=0.5;

    for(int i=0; i<320; i++)
        for(int j=0; j<180; j++)
        {
            x=ax+(320.0-i)/320.0*(bx-ax);
            y=ay+(180.0-j)/180.0*(by-ay);
            //funfal[i][j]=exp(-5.0*(x*x+y*y))*cos(2.0*M_PI*2.0*(u*x-y*sqrt(1.0-u*u)));
            //funfal[i][j]=exp(-0.0*(x*x+y*y))*cos(2.0*M_PI*2.0*(u*x-y*sqrt(1.0-u*u)));
            funfal[i][j]=exp(-3.0*(x*x+y*y))*cos(2.0*M_PI*0.0*(u*x-y*sqrt(1.0-u*u)));
        }

    int inde,indw,indn,inds;
    double wagan,wagas,wagae,wagaw;
    double n,s,e,w;
    int nasyc;
    int er,gie,be;
    ALLEGRO_COLOR kolor;
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
            for(int i=0; i<320; i++)
                for(int j=0; j<180; j++)
                {
                    if((i+j)%2==0)
                    {
                        wagan=1.0;
                        wagas=1.0;
                        wagae=1.0;
                        wagaw=1.0;
                        inde=i+1;
                        indw=i-1;
                        indn=j+1;
                        inds=j-1;
                        if(inde>318)
                        {
                            e=0.0;
                            wagaw=2.0;
                        }
                        else
                            e=funfal[i+1][j];
                        if(indw<1)
                        {
                            w=0.0;
                            wagae=2.0;
                        }
                        else
                            w=funfal[i-1][j];
                        if(indn>178)
                        {
                            n=0.0;
                            wagas=2.0;
                        }
                        else
                            n=funfal[i][j+1];
                        if(inds<1)
                        {
                            s=0.0;
                            wagan=2.0;
                        }
                        else
                            s=funfal[i][j-1];
                        pom[i][j]=0.5*(wagae*e+wagaw*w+wagan*n+wagas*s-2.0*funfal[i][j]);
                    }
                }
            for(int i=0; i<320; i++)
                for(int j=0; j<180; j++)
                    if((i+j)%2==0)
                        funfal[i][j]=pom[i][j];
            for(int i=0; i<320; i++)
                for(int j=0; j<180; j++)
                {
                    if((i+j)%2==1)
                    {
                        wagan=1.0;
                        wagas=1.0;
                        wagae=1.0;
                        wagaw=1.0;
                        inde=i+1;
                        indw=i-1;
                        indn=j+1;
                        inds=j-1;
                        if(inde>318)
                        {
                            e=0.0;
                            wagaw=2.0;
                        }
                        else
                            e=funfal[i+1][j];
                        if(indw<1)
                        {
                            w=0.0;
                            wagae=2.0;
                        }
                        else
                            w=funfal[i-1][j];
                        if(indn>178)
                        {
                            n=0.0;
                            wagas=2.0;
                        }
                        else
                            n=funfal[i][j+1];
                        if(inds<1)
                        {
                            s=0.0;
                            wagan=2.0;
                        }
                        else
                            s=funfal[i][j-1];
                        pom[i][j]=0.5*(wagae*e+wagaw*w+wagan*n+wagas*s-2.0*funfal[i][j]);
                    }
                }
            for(int i=0; i<320; i++)
                for(int j=0; j<180; j++)
                    if((i+j)%2==1)
                        funfal[i][j]=pom[i][j];
            double minwal,maxwal;

            minwal=funfal[0][0];
            maxwal=funfal[0][0];
            for(int i=0; i<320; i++)
                for(int j=0; j<180; j++)
                {
                    if(funfal[i][j]>maxwal)
                        maxwal=funfal[i][j];
                    if(funfal[i][j]<minwal)
                        minwal=funfal[i][j];
                }
            for(int i=0; i<320; i++)
                for(int j=0; j<180; j++)
                {
                    nasyc=(maxwal-funfal[i][j])/(maxwal-minwal)*255.0;
                    if(nasyc<86)
                    {
                        er=255.0-3.0*nasyc;
                        gie=3.0*nasyc;
                        be=0.0;
                    }
                    else if(nasyc>171)
                    {
                        er=-528.434 + 3.07229*nasyc;
                        gie=0.0;
                        be=783.434 - 3.07229*nasyc;
                    }
                    else
                    {
                        er=0.0;
                        gie=513.0-3.0*nasyc;
                        be=-258.0+3.0*nasyc;
                    }
                    kolor=al_map_rgb(be,er,gie);
                    al_draw_filled_rectangle(i*4,j*4,i*4+4,j*4+4,kolor);
                }
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
