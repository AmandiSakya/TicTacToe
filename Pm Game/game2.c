//user vs user code with the log file

#include <stdio.h>
#include <string.h>	//for strlen()
#define EMPTY ' '

FILE *logFile;   //pointer for logfile

void Title(){
	char text[] = "Tic Tac Toe";
	int line_width = 50;
	int len = strlen(text);
	int space = (line_width - len) / 2;

	for(int i = 0; i < space; i++){
		printf(" ");
	}
	printf("%s\n\n",text);
}

void initializeBoard(char board[10][10], int N){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			board[i][j] = EMPTY;
		}
	}
}

void DispBoard(char board[10][10], int N){
	//Print colomn headers
	//prints 3 blank spaces before the colomn numbers start
	printf("   ");			
	for(int col = 0; col < N; col++){
		printf("%6d", col);
	}
	printf("\n");

	//horizontal line width
	int HL_width = N * 7 +1;	
	printf("  ");
	for(int i = 0; i < HL_width; i++){
		printf("_");
	}
	printf("\n");

	//Print rows with seperators
	for(int row =0; row < N; row++){
		printf("%3d |", row);
		for(int col = 0; col < N; col++){
			printf("  %c   |",board[row][col]);
		}
		printf("\n");
		printf("  ");
		for(int i = 0; i < HL_width; i++){
			printf("_");
		}
		printf("\n");
	}
}

// same display also logged into file
void drawBoard(char board[10][10], int N){

	// writing data to the logfile
	//This data does not immediately go into the physical file on disk.
	//Instead, it first goes into a buffer in memory
	fprintf(logFile, "\nCurrent Board:\n");

	for(int row = 0; row < N; row++){
		for(int col = 0; col < N; col++){
			fprintf(logFile, "%c ", board[row][col]);
		}
		fprintf(logFile, "\n");
	}
	fprintf(logFile, "----------------------\n");
	
	//forces the buffer to be write immediately to the file
	//Which means data currently in memory is actually written to disk
	fflush(logFile);  
}

int checkWinner(char board[10][10], int N, char symbol){
	int i, j;

	//check rows
	for(i = 0; i <  N; i++){
		int count = 0;
		for(j = 0; j < N; j++){
			if(board[i][j] == symbol)
				count++;
		}
		if(count == N)
			return 1;
	}

	//check colomns
	for(j = 0; j < N; j++){
		int count = 0;
		for (i = 0; i < N; i++){
			if(board[i][j] == symbol)
			count++;
		}
			if(count == N)
			return 1;
	}

	//check diagonal
	int count = 0;
	for(i = 0; i < N; i++){
		if(board[i][i] == symbol)
		count++;
	}
	if(count == N)
	return 1;

	//check antidiagonal
	count = 0;
	for(i = 0; i < N; i++){
		if(board[i][N-1-i] == symbol)
		count++;
	}
	if (count == N)
	return 1;

	return 0;
}

int main(){
	Title();

	//open logfile
	logFile = fopen("tictactoe2_logfile.txt", "w");
	if(logFile == NULL){
		printf("Could not open log file.\n");
		return 1;
	}

	int N;
	
	printf("Enter board size N(3<=N<=10): ");
	scanf("%d",&N);
	fprintf(logFile, "Selected the Board Size %d", &N);
	fflush(logFile);

	if(N < 3|| N > 10){
		printf("==Invalid size!==\n");
		fprintf(logFile, "Invalid Board Size");
		fflush(logFile); 
		return 0;
	}

	char board[10][10];
	initializeBoard(board, N);

	int moves = 0, maxMoves = N*N;
	char currPlayer = 'X';

	while(moves < maxMoves){
		DispBoard(board, N);

		int row, col;
		printf("Player %c, enter row and colomn(row col): ",currPlayer);
		scanf("%d %d",&row, &col);

		//if the player picks a spot where someone already used
		if(row < 0 || row >= N || col < 0 || col >= N ||board[row][col] != EMPTY){
			printf("==INVALID MOVE. TRY AGAIN==\n");
			fprintf(logFile, "Invalid move by Player %c\n", currPlayer);
			fflush(logFile); 
			continue;
		}

		board[row][col] = currPlayer;
		// log the move by current player
		fprintf(logFile, "Player %c drew move (%d,%d)\n", currPlayer, row, col);
		//Didn't use fflush becoz the drawBoard() will flush anyway
		moves++;

		//Board to be display after placing a move by a player
		drawBoard(board, N);

		if(checkWinner(board, N, currPlayer)){
			drawBoard(board, N);
			printf("==PLAYER %c WON!==\n", currPlayer);
			fprintf(logFile, "PLAYER %c WON!\n", currPlayer);
			fflush(logFile);
			break;
		}

		if(currPlayer == 'X'){
			currPlayer = 'O';}
		else{
			currPlayer = 'X';
		}

		if (moves == maxMoves){
			DispBoard(board, N);
			printf("==THE GAME IS A DRAW!==\n");
			fprintf(logFile, "THE GAME IS A DRAW!\n");
			fflush(logFile);
			break;
		}
	}

	fclose(logFile);
	return 0;
}
