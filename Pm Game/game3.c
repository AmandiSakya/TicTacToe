//GAME WITH THE LOG FILE
#include <stdio.h>
#include <string.h>

#define EMPTY ' '

// ---------- Function Prototypes ----------
void Title();
void initializeBoard(char board[10][10], int N);
void displayBoard(char board[10][10], int N);
void logBoard(FILE *logfile, char board[10][10], int N, int moveNum, char player);
void getUserMove(int *row, int *col, int N);
int isValidMove(char board[10][10], int N, int row, int col);
int checkWinner(char board[10][10], int N, char symbol);
int isDraw(int moves, int maxMoves);

// ---------- Functions ----------

// Print centered title
void Title() {
    char text[] = "Tic Tac Toe";
    int line_width = 50;
    int len = strlen(text);
    int space = (line_width - len) / 2;

    for (int i = 0; i < space; i++) printf(" ");
    printf("%s\n\n", text);
}

// Initialize board with EMPTY cells
void initializeBoard(char board[10][10], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Display current board state
void displayBoard(char board[10][10], int N) {
    printf("     ");
    for (int col = 0; col < N; col++) {
        printf("%6d ", col);
    }
    printf("\n");

    int HL_width = N * 7 + 1;
    printf("  ");
    for (int i = 0; i < HL_width; i++) printf("_");
    printf("\n");

    for (int row = 0; row < N; row++) {
        printf("%3d |", row);
        for (int col = 0; col < N; col++) {
            printf("  %c   |", board[row][col]);
        }
        printf("\n");

        printf("  ");
        for (int i = 0; i < HL_width; i++) printf("_");
        printf("\n");
    }
}

// Log the board state to a file
void logBoard(FILE *logfile, char board[10][10], int N, int moveNum, char player) {
    fprintf(logfile, "\nMove %d by Player %c:\n", moveNum, player);

    // Log board similar to display
    fprintf(logfile, "     ");
    for (int col = 0; col < N; col++) {
        fprintf(logfile, "%6d ", col);
    }
    fprintf(logfile, "\n");

    int HL_width = N * 7 + 1;
    fprintf(logfile, "  ");
    for (int i = 0; i < HL_width; i++) fprintf(logfile, "_");
    fprintf(logfile, "\n");

    for (int row = 0; row < N; row++) {
        fprintf(logfile, "%3d |", row);
        for (int col = 0; col < N; col++) {
            fprintf(logfile, "  %c   |", board[row][col]);
        }
        fprintf(logfile, "\n");

        fprintf(logfile, "  ");
        for (int i = 0; i < HL_width; i++) fprintf(logfile, "_");
        fprintf(logfile, "\n");
    }
}

// Get user move input
void getUserMove(int *row, int *col, int N) {
    printf("Enter row and column (row col): ");
    scanf("%d %d", row, col);
}

// Check if move is valid
int isValidMove(char board[10][10], int N, int row, int col) {
    if (row < 0 || row >= N || col < 0 || col >= N) return 0;   // Out of bounds
    if (board[row][col] != EMPTY) return 0;                     // Cell already used
    return 1;
}

// Check winner conditions
int checkWinner(char board[10][10], int N, char symbol) {
    int i, j;

    // Check rows
    for (i = 0; i < N; i++) {
        int count = 0;
        for (j = 0; j < N; j++) if (board[i][j] == symbol) count++;
        if (count == N) return 1;
    }

    // Check columns
    for (j = 0; j < N; j++) {
        int count = 0;
        for (i = 0; i < N; i++) if (board[i][j] == symbol) count++;
        if (count == N) return 1;
    }

    // Check main diagonal
    int count = 0;
    for (i = 0; i < N; i++) if (board[i][i] == symbol) count++;
    if (count == N) return 1;

    // Check anti-diagonal
    count = 0;
    for (i = 0; i < N; i++) if (board[i][N - 1 - i] == symbol) count++;
    if (count == N) return 1;

    return 0;
}

// Check for draw
int isDraw(int moves, int maxMoves) {
    return moves == maxMoves;
}

// ---------- Main Function ----------
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
    initializeBoard(board, N);

    int moves = 0, maxMoves = N * N;
    char currentPlayer = 'O';

    // Open log file
    FILE *logfile = fopen("application.log", "a+");
    if (logfile == NULL) {
        perror("Error opening log file");
        return 1;
    }
    fprintf(logfile, "=== New Game Started: Board size %dx%d ===\n", N, N);

    // Game loop
    while (1) {
        displayBoard(board, N);

        int row, col;
        getUserMove(&row, &col, N);

        // Validate move
        if (!isValidMove(board, N, row, col)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make move
        board[row][col] = currentPlayer;
        moves++;

        // Log move and board state
        logBoard(logfile, board, N, moves, currentPlayer);

        // Check win
        if (checkWinner(board, N, currentPlayer)) {
            displayBoard(board, N);
            printf("Player %c wins!\n", currentPlayer);
            fprintf(logfile, "Player %c wins!\n", currentPlayer);
            break;
        }

        // Check draw
        if (isDraw(moves, maxMoves)) {
            displayBoard(board, N);
            printf("The game is a draw!\n");
            fprintf(logfile, "The game is a draw!\n");
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'O') ? 'X' : 'O';
    }

    fprintf(logfile, "=== Game Ended ===\n\n");
    fclose(logfile);
    printf("Game log saved to application.log\n");

    return 0;
}
