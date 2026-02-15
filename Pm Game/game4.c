//FINAL GAME USER VS USER without the log file
#include <stdio.h>
#include <string.h>     //for "strlen()"

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
    //prints 3 blank spaces before the colomn numbers start
    printf("   ");                          
    for (int col = 0; col < N; col++) {
        printf("%6d ", col);
    }  
    printf("\n");

    // horizontal line width
    int HL_width = N * 7 + 1;               
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

int main() {
    Title();
    
    int N;

    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &N);

    if (N < 3 || N > 10) {
        printf("Invalid size!!!\n");
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
    char currPlayer = 'O';       

    while (moves < maxMoves) {
        Board(board, N);

        int row, col;
        printf("Player %c, enter row and column(row col): ", currPlayer);
        scanf("%d %d", &row, &col);

        //If the player picks a spot where someone already used, then board[row][col] != EMPTY will be true
        if (row < 0 || row >= N || col < 0 || col >= N || board[row][col] != EMPTY) {
            printf("Invalid move, try again.\n");
            continue;
        }

        board[row][col] = currPlayer;
        moves++;

         if (currPlayer == 'O'){
            currPlayer = 'X';
        }
        else{
            currPlayer = 'O';
        }

        if (checkWinner(board, N, currPlayer)) {
            drawBoard(board, N);
            printf("Player %c wins!\n", currPlayer);
            break;
        }

        if (moves == maxMoves) {
            Board(board, N);
            printf("The Game is a draw!\n");
            break;
        }
    }
    FILE *logfile;
    logfile = fopen("application.log", "a+");

    if (logfile == NULL){
        perror("Error opening log file");
        return 1;
    }

    fprintf(logfile, "This is a log message.\n");
    fprintf(logfile, "Another log entry at a later time.\n");

    fclose(logfile);
    printf("Log messages written to application.log\n");

    return 0;
}




//com  winning conds by myself
if (board[N/2][N/2] == ' ') {
        board[N/2][N/2] = 'O';
        return 1;
    }

    //Block user's winning move
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == ' '){
                board[i][j] = 'X';
                if (checkWinner(board, N, 'X')){
                    board[i][j] = ' ';
                    return 1;
                }
                board[i][j] = ' ';
            }
        }
    }

    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            int nr = lastXrow + dr;
            int nc = lastXcol + dc;
            if (nr >= 0 && nr < N && nc >= 0 && nc < N && board[nr][nc] == EMPTY) {
                *r = nr;
                *c = nc;
                return 1;
            }
        }
    }