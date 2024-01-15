#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
struct prev{
     int x;
     int y;
};
struct snakeH{
     int x;
     int y;
};
struct snakeT{
     int x;
     int y;
};
struct fruit{
     int x;
     int y;
};
typedef struct prev prev;
typedef struct snakeH head;
typedef struct snakeT tail;
typedef struct fruit fruit;
prev p;
head a;
fruit b;
tail c[1500];
int score=0;
int temp=4;
int forbid(){
  for(int i=0;i<temp;i++){
    if(b.x==c[i].x&&b.y==c[i].y){
       return 1;
    }
  }
  return 0;
}
void check(){
    while(forbid()){
        b.x=rand()%30;
        b.y=rand()%15;
    }
}
void checkp(){
    int t=0;
    while(a.x==b.x&&a.y==b.y){
        b.x=rand()%30;
        b.y=rand()%15;
        t=1;
    }
    if(t==1){
        score++;
        temp++;
    }
}
void initialize(){
    a.x=4;
    a.y=1;
    b.x=rand()%30;
    b.y=rand()%15;
    checkp();
}
void dispti(){
    c[0].x=a.x;
    c[0].y=a.y;
    for(int i=1;i<4;i++){
        c[i].x=(c[0].x)-i;
        c[i].y=c[0].y;
        printf("\033[%d;%dH",c[i].y,c[i].x);
        printf("+");
    }
}
void disph(){
    printf("\033[2J");
    printf("\033[%d;%dH",a.y,a.x);
    printf("O");
    printf("\033[%d;%dH",b.y,b.x);
    printf("o");

}
void dispt(){
    c[0].x=p.x;
    c[0].y=p.y;
    for(int i=temp-1;i>0;i--){
        c[i].x=c[i-1].x;
        c[i].y=c[i-1].y;
        printf("\033[%d;%dH",c[i].y,c[i].x);
        printf("+");
    }
}
void move(){
     while(1){
        if(kbhit()){
            char c=getch();
            if(strchr("ijklqv",c)!=NULL){
              p.x=a.x;
              p.y=a.y;
              if(c=='i')
                a.y--;
              else if(c=='j')
                a.x--;
              else if(c=='k')
                a.y++;
              else if(c=='l')
                a.x++;
              else if(c=='q')
                exit(0);
              checkp();
              disph();
              dispt();
           }
        }
     }
}
void dispsnake(){
    disph();
    dispti();
}
int main(){
   initialize();
   dispsnake();
   move();
   return 0;
}
