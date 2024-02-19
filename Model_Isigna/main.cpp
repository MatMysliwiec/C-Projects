#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *mojaczcionka=al_load_ttf_font("czcionka.ttf",18,0);
    ALLEGRO_DISPLAY *display=al_create_display(500,500);
    ALLEGRO_DISPLAY *display2=al_create_display(1000,200);
    ALLEGRO_DISPLAY *display3=al_create_display(1000,200);
    bool redraw=true;
    const float FPS=60;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    int L=100;
    int N=L*L;
    int **spins;
    spins=(int**)malloc(L*sizeof(int*));
    for(int i=0; i<L; i++)
        spins[i]=(int*)malloc(L*sizeof(int));
    for(int i=0; i<L; i++)
        for(int j=0; j<L; j++)
            spins[i][j]=2*(rand()%2)-1;
    ALLEGRO_COLOR czerwony=al_map_rgb(255,0,0);
    ALLEGRO_COLOR niebieski=al_map_rgb(0,0,255);
    ALLEGRO_COLOR bialy=al_map_rgb(255,255,255);
    ALLEGRO_COLOR zielony=al_map_rgb(0,255,0);
    ALLEGRO_COLOR fiolet=al_map_rgb(255,0,255);
    double T=2.0;
    double J=1.0;
    double h=0.0;
    double randomnumber;
    double deltaE;
    double expB;
    int li,lj;
    double M;
    double Mt[N];
    for(int i=0; i<N; i++)
        Mt[i]=0.0;
    double Msr;
    double E;
    double Et[N];
    for(int i=0; i<N; i++)
        Et[i]=0.0;
    double Esr;
    double M2;
    double M2t[2*N];
    for(int i=0; i<N; i++)
        M2t[i]=0.0;
    double M2sr;
    double E2;
    double E2t[N];
    for(int i=0; i<N; i++)
        E2t[i]=0.0;
    double E2sr;
    double X;
    double C;
    int counter=0;
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
            for(int k=0; k<N; k++)
            {
                li=rand()%L;
                lj=rand()%L;
                deltaE=2.0*J*(double)spins[li%L][lj%L]*
                       (spins[(li-1+L)%L][lj%L]+spins[(li+1)%L][lj%L]
                        +spins[li%L][(lj-1+L)%L]+spins[li%L][(lj+1)%L])+2.0*h*spins[li][lj];
                if(deltaE<0.0)
                {
                    spins[li][lj]*=-1;
                }
                else
                {
                    expB=exp(-deltaE/T);
                    randomnumber=((double)(rand()%RAND_MAX))/(double)RAND_MAX;
                    if(randomnumber<expB)
                        spins[li][lj]*=-1;
                }
            }
            M=0.0;
            E=0.0;
            for(int i=0; i<L; i++)
                for(int j=0; j<L; j++)
                {
                    M+=(double)spins[i][j];
                    E+=-0.5*J*spins[i%L][j%L]*
                       (spins[(i-1+L)%L][j%L]+spins[(i+1)%L][j%L]
                        +spins[i%L][(j-1+L)%L]+spins[i%L][(j+1)%L])-h*spins[i][j];
                }
            M/=(double)N;
            E/=(double)N;
            counter++;
            counter=counter%N;
            std::cout<<counter<<std::endl;
            Mt[counter]=M;
            Et[counter]=E;
            M2t[counter]=M*M;
            E2t[counter]=E*E;

            Msr=0.0;
            Esr=0.0;
            M2sr=0.0;
            E2sr=0.0;
            X=0.0;
            C=0.0;
            for(int i=0; i<N; i++)
            {
                Msr+=Mt[i];
                Esr+=Et[i];
                M2sr+=M2t[i];
                E2sr+=E2t[i];
            }
            Msr/=10000.0;
            Esr/=10000.0;
            M2sr/=10000.0;
            E2sr/=10000.0;

            X = (M2sr-(Msr*Msr))/T;
            C = (E2sr-(Esr*Esr))/(T*T);

            al_set_target_bitmap(al_get_backbuffer(display2));
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_line(0,100,1000,100,al_map_rgb(127,127,127),1);
            for(int i=0; i<1000; i++)
            {
                al_draw_filled_circle(i,100.0-100.0*Mt[i],2,bialy);
                al_draw_filled_circle(i,100.0-100.0*M2t[i],2,zielony);
            }
            al_draw_textf(mojaczcionka,bialy,10,10,ALLEGRO_ALIGN_LEFT,"M=%f",Msr);
            al_draw_textf(mojaczcionka,zielony,10,40,ALLEGRO_ALIGN_LEFT,"M2=%f",M2sr);
            al_flip_display();
            al_set_target_bitmap(al_get_backbuffer(display3));
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_line(0,100,1000,100,al_map_rgb(127,127,127),1);
            for(int i=0; i<1000; i++)
            {
                al_draw_filled_circle(i,200*0.667-33.3*Et[i],2,bialy);
                al_draw_filled_circle(i,200*0.667-33.3*E2t[i],2,fiolet);
            }
            al_draw_textf(mojaczcionka,bialy,10,10,ALLEGRO_ALIGN_LEFT,"E=%f",Esr);
            al_draw_textf(mojaczcionka,fiolet,10,40,ALLEGRO_ALIGN_LEFT,"E2=%f",E2sr);
            al_flip_display();
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0,0,0));
            for(int i=0; i<L; i++)
                for(int j=0; j<L; j++)
                {
                    if(spins[i][j]==1)
                        al_draw_filled_rectangle(5*i,5*j,5*i+5,5*j+5,czerwony);
                    else
                        al_draw_filled_rectangle(5*i,5*j,5*i+5,5*j+5,niebieski);
                }
            al_flip_display();
        }
    }
    fprintf(plik, "%lf\t%lf\t%.7lf\t%.7lf\t%.7lf\t%.7lf\n",T,h,Msr,Esr,X,C);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    fclose(plik);
    return 0;

}

