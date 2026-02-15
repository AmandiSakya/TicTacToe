//USER VS USER and USER VS COMPUTER withouth the logfile
#include <stdio.h>
#include <string.h>  //for strlen()
#include <stdlib.h>  //for rand()
#include <time.h>    //for srand()

//Define an empty cell
#define EMPTY ' '

void Title() {
    char text[] = "Tic Tac Toe";
    int line_width = 50;
    int len = strlen(text);                 
    int space = (line_width - len) / 2;     

    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%s\n\n", text);
}


void Board(char board[10][10], int N) {
    // Print column headers
    printf("   ");                          //prints 3 blank spaces before the colomn numbers start
    for (int col = 0; col < N; col++) {
        printf("%6d ", col);
    }  
    printf("\n");

    int HL_width = N * 7 + 1;               // horizontal line width
    printf("  "); 
    for (int i = 0; i < HL_width; i++) {
        printf("_");
    }
    printf("\n");

    // Print rows with separators
    for (int row = 0; row < N; row++) {
        printf("%3d |", row);
        for (int col = 0; col < N; col++) {
            printf("  %c   |", board[row][col]);
        }
        printf("\n");
        printf("  ");
        for (int i = 0; i < HL_width; i++) {
            printf("_");
        }
        printf("\n");
    }
}

void drawBoard(char board[10][10],int N){
    Board(board,N);
}

int checkWinner(char board[10][10], int N, char symbol) {
    int i, j;

    // Check rows
    for (i = 0; i < N; i++) {
        int count = 0;
        for (j = 0; j < N; j++) {
            if (board[i][j] == symbol) count++;
        }
        if (count == N) 
        return 1;
    }

    // Check columns
    for (j = 0; j < N; j++) {
        int count = 0;
        for (i = 0; i < N; i++) {
            if (board[i][j] == symbol) 
            count++;
        }
        if (count == N) 
        return 1;
    }

    // Check main diagonal
    int count = 0;
    for (i = 0; i < N; i++) {
        if (board[i][i] == symbol) 
        count++;
    }
    if (count == N) 
    return 1;

    // Check anti-diagonal
    count = 0;
    for (i = 0; i < N; i++) {
        if (board[i][N - 1 - i] == symbol) 
        count++;
    }
    if (count == N) 
    return 1;

    return 0;
}

int moveValid(char board[10][10], int size, int row, int col){
    return(row >= 0 && row < size && col >= 0 && col < size &&board[row][col] == EMPTY);
}

//Conditions for Compuer moves
int ComWinConditions(char board[10][10], int N, int *lastrow, int *lastcol) {
    int i, j;

    //1.Check if computer can win
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            if(board[row][col] == ' '){
                board[row][col] = 'O';
                if(checkWinner(board,N,'O')){
                    board[row][col] = ' ';
                    *lastrow = row;
                    *lastcol = col;
                    return 1;
                }
                board[row][col] = ' ';
            }
        }
    }

    //2.Block player if they are about to win
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            if(board[row][col] == ' '){
                board[row][col] = 'X';
                if(checkWinner(board, N, 'X')){
                    board[row][col] = ' ';
                    *lastrow = row;
                    *lastcol = col;
                    return 1;
                }
                board[row][col] = ' ';
            }
        }
    }

    //3.Use the center cell if available
    if (board[N/2][N/2] == ' ') {
        board[N/2][N/2] = 'O';
        return 1;
    }

    //4.else choose a random move
    while(1){
        int rand_row = rand() % N;
        int rand_col = rand() % N;
        if(moveValid(board, N,rand_row, rand_col)){
            *lastrow = rand_row;
            *lastcol = rand_col;
            return 1;
        }
    }

    //if not, pick the first empty cell
    return 0;
}

//Computer move
void computerMove(char board[10][10], int N){
    int row, col;
    
    if(ComWinConditions(board, N, &row, &col)){
        board[row][col] = 'O';
        printf("Computer placed at %d %d\n",row, col);
    }
}

int main() {
    Title();
    srand(time(NULL));

    int N;
    int num;

    printf("Select the game mode:\n 1.two Players(User ves User)\n 2.User vs Computer\n 3.Three Player\n\n");
    printf("Enter choice(1-3): ");
    scanf("%d",&num);

    if(num < 1 || num > 3){
        printf("==Invalid Game Mode==\n");
        return 0;
    }

    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &N);

    if (N < 3 || N > 10) {
        printf("==Invalid size!==\n");
        return 0;
    }

    char board[10][10];
    int i, j;

    // Initialize board
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            board[i][j] = EMPTY;
        }
    }

    int moves = 0, maxMoves = N * N;
    //current player
    char currPlayer = 'X';       

    while (moves < maxMoves) {
        Board(board, N);
        
        int row, col;

        if(num == 1 || currPlayer == 'X'){
        //user move
        printf("Player %c, enter row and column(row col): ", currPlayer);
        scanf("%d %d", &row, &col);

        //If the player picks a spot where someone already used, then board[row][col] != EMPTY will be true
        if (row < 0 || row >= N || col < 0 || col >= N || board[row][col] != EMPTY) {
            printf("Invalid move, try again.\n");
            continue;
        }

        board[row][col] = currPlayer;
        }else{
        computerMove(board, N);
        }

        //check winner immidiately after the move
        if (checkWinner(board, N, currPlayer)) {
            drawBoard(board, N);
            printf("Player %c wins!\n", currPlayer);
            break;
        }

        moves++;

        if (currPlayer == 'X'){
            currPlayer = 'O';
        }
        else{
            currPlayer = 'X';
        }

        if (moves == maxMoves) {
            Board(board, N);
            printf("The Game is a draw!\n");
            break;
        }
    }

    return 0;
}