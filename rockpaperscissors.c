#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int movePlayer();
int moveComputer();
void calculateScore(int playr,int comp);

struct players
{
    int score;

}player,computer;

int main(void){
    system("clear");
    player.score=0;
    computer.score=0;
    while(computer.score != 3 && player.score != 3){
        printf("Scores:\nPlayer: %i Computer: %i\n",player.score,computer.score);
        printf("Select one:\n1-Rock\n2-Paper\n3-Scissors\n");
        calculateScore(movePlayer(),moveComputer());
    }
    printf("Scores:\nPlayer: %i Computer: %i\n",player.score,computer.score);
    if(player.score == 3){
            printf("Player won!\n");
            system("./start");
            return 0;
    }
    printf("Computer Won!\n");
    system("./start");
    return 0;
}
/*
Gets input  from the player and prints rock paper or scissors according to the input.
*/
int movePlayer(){
    int selected=0;
    scanf("%d",&selected);
    system("clear");
    switch(selected){
        case 1:
        printf("Rock is selected.\n");
        printf("    _______\n---'   ____)\n      (_____)\n      (_____)\n      (____)\n---.__(___)\n");
        return 0;
        case 2:
        printf("Paper is selected.\n");
        printf("    _______\n---'   ____)____\n          ______)\n          _______)\n         _______)\n---.__________)\n");
        return 1;
        case 3:
        printf("Scissors is selected.\n");
        printf("    _______\n---'   ____)____\n          ______)\n       __________)\n      (____)\n---.__(___)\n");
        return 2;
        default: 
        printf("Select 1(Rock) 2(Paper) or 3(Scissors)\n");
        break;
    }
    return movePlayer();
}
/* 
Moves the computer according to a random component 
sleep() function is used to give a thinking effect
*/
int moveComputer(){
    srand(time(NULL));
    int chose=rand()%3;
    sleep(3);
    switch(chose){
        case 0:
        printf("Computer selected Rock\n");
        printf("      _______\n     (____   ‘---\n    (_____)\n    (_____)\n     (____)\n      (___)__.---\n");
        return 0;
        case 1:
        printf("Computer Selected Paper\n");
        printf("        _______\n   ____(____   ‘---\n  (_____\n (______\n  (____ \n    (___________.---\n");
        return 1;
        case 2:
        printf("Computer Selected Scissors\n");
        printf("         _______\n    ____(____   ‘---\n   (______\n   (______\n       (____)\n        (___)___.---\n");
        return 2;
    }
    return moveComputer();
}

/* 
Takes the moves (R P OR S) of both player and computer
 and adds 1 to the side who won. outputs "Tie!" if both picked the same.
*/
void calculateScore(int playr,int comp){
    int cmpScore=computer.score;
    if(playr == comp){
        printf("Tie!\n");
        return;
    }
    switch(playr){
        case 0:
        computer.score=(comp == 1)? computer.score+1:computer.score;
        break;
        case 1:
        computer.score=(comp == 2)? computer.score+1:computer.score;
        break;
        case 2:
        computer.score=(comp == 0)? computer.score+1:computer.score;
        break;
    }
    player.score=(computer.score == cmpScore)? player.score+1:player.score;   
}

