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
struct snakeHead{
     int x;
     int y;
};
struct snakeTail{
     int x;
     int y;
};
struct food{
     int x;
     int y;
};
typedef struct prev prev;
typedef struct snakeHead snakeHead;
typedef struct snakeTail snakeTail;
typedef struct food food;
prev p;
snakeHead head;
food fruit;
snakeTail tail[1500];
int score=0;
int snakeLength=4;
const int boardlength=20;
const int boardwidth=50;
const char arrowkeys[]={72,75,80,77,'q'};
void displayEnvironment(){
    for(int i=1;i<=boardlength;i++){
        for(int j=1;j<=boardwidth;j++){
            if((i==1)||(j==1)||(j==boardwidth)||(i==boardlength)){
                printf("\033[%d;%dH",i,j);
                printf("X");
            }
        }
    }
}
void displayHead(){
    printf("\033[%d;%dH",head.y,head.x);
    printf("O");
}
void displayTail(){
    tail[0].x=p.x;
    tail[0].y=p.y;
    printf("\033[%d;%dH",tail[snakeLength-1].y,tail[snakeLength-1].x);
    printf(" ");
    for(int i=snakeLength-1;i>0;i--){
        tail[i].x=tail[i-1].x;
        tail[i].y=tail[i-1].y;
        printf("\033[%d;%dH",tail[i].y,tail[i].x);
        printf("+");
    }
}
void displayFruit(){
    printf("\033[%d;%dH",fruit.y,fruit.x);
    printf("o");
}
int forbiddenHeadPosition(){
  if(head.x==boardwidth||head.y==boardlength||head.x==1||head.y==1)
        return 1;
  for(int i=0;i<snakeLength;i++){
    if(head.x==tail[i].x&&head.y==tail[i].y){
       return 1;
    }
  }
  return 0;
}
void checkHeadPosition(){
    if(forbiddenHeadPosition()){
        printf("\033[%d;%dH",(boardlength)/2,(boardwidth+5));
        printf("SORRY!!! YOU CRASHED");
        printf("\n");
        printf("\033[%dG",boardwidth+5);
        printf("SCORE: %d",score);
        getch();
        exit(0);
    }
}
int forbiddenFruitPosition(){
  for(int i=0;i<snakeLength;i++){
    if(fruit.x==tail[i].x&&fruit.y==tail[i].y){
       return 1;
    }
  }
  return 0;
}
void checkValidity(){
    clock_t time1=clock();
    while(forbiddenFruitPosition()||(head.x==fruit.x&&head.y==fruit.y)){
        fruit.x=rand()%(boardwidth-2)+2;
        fruit.y=rand()%(boardlength-2)+2;
        clock_t time2=clock();
        double time=(double)((time2-time1)/CLOCKS_PER_SEC);
        if(time>5){
            printf("\033[%d;%dH",(boardlength)/2,(boardwidth+5));
            printf("CONGRATULATIONS YOU WON THE GAME\n\033[%dG YOU ARE A GENIOUS",boardwidth+5);
            printf("\n");
            printf("\033[%dG",boardwidth+5);
            printf("SCORE: %d",score);
            getch();
            exit(0);
        }
    }
}
void checkpoint(){
    if(head.x==fruit.x&&head.y==fruit.y){
        printf("\033[%d;%dH",fruit.y,fruit.x);
        printf(" ");
        fruit.x=rand()%(boardwidth-2)+2;
        fruit.y=rand()%(boardlength-2)+2;
        score++;
        snakeLength++;
    }
}
void initialHeadPosition(){
    head.x=5;
    head.y=2;
    displayHead();
}
void initialFruitPosition(){
    fruit.x=rand()%(boardwidth-2)+2;
    fruit.y=rand()%(boardlength-2)+2;
    while(head.x==fruit.x&&head.y==fruit.y||(fruit.x==4&&fruit.y==2)||(fruit.x==3&&fruit.y==2)||(fruit.x==2&&fruit.y==2)){
        fruit.x=rand()%(boardwidth-2)+2;
        fruit.y=rand()%(boardlength-2)+2;
    }
    displayFruit();
}
void initialTailPosition(){
    for(int i=1;i<snakeLength;i++){
        tail[i].x=5-i;
        tail[i].y=2;
        printf("\033[%d;%dH",tail[i].y,tail[i].x);
        printf("+");
    }
}

void displaysnakeInitially(){
    initialHeadPosition();
    initialTailPosition();
    initialFruitPosition();
}
void movement(){
     while(1){
        if(kbhit()){
            char c=_getch();
            if(strchr(arrowkeys,c)!=NULL){
              p.x=head.x;
              p.y=head.y;
              if(c==72)
                head.y--;
              else if(c==75)
                head.x--;
              else if(c==80)
                head.y++;
              else if(c==77)
                head.x++;
              else if(c=='q')
                exit(0);
              checkpoint();
              displayTail();
              displayHead();
              checkHeadPosition();
              checkValidity();
              displayFruit();
           }
        }
     }
}
int main(){
   printf("\033[?25l");
   displayEnvironment();
   displaysnakeInitially();
   movement();
   return 0;
}
