//Multiplayer Final with the log file
#include <stdio.h>   //for printf(),scanf(),fprintf
#include <string.h>  //for strings(Z,X,O)
#include <stdlib.h>  //for rand()
#include <time.h>    //for srand()

//Define an empty cell
#define EMPTY ' '

FILE *logFile;

//Initializing and Displaying the Game Board
void Board(char board[10][10], int N) {
    // Print column headers
    //prints 3 blank spaces before the colomn numbers start
    printf("   ");
    for (int col = 0; col < N; col++) printf("%6d ", col);
    printf("\n");

    // horizontal line width
    int HL_width = N * 7 + 1;
    printf("  ");
    for (int i = 0; i < HL_width; i++) printf("_");
    printf("\n");

    // Print rows with separators
    for (int row = 0; row < N; row++) {
        printf("%3d |", row);
        for (int col = 0; col < N; col++) {
            printf("  %c   |", board[row][col]);
        }
        printf("\n  ");
        for (int i = 0; i < HL_width; i++) printf("_");
        printf("\n");
    }
}

//starting the logfile
void drawBoard(char board[10][10],int N){
    fprintf(logFile, "\nCurrent Board:\n");
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            fprintf(logFile, "%c ", board[row][col]);
        }
        fprintf(logFile, "\n");
    }
    fprintf(logFile, "----------------------\n");
    fflush(logFile);
}

// Checking Win Conditions
int checkWinner(char board[10][10], int N, char symbol) {
    int i, j;

    // Check rows
    for (i = 0; i < N; i++) {
        int count = 0;
        for (j = 0; j < N; j++)
            if (board[i][j] == symbol) count++;
        if (count == N) return 1;
    }

    // Check columns
    for (j = 0; j < N; j++) {
        int count = 0;
        for (i = 0; i < N; i++)
            if (board[i][j] == symbol) count++;
        if (count == N) return 1;
    }

    // Check main diagonal
    int count = 0;
    for (i = 0; i < N; i++)
        if (board[i][i] == symbol) count++;
    if (count == N) return 1;

    // Check anti-diagonal
    count = 0;
    for (i = 0; i < N; i++)
        if (board[i][N - 1 - i] == symbol) count++;
    if (count == N) return 1;

    return 0;
}

//check whether it's a valid move (Validating user inputs)
int ValidMove(char board[10][10], int size, int row, int col) {
    return (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == EMPTY);
}

//Conditions for Computer moves
void computerMove(char board[10][10], int N, char symbol) {
    int row, col;

    //1.Use the center cell if available
    if (board[N/2][N/2] == EMPTY) {
        board[N/2][N/2] = symbol;
        printf("Computer %c placed at row %d and colomn %d\n", symbol, N/2, N/2);
        fprintf(logFile, "Computer %c placed at row %d and colomn %d\n", symbol, N/2, N/2);
        return;
    }

    //2.else choose a random computer move
    while (1) {
        row = rand() % N;
        col = rand() % N;
        if (ValidMove(board, N, row, col)) {
            board[row][col] = symbol;
            printf("Computer %c placed at row %d and colomn %d\n", symbol, row, col);
            fprintf(logFile, "Computer %c placed at row %d and colomn %d\n", symbol, row, col);
            return;
        }
    }
    fflush(logFile);
}

int main() {
    logFile = fopen("tictactoe4_logfile.txt", "w");
    if(logFile == NULL){
        printf("Could not open log file.\n");
        return 1;
    }
    
    printf(":::::::::::TIC TAC TOE::::::::::\n\n");
    fprintf(logFile, ":::::::::::TIC TAC TOE::::::::::\n\n");
    fflush(logFile);

    srand(time(NULL));

    int N, num;
    printf("Select the game mode:\n 1.Two Players(User vs User)\n 2.User vs Computer\n 3.Three Players\n\n");
    printf("Enter choice(1-3): ");
    scanf("%d", &num);
    fprintf(logFile, "Selected Game Mode %d\n", num);
    fflush(logFile);

    if (num < 1 || num > 3) {
        printf("==Invalid Game Mode==\n");
        fprintf(logFile, "==Invalide Game Mode==\n");
        fflush(logFile);
        return 0;
    }

    char sign[3] = {'X','O','Z'};

    //marks whether each player is a computer or not
    //human -> 0 , com -> 1
    int Computer[3] = {0,0,0}; 
    int totalPlayers;

    if(num == 3) {
        totalPlayers = 3;
    }
    else{totalPlayers = 2;}

     // for user vs computer
    if (num == 2) {
        Computer[1] = 1; 
    }

    //Choosing a sign for multiplePlayer choice
    if (num == 3) {
        int multiChoice;
        printf("\nSelect Multiplayer Type:\n");
        printf("1. Two Users + Computer\n");
        printf("2. One User + Two Computers\n");
        printf("3. Three Users\n");
        scanf("%d", &multiChoice);
        fprintf(logFile, "Selected the Multiplayer Type %d.\n", multiChoice);
        fflush(logFile);

        if (multiChoice == 1) {
            Computer[2] = 1; 
        } else if (multiChoice == 2) {
            Computer[1] = 1;
            Computer[2] = 1;
        } 
    }

    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &N);
    fprintf(logFile, "Selected board size %d\n\n", N);
    if (N < 3 || N > 10) {
        printf("==Invalid size!==\n");
        fprintf(logFile, "==Invalide Size!==\n");
        fflush(logFile);
        return 0;
    }

    // Initialize board
    char board[10][10];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = EMPTY;
    fprintf(logFile, "Game board initialized.\n");
    fflush(logFile);

    //To check for a draw
    int moves = 0, maxMoves = N * N;

    //currPlayerIndex = 0 -> curr player is using 'X' symbol
    //currPlayerIndex = 1 -> curr player is using 'O' symbol
    //currPlayerIndex = 2 -> curr player is using 'Z' symbol
    int currPlayerIndex = 0;

    while (moves < maxMoves) {
        Board(board, N);
        char currSymbol = sign[currPlayerIndex];

        printf("\nPlayer %d's turn (%c)\n", currPlayerIndex + 1, currSymbol);
        fprintf(logFile, "Player %d's turn (%c)\n", currPlayerIndex + 1, currSymbol);
        fflush(logFile);

        if (Computer[currPlayerIndex]) {
            computerMove(board, N, currSymbol);
        } else {
            int row, col;
            
            //Accepting user inputs
            printf("Player %c, enter row and column (row col): ", currSymbol);
            scanf("%d %d", &row, &col);
            fprintf(logFile, "Player %c, entered the row %d and column %d\n", currSymbol, row, col);
            fflush(logFile); 

            if (!ValidMove(board, N, row, col)) {
                printf("==Invalid Move, Try Again==\n");
                fprintf(logFile, "==Invalid Move, Try Again==");
                fflush(logFile); 
                continue;
            }
            board[row][col] = currSymbol;
	    drawBoard(board, N);
        }

        if (checkWinner(board, N, currSymbol)) {
            Board(board, N);
            printf("== PLAYER %c WON! ==\n", currSymbol);
            fprintf(logFile, "== PLAYER %c WON! ==\n", currSymbol);
            fflush(logFile); 
            return 0;
        }

        moves++;
        currPlayerIndex = (currPlayerIndex + 1) % totalPlayers;
    }

    if (moves == maxMoves){
    Board(board, N);
    printf("== THE GAME IS A DRAW! ==\n");
    fprintf(logFile, "== THE GAME IS A DRAW! ==\n");
    }

    fclose(logFile);
    return 0;
}





//Multiplayer Final without log file
#include <stdio.h>   //for printf
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

    for (int i = 0; i < space; i++) printf(" ");
    printf("%s\n\n", text);
}

void Board(char board[10][10], int N) {
    // Print column headers
    //prints 3 blank spaces before the colomn numbers start
    printf("   ");
    for (int col = 0; col < N; col++) printf("%6d ", col);
    printf("\n");

    // horizontal line width
    int HL_width = N * 7 + 1;
    printf("  ");
    for (int i = 0; i < HL_width; i++) printf("_");
    printf("\n");

    // Print rows with separators
    for (int row = 0; row < N; row++) {
        printf("%3d |", row);
        for (int col = 0; col < N; col++) {
            printf("  %c   |", board[row][col]);
        }
        printf("\n  ");
        for (int i = 0; i < HL_width; i++) printf("_");
        printf("\n");
    }
}

// Winner Conditions
int checkWinner(char board[10][10], int N, char symbol) {
    int i, j;

    // Check rows
    for (i = 0; i < N; i++) {
        int count = 0;
        for (j = 0; j < N; j++)
            if (board[i][j] == symbol) count++;
        if (count == N) return 1;
    }

    // Check columns
    for (j = 0; j < N; j++) {
        int count = 0;
        for (i = 0; i < N; i++)
            if (board[i][j] == symbol) count++;
        if (count == N) return 1;
    }

    // Check main diagonal
    int count = 0;
    for (i = 0; i < N; i++)
        if (board[i][i] == symbol) count++;
    if (count == N) return 1;

    // Check anti-diagonal
    count = 0;
    for (i = 0; i < N; i++)
        if (board[i][N - 1 - i] == symbol) count++;
    if (count == N) return 1;

    return 0;
}

//check whether it's a valid move
int ValidMove(char board[10][10], int size, int row, int col) {
    return (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == EMPTY);
}

//Conditions for Compuer moves
void computerMove(char board[10][10], int N, char symbol) {
    int row, col;

    //1.Use the center cell if available
    if (board[N/2][N/2] == EMPTY) {
        board[N/2][N/2] = symbol;
        printf("Computer %c placed at %d %d\n", symbol, N/2, N/2);
        return;
    }

    //2.else choose a random move
    while (1) {
        row = rand() % N;
        col = rand() % N;
        if (ValidMove(board, N, row, col)) {
            board[row][col] = symbol;
            printf("Computer %c placed at %d %d\n", symbol, row, col);
            return;
        }
    }
}

int main() {
    Title();
    srand(time(NULL));

    int N, num;
    printf("Select the game mode:\n 1.Two Players(User vs User)\n 2.User vs Computer\n 3.Three Players\n\n");
    printf("Enter choice(1-3): ");
    scanf("%d", &num);

    if (num < 1 || num > 3) {
        printf("==Invalid Game Mode==\n");
        return 0;
    }

    char sign[3] = {'X','O','Z'};

    //marks whether each player is a computer or not
    //human -> 0 , com -> 1
    int Computer[3] = {0,0,0}; 
    int totalPlayers;

    if(num == 3) {
        totalPlayers = 3;
    }
    else{totalPlayers = 2;}

     // for user vs computer
    if (num == 2) {
        Computer[1] = 1; 
    }

    //Choosing a sign for multiplePlayer choice
    if (num == 3) {
        int multiChoice;
        printf("\nSelect Multiplayer Type:\n");
        printf("1. Two Users + Computer\n");
        printf("2. One User + Two Computers\n");
        printf("3. Three Users\n");
        scanf("%d", &multiChoice);

        if (multiChoice == 1) {
            Computer[2] = 1; 
        } else if (multiChoice == 2) {
            Computer[1] = 1;
            Computer[2] = 1;
        } 
    }

    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &N);
    if (N < 3 || N > 10) {
        printf("==Invalid size!==\n");
        return 0;
    }

    // Initialize board
    char board[10][10];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = EMPTY;

    int moves = 0, maxMoves = N * N;
    int currPlayerIndex = 0;
    //currPlayerIndex = 0 -> current player is using 'X'
    //currPlayerIndex = 1 -> current player is using 'O'
    //currPlayerIndex = 2 -> current player is using 'Z'

    while (moves < maxMoves) {
        Board(board, N);
        char currSymbol = sign[currPlayerIndex];

        if (Computer[currPlayerIndex]) {
            computerMove(board, N, currSymbol);
        } else {
            int row, col;
            printf("Player %c, enter row and column (row col): ", currSymbol);
            scanf("%d %d", &row, &col);
            if (!ValidMove(board, N, row, col)) {
                printf("==Invalid move, try again==\n");
                continue;
            }
            board[row][col] = currSymbol;
        }

        if (checkWinner(board, N, currSymbol)) {
            Board(board, N);
            printf("== PLAYER %c WON! ==\n", currSymbol);
            return 0;
        }

        moves++;
        currPlayerIndex = (currPlayerIndex + 1) % totalPlayers;
    }

    Board(board, N);
    printf("== THE GAME IS A DRAW! ==\n");
    return 0;
}
