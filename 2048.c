// 2048.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>



#define MAX_SIZE 4
#define OVER 0
#define NOT_OVER 1

#define FG_RED     "\x1b[31m"
#define FG_GREEN   "\x1b[32m"
#define FG_YELLOW  "\x1b[33m"
#define FG_BLUE    "\x1b[34m"
#define FG_MAGENTA "\x1b[35m"
#define FG_CYAN    "\x1b[36m"
#define FG_RESET   "\x1b[0m"

#define BG_RESET "\e[m"
#define BG_RED "\e[41m"
#define BG_GREEN "\e[42m"
#define BG_YELLOW "\e[43m"
#define BG_BLUE "\e[44m"
#define BG_PINK "\e[45m"
#define BG_CYAN "\e[46m"
#define BG_GREY "\e[100m"
#define BG_SKY_BLUE "\e[104m"


typedef struct _game *Game;

typedef struct _game {
	int board[MAX_SIZE][MAX_SIZE];
	int turnNum;
} game;

void drawBoard (Game g);
Game newGame ();
void newTile (Game g);
void decideMove (Game g);
void rotateClockwise (Game g);
int gameState (Game g);
void makeMove (Game g);
int turn (Game g);

int main(int argc, char *argv[]) {
	system("clear");
	
	Game g = newGame();

	printf("~~~ 2048 ~~~\n\n");
	printf("How To Play: use W,A,S,D to move tiles, when equal tiles touch they merge!\n\n");

	srand(time(NULL));

	//starting two tiles
	newTile(g);
	newTile(g);
	drawBoard(g);
	printf("Score: %d\n", 10 * turn (g) );

	while (gameState(g) == NOT_OVER) {
		
		decideMove(g);

		system("clear");

		printf("~~~ 2048 ~~~\n\n");
		printf("How To Play: use W,A,S,D to move tiles, when equal tiles touch they merge!\n\n");

		newTile(g);
		drawBoard(g);
		printf("Score: %d\n", 10 * turn (g) );
	}

	printf("Game Over\n");

	return EXIT_SUCCESS;
}

int gameState(Game g) {
	int state = OVER;

	int x = 0;
	int y = 0;
	while (y < MAX_SIZE) {
		x = 0;
		while (x < MAX_SIZE) {
			if (g->board[x][y] == 0) {
				state = NOT_OVER;
			}

			x++;
		}
		y++;
	}

	return state;
}

int turn (Game g) {
	return g->turnNum;
}

void drawBoard (Game g) {
	int x = 0;
	int y = 0;
	printf(BG_GREY"-----------------\n"BG_RESET);
	while (y < MAX_SIZE) {
		x = 0;
		while (x < MAX_SIZE) {
			if (g->board[x][y] == 0) {
				printf(BG_GREY"|   "BG_RESET);
			} else if (g->board[x][y] >= 10 && g->board[x][y] < 100 ) {
				if (g->board[x][y] == 16) {
					printf(BG_GREY"|"BG_RESET BG_BLUE" %d"BG_RESET, g->board[x][y]);
				} else if (g->board[x][y] == 32) {
					printf(BG_GREY"|"BG_RESET BG_PINK" %d"BG_RESET, g->board[x][y]);
				} else if (g->board[x][y] == 64) {
					printf(BG_GREY"|"BG_RESET BG_CYAN" %d"BG_RESET, g->board[x][y]);
				}
			} else if (g->board[x][y] >= 100) {
				printf(BG_GREY"|"BG_RESET BG_SKY_BLUE"%d"BG_RESET, g->board[x][y]);
			} else {
				if (g->board[x][y] == 2) {
					printf(BG_GREY"|"BG_RESET BG_RED" %d "BG_RESET, g->board[x][y]);
				} else if (g->board[x][y] == 4) {
					printf(BG_GREY"|"BG_RESET BG_GREEN" %d "BG_RESET, g->board[x][y]);
				} else if (g->board[x][y] == 8) {
					printf(BG_GREY"|"BG_RESET BG_YELLOW" %d "BG_RESET, g->board[x][y]);
				}
			}
			x++;
		}
		y++;
		printf(BG_GREY"|\n"BG_RESET);
		printf(BG_GREY"-----------------\n"BG_RESET);
	}
}

Game newGame (void) {
	Game g = malloc(sizeof(struct _game));

	g->turnNum = -2;

	int x = 0;
	int y = 0;
	while (y < MAX_SIZE) {
		x = 0;
		while (x < MAX_SIZE) {
			g->board[x][y] = 0;
			x++;
		}
		y++;
	}
	return g;
}

void newTile (Game g) {
	int x;
	int y;

	x = rand()% 4;
	y = rand()% 4;

	while (g->board[x][y] != 0) {
		x = rand()% 4;
		y = rand()% 4;
	}

	int decide = rand() % 11;

	if (decide >= 0 && decide <= 8) {
		g->board[x][y] = 2;
	} else {
		g->board[x][y] = 4;
	}

	g->turnNum++;
}

void decideMove (Game g) {
	char move;
	scanf(" %c",&move);

	if (move == 'a') {
		makeMove (g);

	} else if (move == 'w') {
		// rotate once
		rotateClockwise (g);
		rotateClockwise (g);
		rotateClockwise (g);
		// do move
		makeMove (g);
		// rotate back
		rotateClockwise (g);

	} else if (move == 'd') {
		// rotate twice
		rotateClockwise (g);
		rotateClockwise (g);

		// do move
		makeMove (g);
		// rotate back

		rotateClockwise (g);
		rotateClockwise (g);

	} else if (move == 's') {
		// rotate thrice
		rotateClockwise (g);

		// do move
		makeMove (g);
		// rotate back
		rotateClockwise (g);
		rotateClockwise (g);
		rotateClockwise (g);

	} else {
		printf("Not a valid move!\n");
		decideMove(g);
	}

}

void makeMove (Game g) {
	int y = 0;
	while (y < MAX_SIZE) {

		// hard coded for individual cases, but breaks down, therefore there is quite a bit of repeatition 
		
		// ones:

		//? 0 0 0 
		// nothing

		//0 ? 0 0
		if ( g->board[0][y] == 0 && g->board[1][y] != 0 && g->board[2][y] == 0 && g->board[3][y] == 0 ) {

			g->board[0][y] = g->board[1][y];
			g->board[1][y] = 0;
			
		}

		//0 0 ? 0
		else if ( g->board[0][y] == 0 && g->board[1][y] == 0 && g->board[2][y] != 0 && g->board[3][y] == 0 ) {

			g->board[0][y] = g->board[2][y];
			g->board[2][y] = 0;
			
		}
		
		//0 0 0 ? 
		else if ( g->board[0][y] == 0 && g->board[1][y] == 0 && g->board[2][y] == 0 && g->board[3][y] != 0 ) {

			g->board[0][y] = g->board[3][y];
			g->board[3][y] = 0;
			
		}

		// twos
		// ? ? 0 0
		else if ( g->board[0][y] != 0 && g->board[1][y] != 0 && g->board[2][y] == 0 && g->board[3][y] == 0 ) {

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = 0;
			
			}
		}
		//0 0 ? ?
		else if ( g->board[0][y] == 0 && g->board[1][y] == 0 && g->board[2][y] != 0 && g->board[3][y] != 0 ) {

			g->board[0][y] = g->board[2][y];
			g->board[1][y] = g->board[3][y];

			g->board[2][y] = 0;
			g->board[3][y] = 0;

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = 0;
			
			}
		}
		//0 ? ? 0
		else if ( g->board[0][y] == 0 && g->board[1][y] != 0 && g->board[2][y] != 0 && g->board[3][y] == 0 ) {

			g->board[0][y] = g->board[1][y];
			g->board[1][y] = g->board[2][y];

			g->board[2][y] = 0;

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = 0;
			
			}
		}
		//? 0 0 ?
		else if ( g->board[0][y] != 0 && g->board[1][y] == 0 && g->board[2][y] == 0 && g->board[3][y] != 0 ) {

			g->board[1][y] = g->board[3][y];

			g->board[3][y] = 0;

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = 0;
			
			}
		}
		//? 0 ? 0
		else if ( g->board[0][y] != 0 && g->board[1][y] == 0 && g->board[2][y] != 0 && g->board[3][y] == 0 ) {

			g->board[1][y] = g->board[2][y];

			g->board[2][y] = 0;

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = 0;
			
			}
		}
		//0 ? 0 ?
		else if ( g->board[0][y] == 0 && g->board[1][y] != 0 && g->board[2][y] == 0 && g->board[3][y] != 0 ) {

			g->board[0][y] = g->board[1][y];
			g->board[1][y] = g->board[3][y];

			g->board[3][y] = 0;

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = 0;
			
			}
		}

		// threes:

		// ? ? ? 0
		else if ( g->board[0][y] != 0 && g->board[1][y] != 0 && g->board[2][y] != 0 && g->board[3][y] == 0 ) {

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = g->board[2][y];
				g->board[2][y] = 0;
			
			} else if (g->board[1][y] == g->board[2][y]) {
				
				g->board[1][y] = g->board[1][y] * 2;
				g->board[2][y] = 0;
			
			}
		}
		//0 ? ? ?
		else if ( g->board[0][y] == 0 && g->board[1][y] != 0 && g->board[2][y] != 0 && g->board[3][y] != 0 ) {

			g->board[0][y] = g->board[1][y];
			g->board[1][y] = g->board[2][y];
			g->board[2][y] = g->board[3][y];

			g->board[3][y] = 0;

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = g->board[2][y];
				g->board[2][y] = 0;
			
			} else if (g->board[1][y] == g->board[2][y]) {
				
				g->board[1][y] = g->board[1][y] * 2;
				g->board[2][y] = 0;
			
			}
		}
		//? 0 ? ?
		else if ( g->board[0][y] != 0 && g->board[1][y] == 0 && g->board[2][y] != 0 && g->board[3][y] != 0 ) {

			g->board[1][y] = g->board[2][y];
			g->board[2][y] = g->board[3][y];

			g->board[3][y] = 0;


			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = g->board[2][y];
				g->board[2][y] = 0;
			
			} else if (g->board[1][y] == g->board[2][y]) {
				
				g->board[1][y] = g->board[1][y] * 2;
				g->board[2][y] = 0;
			
			}
		}
		//? ? 0 ?
		else if ( g->board[0][y] != 0 && g->board[1][y] != 0 && g->board[2][y] == 0 && g->board[3][y] != 0 ) {

			g->board[2][y] = g->board[3][y];

			g->board[3][y] = 0;

			if (g->board[0][y] == g->board[1][y]) {
				
				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = g->board[2][y];
				g->board[2][y] = 0;

			} else if (g->board[1][y] == g->board[2][y]) {
				
				g->board[1][y] = g->board[1][y] * 2;
				g->board[2][y] = 0;
			
			}
		}

		// fours:
		// ? ? ? ?
		else if ( g->board[0][y] != 0 && g->board[1][y] != 0 && g->board[2][y] != 0 && g->board[3][y] != 0 ) {
			
			//all equal
			if ( g->board[0][y] == g->board[1][y] && g->board[1][y] == g->board[2][y] 
					&& g->board[2][y] == g->board[3][y] ) {

				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = g->board[2][y] * 2;
				
				g->board[2][y] = 0;
				g->board[3][y] = 0;
			} 
			// 2 2 4 4
			else if ( g->board[0][y] == g->board[1][y] && g->board[2][y] == g->board[3][y] 
					&& g->board[1][y] != g->board[2][y] ) {

				g->board[0][y] = g->board[0][y] * 2;
				g->board[1][y] = g->board[2][y] * 2;
				
				g->board[2][y] = 0;
				g->board[3][y] = 0;
			} 
			// 2 2 2 4
			else if ( g->board[0][y] == g->board[1][y] && g->board[1][y] == g->board[2][y] 
					&& g->board[2][y] != g->board[3][y] ) {

				g->board[0][y] = g->board[0][y] * 2;
				
				g->board[1][y] = g->board[2][y];
				g->board[2][y] = g->board[3][y];
				g->board[3][y] = 0;
			} 
			// 4 2 2 2  
			else if ( g->board[0][y] != g->board[1][y] && g->board[1][y] == g->board[2][y] 
					&& g->board[2][y] == g->board[3][y] ) {

				g->board[1][y] = g->board[1][y] * 2;
				
				g->board[2][y] = g->board[3][y];
				g->board[3][y] = 0;
			}
			// 2 4 4 2  
			else if ( g->board[0][y] != g->board[1][y] && g->board[1][y] == g->board[2][y] 
					&& g->board[2][y] != g->board[3][y] ) {

				g->board[1][y] = g->board[1][y] * 2;
				
				g->board[2][y] = g->board[3][y];
				g->board[3][y] = 0;
			}

			else {

				// 2 2 4 8
				if (g->board[0][y] == g->board[1][y]) {
					
					g->board[0][y] = g->board[0][y] * 2;
					g->board[1][y] = g->board[2][y];
					g->board[2][y] = g->board[3][y];
					g->board[3][y] = 0;
				
				} 
				// 4 2 2 4
				else if (g->board[1][y] == g->board[2][y]) {
					
					g->board[1][y] = g->board[1][y] * 2;
					g->board[2][y] = g->board[3][y];
					g->board[3][y] = 0;

				} 
				// 4 4 2 2
				else if (g->board[2][y] == g->board[3][y]) {

					g->board[2][y] = g->board[2][y] * 2;
					g->board[3][y] = 0;

				}
			}
		} 

		else {

		}
		y++;
	}
}

void rotateClockwise (Game g) {
	int tempBoard[MAX_SIZE][MAX_SIZE] = {0};

	int x = 0;
	int y = 0;
	while (y < MAX_SIZE) {
		x = 0;
		while (x < MAX_SIZE) {
			tempBoard[x][y] = g->board[y][MAX_SIZE-1-x];
			x++;
		}
		y++;
	} 
	/*
	printf("Rotated:\n");
	x = 0;
	y = 0;
	while (y < MAX_SIZE) {
		x = 0;
		while (x < MAX_SIZE) {
			printf("%d ", tempBoard[x][y]);
			x++;
		}
		y++;
		printf("\n");
	}*/


	x = 0;
	y = 0;
	while (y < MAX_SIZE) {
		x = 0;
		while (x < MAX_SIZE) {
			g->board[x][y] = tempBoard[x][y];
			x++;
		}
		y++;
	}
}