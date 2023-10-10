#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define LENGTH_FRAME 5
#define LENGTH_TEMPLATE 3

void printFrame();
bool haveSpaces();
bool isFinished(char round);
void moveComputer();
void move();
void change(char *word);

char frame[LENGTH_FRAME][LENGTH_FRAME]={
        {' ','|',' ','|',' '},
        {'-','|','-','|','-'},
        {' ','|',' ','|',' '},
        {'-','|','-','|','-'},
        {' ','|',' ','|',' '},
    };
char template[LENGTH_TEMPLATE][LENGTH_TEMPLATE]={
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '},
};
char player;
char computer;

int main(void){
    system("clear");
    srand(time(NULL));
    int r=rand()%2;
    player=(r==0)? 'X':'O';
    computer=(player == 'X')? 'O':'X';
	printf("You are: %c. Make your move.\n", player);
    if(player == 'X'){
        printFrame();
        move();
        return 0;
    }
    moveComputer();
    return 0;
    
}
/* 
Prints the frame.
*/
void printFrame(){
    printf("  1 2 3\n");
    for(int i=0;i<LENGTH_FRAME;i++){
        switch(i){
            case 0: printf("A ");
            break;
            case 2: printf("B ");
            break;
            case 4: printf("C ");
            break;
            default: printf("  ");
        }
        for(int j=0;j<LENGTH_FRAME;j++){
            
            printf("%c",frame[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/*
Checks if the 3x3 table still has spaces. Some functions depend
on this function.
*/
bool haveSpaces(){
    for(int i=0;i<LENGTH_TEMPLATE;i++){
        for(int j=0;j<LENGTH_TEMPLATE; j++)
            if(template[i][j] == ' '){
                return true;
            }
    }
    return false;
}
/*
Checks template for certain moves that determines the player/computer won or not.
Could be improved :(
*/
bool isFinished(char round){
    int atx=0;
    int aty=0;
    while(aty < 3){
        if(template[atx][aty]== round && template[atx][aty] == template[atx+1][aty] && template[atx+1][aty] == template[atx+2][aty])
            return true;
        aty++;
    }
    aty=0;
    while(atx < 3){
        if(template[atx][aty]== round && template[atx][aty] == template[atx][aty+1] && template[atx][aty+1] == template[atx][aty+2])
            return true;
        atx++;
    }
    atx=0;
    if(template[atx][aty]== round && template[atx][aty]==template[atx+1][aty+1] && template[atx+1][aty+1]==template[atx+2][aty+2])
    return true;
    
    if(template[atx+1][aty+1]== round && template[atx+2][aty]==template[atx+1][aty+1] && template[atx+1][aty+1]==template[atx][aty+2])
    return true;
    
    return false;
}
/* 
Moves computer depending on random axis numbers.
Updates the frame and template.
sleep() function is used to give a thinking effect to the computer.
Could be improved :(
*/
void moveComputer(){
    srand(time(NULL));
    int randomx=rand()%3;
    int randomy=rand()%3;
    if(haveSpaces()){
        while (template[randomx][randomy] != ' '){
            randomx=rand()%3;
            randomy=rand()%3;
        }
        template[randomx][randomy] =computer;
        frame[randomx*2][randomy*2]=computer;
        if(isFinished(computer) != true){
            sleep(2);
            system("clear");
            printFrame();
            move();
            return;
        }
        else{
            system("clear");
            printFrame();
            printf("Computer won!\n");
            system("./start");
        }
    }
    else{
        system("clear");
            printFrame();
         printf("Tie!\n");
         system("./start");
    }
}
/*
Takes input from user.
checks the win/Tie situations.
*/
void move(){
    char moveTo[2];
    if (haveSpaces()){
        scanf("%s",moveTo);
        change(moveTo);
        if(isFinished(player) != true){
        system("clear");
        printFrame();
        moveComputer();
        return;
        }
        else{
            system("clear");
            printFrame();
            printf("Player won!\n");
            system("./start");
        }
    }
    else{
        system("clear");
            printFrame();
         printf("Tie!\n");
         system("./start");
    }
}   
/*
Checks the input of the player. Input should obey some rules.
If it did not change() function will print a warning.
Updates the frame depending on the input. 
*/
void change(char *word){
    int x=3;
    int y=3;
    int length=strlen(word);
    if(length == 2){
    switch(word[0]){
        case 'A': 
        case 'a':
        x=0;
        break;
        case 'B':
        case 'b':
        x=1;
        break;
        case 'C':
        case 'c':
        x=2;
        break;
        default: 
        printf("Only A B or C\n");
        scanf("%s",word);
        change(word);
        return;
    }
    switch(word[1]){
        case '1': y=0;
        break;
        case '2': y=1;
        break;
        case '3': y=2;
        break;
        default:         
        printf("Only 1 2 or 3\n");
        scanf("%s",word);
        change(word);
        return;
    }
    if(template[x][y] != ' '){
        printf("That space is full\n");
        scanf("%s",word);
        change(word);
        return;
    }
    else{
    template[x][y]=player;
    frame[x*2][y*2]=player;
    }
    }
    else{
        printf("Ex: A1, B2, C3\n");
        scanf("%s",word);
        change(word);
        return;
    }
}


