#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpace();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main() {
    char response;
    do {
        char winner = ' ';
        resetBoard();
        while (winner == ' ' && checkFreeSpace() != 0){
            printBoard();
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpace() == 0){
                break;
            }
            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpace() == 0){
                break;
            }

        }
        printBoard();
        printWinner(winner);
        printf("\nAgain? (Y/N):");
        scanf("%c");
        scanf("%c",&response);
        response = toupper(response);

    } while(response == 'Y');
    printf("See you.");
    return 0;
}

void resetBoard(){
    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard(){
    printf(" %c | %c | %c ", board[0][0],board[0][1],board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0],board[1][1],board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0],board[2][1],board[2][2]);
    printf("\n");
}

int checkFreeSpace(){
    int freeSpace = 9;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if (board[i][j] != ' '){
                freeSpace--;
            }
        }
    }
    return freeSpace;
}

void playerMove(){
    int x,y;
    do{
        printf("Enter row number (1-3): ");
        scanf("%d",&x);
        printf("Enter column number (1-3): ");
        scanf("%d",&y);
        if(board[y-1][x-1] != ' '){
            printf("Invalid move!");
        } else {
            board[y-1][x-1] = PLAYER;
            break;
        }
    } while (board[y-1][x-1] != ' ');


}

void computerMove(){
    srand(time(0));
    int x,y;
    if (checkFreeSpace()>0){
        do {
            x=rand()%3;
            y=rand()%3;
        } while (board[y][x]!=' ');
        board[y][x]=COMPUTER;
    } else{
        printWinner(' ');
    }
}

char checkWinner(){
    for(int i=0; i<3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }
    for(int j=0; j<3; j++){
        if(board[0][j] == board[1][j] && board[0][j] == board[2][j]){
            return board[0][j];
        }
    }

    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }
    return ' ';
}

void printWinner(char winner){
    if (winner == PLAYER){
        printf("You Win!");
    } else if (winner == COMPUTER){
        printf("You Lose...");
    } else {
        printf("Tied.");
    }
}