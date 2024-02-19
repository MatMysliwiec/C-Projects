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

double **grip;
int L=50;
int N=L*L;
double J=1.0;

FILE *plik = fopen("result.txt","w");
FILE *plik2 = fopen("parameter.txt","w");

double randomnaab(double a,double b)
{
    double u=(double)(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
}
void inic()
{
    grip=new double*[L];
    for(int i=0; i<L; i++)
        grip[i]=new double [L];
    for(int i=0; i<L; i++)
        for(int j=0; j<L; j++)
            grip[i][j]=randomnaab(0.0,2.0*M_PI);
}

void stepMC(double T)
{
    int i=rand()%L;
    int j=rand()%L;

    double dE=0.0;
    double dThete=randomnaab(-0.5,0.5);
    double newangle=grip[i][j]+dThete;
    double h=0.0; //model with external EM field

    dE+=J*cos(grip[i][j]-grip[(i+1)%L][j]);
    dE+=J*cos(grip[i][j]-grip[(i-1+L)%L][j]);
    dE+=J*cos(grip[i][j]-grip[i][(j+1)%L]);
    dE+=J*cos(grip[i][j]-grip[i][(j-1+L)%L]);

    dE-=J*cos(newangle-grip[(i+1)%L][j]);
    dE-=J*cos(newangle-grip[(i-1+L)%L][j]);
    dE-=J*cos(newangle-grip[i][(j+1)%L]);
    dE-=J*cos(newangle-grip[i][(j-1+L)%L]);//modelXY

    /*dE+=J*(0.25+0.75*cos(2.0*(grip[i][j]-grip[(i+1)%L][j])));
    dE+=J*(0.25+0.75*cos(2.0*(grip[i][j]-grip[(i-1+L)%L][j])));
    dE+=J*(0.25+0.75*cos(2.0*(grip[i][j]-grip[i][(j+1)%L])));
    dE+=J*(0.25+0.75*cos(2.0*(grip[i][j]-grip[i][(j-1+L)%L])));

    dE-=J*(0.25+0.75*cos(2.0*(newangle-grip[(i+1)%L][j])));
    dE-=J*(0.25+0.75*cos(2.0*(newangle-grip[(i-1+L)%L][j])));
    dE-=J*(0.25+0.75*cos(2.0*(newangle-grip[i][(j+1)%L])));
    dE-=J*(0.25+0.75*cos(2.0*(newangle-grip[i][(j-1+L)%L])));//model Lebwohl-Lasher*/

    //dE+=h*cos(grip[i][j]);
    dE+=h*0.707*cos(grip[i][j])+h*0.707*sin(grip[i][j]);
    //dE+=h*sin(grip[i][j]);


    //dE-=h*cos(newangle);
    dE-=h*0.707*cos(newangle)+h*0.707*sin(newangle);
    //dE-=h*sin(newangle);

    if(dE<0.0)
    {
        grip[i][j]=newangle;
    }
    else
    {
        double random=randomnaab(0.0,1.0);
        if(random<exp(-dE/T))
        {
            grip[i][j]=newangle;
        }
    }
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
    ALLEGRO_FONT *mojaczcionka=al_load_ttf_font("czcionka.ttf",18,0);
    ALLEGRO_DISPLAY *display=al_create_display(800,800);
    bool redraw=true;
    const float FPS=600;

    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    ALLEGRO_COLOR czerwony=al_map_rgb(255,0,0);
    ALLEGRO_COLOR niebieski=al_map_rgb(0,0,255);
    ALLEGRO_COLOR bialy=al_map_rgb(255,255,255);
    ALLEGRO_COLOR zielony=al_map_rgb(0,255,0);
    ALLEGRO_COLOR fiolet=al_map_rgb(255,0,255);

    double T=1.0;

    inic();

    double E=0.0;
    int counter1=0;
    double M=0.0;
    double h=0.0;
    double Mt[N];
    for(int i=0; i<N; i++)
        Mt[i] = 0.0;
    double Et[N];
    for(int i=0; i<N; i++)
        Et[i]=0.0;;
    double M2t[N];
    for(int i=0; i<N; i++)
        M2t[i]=0.0;
    double E2t[N];
    for(int i=0; i<N; i++)
        E2t[i]=0.0;
    double Msr=0.0;
    double Esr=0.0;
    double M2sr=0.0;
    double E2sr=0.0;
    double X=0.0;
    double C=0.0;

    double scale_x=al_get_bitmap_width(al_get_backbuffer(display))/(double)L;
    double scale_y=al_get_bitmap_height(al_get_backbuffer(display))/(double)L;

    double color;
    double sine1,cosine1;
    double sine2,cosine2;
    double wskx,wsky;

    double Qxx=0.0;
    double Qxy=0.0;
    int counter2=0;

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
            for(int i=0; i<N; i++)
            {
                stepMC(T);
            }

            M=0.0;
            E=0.0;
            for(int i=0; i<L; i++)
                for(int j=0; j<L; j++)
                {
                    sine1=sin(grip[i][j]);
                    cosine1=cos(grip[i][j]);
                    M+=sqrt(sine1*sine1+cosine1*cosine1);
                    E+=-0.5*J*cos(grip[i][j]-grip[(i+1)%L][j]);
                    E+=-0.5*J*cos(grip[i][j]-grip[(i-1+L)%L][j]);
                    E+=-0.5*J*cos(grip[i][j]-grip[i][(j+1)%L]);
                    E+=-0.5*J*cos(grip[i][j]-grip[i][(j-1+L)%L]);
                    E+=-h*0.707*cos(grip[i][j])+h*0.707*sin(grip[i][j]);
                }
            M/=(double)N;
            E/=(double)N;
            counter1++;
            counter1=counter1%N;
            counter2++;
            std::cout<<counter2<<std::endl;
            Mt[counter1]=M;
            Et[counter1]=E;
            M2t[counter1]=M*M;
            E2t[counter1]=E*E;

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
            Msr/=N;
            Esr/=N;
            M2sr/=N;
            E2sr/=N;
            X = (M2sr-(Msr*Msr))/T;
            C = (E2sr-(Esr*Esr))/(T*T);



            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0,0,0));

            for(int i=0; i<L; i++)
                for(int j=0; j<L; j++)
                {
                    //color=(cos(grip[i][j])+1.0)*0.5*255.0;
                    color=(cos(2.0*grip[i][j])+1.0)*0.5*255.0;
                    al_draw_filled_rectangle(scale_x*i,scale_y*j,scale_x*(i+1),scale_y*(j+1),al_map_rgb(color,0,255.0-color));
                }

            for(int i=0; i<L; i++)
                for(int j=0; j<L; j++)
                {
                    sine2=sin(grip[i][j]);
                    cosine2=cos(grip[i][j]);
                    Qxx+=(1.0/N)*((cosine2*cosine2)-0.5);
                    Qxy+=(1.0/N)*(cosine2*sine2);
                    wskx=0.5*scale_x*cosine2;
                    wsky=0.5*scale_y*sine2;
                    al_draw_line(scale_x*(i+0.5),scale_y*(j+0.5),scale_x*(i+0.5)+wskx,scale_y*(j+0.5)+wsky,bialy,2);
                    //al_draw_line(scale_x*(i+0.5)-wskx,scale_y*(j+0.5)-wsky,scale_x*(i+0.5)+wskx,scale_y*(j+0.5)+wsky,bialy,2);
                }

            for(int i=0; i<L; i++)
                for(int j=0; j<L; j++)
                {
                    double ang1=fabs(grip[i][j]-grip[(i+1)%L][j]);
                    double ang2=fabs(grip[i][j]-grip[(i-1+L)%L][j]);
                    double ang3=fabs(grip[i][j]-grip[i][(j+1)%L]);
                    double ang4=fabs(grip[i][j]-grip[i][(j-1+L)%L]);

                    if((ang1>1.31&&ang1<1.83) || (ang1>4.45&&ang1<4.97))
                        al_draw_rectangle(scale_x*i,scale_y*j,scale_x*(i+1),scale_y*(j+1),zielony,3);

                    if((ang2>1.31&&ang2<1.83) || (ang2>4.45&&ang2<4.97))
                        al_draw_rectangle(scale_x*i,scale_y*j,scale_x*(i+1),scale_y*(j+1),zielony,3);

                    if((ang3>1.31&&ang3<1.83) || (ang3>4.45&&ang3<4.97))
                        al_draw_rectangle(scale_x*i,scale_y*j,scale_x*(i+1),scale_y*(j+1),zielony,3);

                    if((ang4>1.31&&ang4<1.83) || (ang4>4.45&&ang4<4.97))
                        al_draw_rectangle(scale_x*i,scale_y*j,scale_x*(i+1),scale_y*(j+1),zielony,3);
                }
            al_flip_display();

        }
    }
    fprintf(plik, "%lf\t%lf\t%.7lf\t%.7lf\t%.7lf\t%.7lf\n",T,h,Msr,Esr,X,C);
    Qxx/=counter2;
    Qxy/=counter2;
    fprintf(plik2,"%lf\t%lf\t%lf\t%lf\t%lf\n",Qxx,Qxy,sqrt(Qxx*Qxx+Qxy*Qxy),T,h);
    fclose(plik);
    fclose(plik2);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
