#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_hangman(char *hangman[5][5]);
void check_hangman(int wrong, char *hangman[5][5]);
void refresh_word(char *input, char *word, char *guess);
void print_word(char *word);
void give_hint(char *word, char *input, int *hints);
bool contains_str(char *input, char *guess);
int generate_hint_count(char *input);
bool check_answer(char *answer,char *input);
bool check_input(char *input);
void print_evocation();
#define LENGTH 50
int main()
{
    system("clear");
    char *hangman[5][5] = {
        {" ", " ", " ", " ", " "}, {" ", " ", " ", " ", " "}, {" ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " "}, {" ", " ", " ", " ", " "},
    };
    char input[LENGTH]={ 0 };
    char *guess = malloc(2);
    if (guess == NULL)
    {
        return 1;
    }
    int wrong = 0;
    printf("Welcome to Hangman! Write the word your that friends have to find out!\nWrite '?' to take a clue and write 'word' if you found out what the word was!\nBe careful as you will lose if you don't answer correctly\n");
    fputs("Picked word: ",stdout);
    fgets(input, sizeof input, stdin);
    while(check_input(input)){
    print_evocation();
    fputs("Picked word: ",stdout);
    fgets(input, sizeof input, stdin);
    }
    int length = strlen(input);
    int hints=generate_hint_count(input);
    char word[length];
    word[length]='\0';
    system("clear");

    for (int i = 0; i < length; i++)
        word[i] = '_';
    print_word(word);
    while (strchr(word, '_') != NULL)
    {
        printf("Take a guess! Write a letter!\n");
        do
        {
            scanf("%s", guess);
            int lengthGuess = strlen(guess);
            char s = guess[0];
            int result=strcmp(guess,"word\0");
            if (( result != 0 && lengthGuess != 1) || ((s < 65 || s > 90) && (s < 97 || s > 122) && (s != 63)))
                printf("Write a letter not a word or a punctuation nor a numberrrrrr!!\n");
            else if(strstr(word,guess) != NULL)
                printf("You already wrote this letter\n");
            else
                break;
        }
        while (true);
        system("clear");
        if(guess[0] == '?'){
            give_hint(word,input,&hints);
            print_word(word);
            if (wrong != 0 && strchr(word, '_') != NULL)
                print_hangman(hangman);
        }
        else if(strcmp(guess,"word") == 0){
            char answer[LENGTH];
            char c;
            printf("What do you think the word is?\n");
            scanf("%c", &c);
            fgets(answer,sizeof(answer),stdin);
            int lenAnswer=strlen(answer)-1;
            answer[lenAnswer]='\0';
            if(!check_answer(answer,input)){
                printf("Well.. Wrooooong You lost!\n");
                printf("Word you were looking for was: %s\n",input);
                return 0;
            }
            break;
        }
        else if (contains_str(input,guess))
        {
            refresh_word(input, word, guess);
            printf("Correct!\n");
            print_word(word);
            if (wrong != 0 && strchr(word, '_') != NULL)
                print_hangman(hangman);
        }
        else
        {
            wrong++;
            check_hangman(wrong, hangman);
            printf("Wrong guess\n");
            print_hangman(hangman);
            if(wrong<9){
            print_word(word);
            }
            else{
             printf("You lost\n");
             printf("Word you were looking for was: %s\n",input);
             system("./start");
            free(guess);
             return 0;
            }
        }
    }

    printf("( ＾◡＾)っ ♡ \n");
    printf("Congratulations!\n");
    system("./start");
    free(guess);
    return 0;
}
/*
Prints hangman as it is.
*/
void print_hangman(char *hangman[5][5])
{
    for (int k = 0; k < 5; k++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%s", hangman[k][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/*
Removes parts depending on the incorrect answers user gave.
*/
void check_hangman(int wrong, char *hangman[5][5])
{
    switch (wrong)
    {
        case 1:
            hangman[1][0] = "|";
            hangman[2][0] = "|";
            hangman[3][0] = "|";
            hangman[4][0] = "|";
            break;
        case 2:
            hangman[0][4] = "_";
            hangman[0][3] = "_";
            hangman[0][2] = "_";
            hangman[0][1] = "_";
            hangman[0][0] = "_";
            break;
        case 3:
            hangman[1][3] = "|";
            break;
        case 4:
            hangman[2][3] = "O";
            break;
        case 5:
            hangman[3][3] = "|";
            break;
        case 6:
            hangman[3][2] = "/";
            break;
        case 7:
            hangman[3][4] = "\\";
            break;
        case 8:
            hangman[4][2] = "/";
            break;
        case 9:
            hangman[4][4] = "\\";
            break;
    }
}
/*
Updates the word depending on the guess. If the guess is'nt in input this function won't change anything.
*/
void refresh_word(char *input, char *word, char *guess)
{
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (input[i] == guess[0] || input[i] + 32 == guess[0] || input[i] - 32 == guess[0])
        {
            word[i] = input[i];
        }
    }
}
/*
Prints word as it is.
*/
void print_word(char *word){
    int length=strlen(word);
    for(int i=0;i<length && word[i] != '\0';i++)
       printf("%c ",word[i]);
    printf("\n\n");
}
/*
Checkes if input contains guess.
*/
bool contains_str(char *input, char *guess){
    if (strchr(input, guess[0]) == NULL && (strchr(input,(guess[0] + 32)) == NULL && strchr(input, guess[0] -32) == NULL))
        return false;
    return true;
}
/*
Gives hint if there are hints left, if not informs the user that there are none left
*/
void give_hint(char *word, char *input,int *hints){
    int length=strlen(word);
    time_t t;
    srand((unsigned) time(&t));
    if(*hints == 0){
        printf("No hints Left!\n");
        return;
    }
    int random=rand() % length;
    while(word[random] != '_'){
        random=rand() % length;
    }
    word[random] = input[random];
    *hints += -1;
    printf("You used an hint! You now have %i hints left\n",*hints);

}
/*
Gives the hint count of an input depending on its length.
*/
int generate_hint_count(char *input){

    int length=strlen(input);
    int count;
    if(length>=15)
        count=3;
    else if(length >=10)
        count=2;
    else
        count=1;
    return count;
}
/*
Checks the answer of user after user typed 'word' as guess input.
*/
bool check_answer(char *answer,char *input){
    int length=strlen(input);
    int count=0;
    int answerLen=strlen(answer);
    if(answerLen==length){
    for(int i=0;i<length;i++){
        if(answer[i] == input[i] || answer[i] == input[i]+32 || answer[i] == input[i]-32)
        count++;
      }
    }
    else
    return false;
    if(count == length)
        return true;
    return false;
}
/*
Checks the input variable. If it's allowed returns false else it will return true
*/
bool check_input(char *input){
    int length=strlen(input)-1;
    if(length > 45)
        return true;
    char s=' ';
    for(int i=0;i<length;i++){
        s=input[i];
        if((s < 65 || s > 90) && (s < 97 || s > 122)){
            return true;
        }
    }
    input[length]='\0';
    return false;
}
void print_evocation(){
    system("clear");
    printf("Remember:\n1)You can't write a word more than 45 chars long\n");
    printf("2)You should'nt write a sentence,no punctuation or spaces included\n3)Only english chars are allowed\n");
}