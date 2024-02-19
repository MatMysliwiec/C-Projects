#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

double random_naab(double a,double b)
{
    double u=(double)(rand()%RAND_MAX)/(double)RAND_MAX;
    return a+(b-a)*u;
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

    int const L=600;
    ALLEGRO_DISPLAY *display=al_create_display(L,L);

    bool redraw=true;
    const float FPS=60;

    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    bool **grid=(bool**)malloc(L*sizeof(bool*));
    for(int i=0; i<L; i++)
        grid[i]=(bool*)malloc(L*sizeof(bool));

    for(int i=0; i<L; i++)
        for(int j=0; j<L; j++)
            grid[i][j]=false;

    /*for(int i=0;i<L;i++)
    {
        grid[i][L-1]=true;
        grid[i][1]=true;
        grid[1][i]=true;
        grid[L-1][i]=true;
    }*/

    grid[L/2][L/2]=true;
    int hist[L/2];
    for(int i=0; i<L/2; i++)
        hist[i]=0;

    int histc[L/2];
    for(int i=0; i<L/2; i++)
        histc[i]=0;

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

                double angle=random_naab(0.0,2.0*M_PI);
                double r=L/2-1.0;
                int x=(int)(r*cos(angle))+L/2;
                int y=(int)(r*sin(angle))+L/2;

                do
                {
                    double random=random_naab(0.0,1.0);
                    if(random<0.25)
                        y++;
                    else if(random<0.5&&random>=0.25)
                        y--;
                    else if(random<0.75&&random>=0.5)
                        x++;
                    else
                        x--;
                    if(x<1)
                        x=L-2;
                    if(x>L-2)
                        x=1;
                    if(y<1)
                        y=L-2;
                    if(y>L-2)
                        y=1;
                    if(grid[x-1][y]==true||grid[x+1][y]==true||grid[x][y-1]==true||grid[x][y+1]==true)
                        grid[x][y]=true;

                }
                while(grid[x][y]==false);
                double histr=sqrt((x-L/2.0)*(x-L/2.0)+(y-L/2.0)*(y-L/2.0));
                if((int)histr<L/2)
                {
                    hist[(int)histr]++;
                }

            }

            al_clear_to_color(al_map_rgb(0,0,0));

            for(int i=0; i<L; i++)
                for(int j=0; j<L; j++)
                    al_draw_pixel(i,j,al_map_rgb(grid[i][j]*255,grid[i][j]*255,grid[i][j]*255));


            al_flip_display();
        }
    }
    for(int i=0; i<L/2; i++)
        for(int j=0; j<=i; j++)
            histc[i]+=hist[j];

    for(int i=0; i<L/2; i++)
        fprintf(plik,"%d\t%d\n",i,histc[i]);
    fclose(plik);

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}

