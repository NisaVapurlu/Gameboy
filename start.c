#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

void toLower(char *word);
void direct();
bool inGames();

char *games[3]={"hangman","xox","rockpaperscissors"};
char game[50]={ 0 };

int main(void){
    printf("Welcome to good old Gameboy 2.0!\n");
    printf("Write the game you want to play!\n");
    while(inGames() == false)
    printf("There is no such a game as: %s\n",game);
    direct();
    return 0;
}

void toLower(char *word){
    int length=strlen(word);
    for(int i=0;i<length;i++){
        word[i]=tolower(word[i]);
    }
}
bool inGames(){
    scanf("%s",game);
    int length=strlen(game);
    toLower(game);
    for(int i=0;i<sizeof games/sizeof games[0] ;i++)
        if(strcmp(games[i],game) == 0){
            game[length]='\0';
            return true;
        }
    return false;
}
void direct(){
    char word[53]={ 0 };
    word[0]='.';
    word[1]='/';
    int length=strlen(game);
    for(int i=0;i<length && game[i] != '\0';i++){
        word[i+2]=game[i];
    }
    system(word);
}

