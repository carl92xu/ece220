#include "game.h"

/* This file will be used by main.c
 * I wrote make_game, remake_game, get_cell, move_w, move_s, move_a, move_d, legal_move_check
 * I also created slide_up, slide_down, slide_left, slide_right functions to be used by four move functions
 */


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));		// ***** WHAT does it do?
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	mygame->rows = rows;		// assign rows
	mygame->cols = cols;		// assign cols
	
    for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {		// loop through every cell
			mygame->cells[i*cols+j] = -1;	// initialize the cell to -1
		}
	}
	
	int score=0;
	// mygame->score = malloc(sizeof(score));		// allocate memory for score
	mygame->score = score;		// initialize score to 0

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;
	(*_cur_game_ptr)->cols = new_cols;
	
	for (int i=0; i<new_rows; i++) {
		for (int j=0; j<new_cols; j++) {		// loop through every cell
			(*_cur_game_ptr)->cells[i*new_cols+j] = -1;	// initialize the cell to -1
		}
	}
	
	int score=0;
	// (*_cur_game_ptr)->score = malloc(score);		// re-allocate memory for score
	(*_cur_game_ptr)->score = score;		// re-initialize score to 0

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	if ((row<=cur_game->rows) && (col<=cur_game->cols)) {
		return &cur_game->cells[row*(cur_game->cols)+col];		// return the pointer of the cell
	} else return NULL;
}

// ******************************************************************************
// this function will be called by move_w
// this function slides all cells upwards
int slide_up(game * cur_game) {
    int row = cur_game->rows;
    int col = cur_game->cols;
    int moved = 0;
    
    for (int j=0; j<col; j++) {
        // get first empty cell
        int empty;
        for (empty=0; empty<row && cur_game->cells[empty*col+j] != -1; empty++);
        
        for (int i=empty+1; i<row; i++) {
            if (cur_game->cells[i*col+j] != -1) {
                cur_game->cells[empty*col+j] = cur_game->cells[i*col+j];        // shift the cell up
                cur_game->cells[i*col+j] = -1;      // clear the original cell
                empty++;        // increment empty
                moved = 1;
            }
        }
    }
    return moved;		// ***** What does it do actually?
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int moved;

    moved = slide_up(cur_game);     // slide elements up
    
    // combine cells upwards
    int row = cur_game->rows;
    int col = cur_game->cols;
    
    for (int i=0; i<row-1; i++) {
        for (int j=0; j<col; j++) {
            // if the cell isn't empty, and equals the one at its top, combine them
            if (cur_game->cells[i*col+j] == -1) continue;
            if (cur_game->cells[i*col+j] == cur_game->cells[(i+1)*col+j]) {
                cur_game->cells[i*col+j] *= 2;      // double the top
                cur_game->cells[(i+1)*col+j] = -1;      // clear the bottom
                cur_game->score += cur_game->cells[i*col+j];		// update score
                moved = 1;
            }
        }
    }
    
    slide_up(cur_game);     // slide elements up

    return moved;
};


// ******************************************************************************
// this function will be called by move_s
// this function slides all cells downwards
int slide_down(game * cur_game) {
    int row = cur_game->rows;
    int col = cur_game->cols;
    int moved = 0;

    for (int j=0; j<col; j++) {
        // get first empty cell
        int empty;
        for (empty=row-1; empty>=0 && cur_game->cells[empty*col+j] != -1; empty--);
        
        for (int i=empty-1; i>=0; i--) {
            if (cur_game->cells[i*col+j] != -1) {
                cur_game->cells[empty*col+j] = cur_game->cells[i*col+j];        // shift the cell down
                cur_game->cells[i*col+j] = -1;      // clear the original cell
                empty--;        // decrement empty
                moved = 1;
            }
        }
    }
    return moved;
}

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int moved;

    moved = slide_down(cur_game);     // slide elements down

    // combine cells upwards
    int row = cur_game->rows;
    int col = cur_game->cols;
    
    for (int i=row-1; i>0; i++) {
        for (int j=0; j<col; j++) {
            // if the cell isn't empty, and equals the one at its top, combine them
            if (cur_game->cells[i*col+j] == -1) continue;
            if (cur_game->cells[i*col+j] == cur_game->cells[(i-1)*col+j]) {
                cur_game->cells[i*col+j] *= 2;      // double the bottom
                cur_game->cells[(i-1)*col+j] = -1;      // clear the top
                cur_game->score += cur_game->cells[i*col+j];
                moved = 1;
            }
        }
    }
    
    slide_down(cur_game);     // slide elements down

    return moved;
};


// ******************************************************************************
// this function will be called by move_a
// this function slides all cells leftwards
int slide_left(game * cur_game) {
    int row = cur_game->rows;
    int col = cur_game->cols;
    int moved = 0;

    for (int i=0; i<row; i++) {     // loop through rows
        // get first empty cell
        int empty;
        for (empty=0; empty<col && cur_game->cells[i*col+empty] != -1; empty++);
        
        for (int j=empty+1; j<col; j++) {       // loop through columns
            if (cur_game->cells[i*col+j] != -1) {
                cur_game->cells[i*col+empty] = cur_game->cells[i*col+j];        // shift the cell left
                cur_game->cells[i*col+j] = -1;      // clear the original cell
                empty++;        // increment empty
                moved = 1;
            }
        }
    }
    return moved;
}

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int moved;

    moved = slide_left(cur_game);     // slide elements left

    // combine cells upwards
    int row = cur_game->rows;
    int col = cur_game->cols;
    
    // for (int i=0; i<row; i++) {
    for (int j=0; j<col-1; j++) {
        // for (int j=0; j<col-1; j++) {
        for (int i=0; i<row; i++) {
            // if the cell isn't empty, and equals the one at its top, combine them
            if (cur_game->cells[i*col+j] == -1) continue;
            if (cur_game->cells[i*col+j] == cur_game->cells[i*col+(j+1)]) {
                cur_game->cells[i*col+j] *= 2;      // double the left
                cur_game->cells[i*col+(j+1)] = -1;      // clear the right
                cur_game->score += cur_game->cells[i*col+j];
                moved = 1;
            }
        }
    }
    
    slide_left(cur_game);     // slide elements left

    return moved;
};


// ******************************************************************************
// this function will be called by move_d
// this function slides all cells rightwards
int slide_right(game * cur_game) {
    int row = cur_game->rows;
    int col = cur_game->cols;
    int moved = 0;

    for (int i=0; i<row; i++) {     // loop through rows
        // get first empty cell
        int empty;
        for (empty=col-1; empty>=0 && cur_game->cells[i*col+empty] != -1; empty--);
        
        for (int j=empty-1; j>=0; j--) {       // loop through columns
            if (cur_game->cells[i*col+j] != -1) {
                cur_game->cells[i*col+empty] = cur_game->cells[i*col+j];        // shift the cell right
                cur_game->cells[i*col+j] = -1;      // clear the original cell
                empty--;        // decrement empty
                moved = 1;
            }
        }
    }
    return moved;
}

int move_d(game * cur_game)  //slide to the right
{
    //YOUR CODE STARTS HERE
    int moved;

    moved = slide_right(cur_game);     // slide elements right
    
    // combine cells upwards
    int row = cur_game->rows;
    int col = cur_game->cols;
    
    // for (int i=0; i<row; i++) {
    for (int j=col-1; j>0; j--) {
        // for (int j=col-1; j>0; j--) {
        for (int i=0; i<row; i++) {
            // if the cell isn't empty, and equals the one at its left, combine them
            if (cur_game->cells[i*col+j] == -1) continue;
            if (cur_game->cells[i*col+j] == cur_game->cells[i*col+(j-1)]) {
                cur_game->cells[i*col+j] *= 2;      // double the right
                cur_game->cells[i*col+(j-1)] = -1;      // clear the left
                moved = 1;
            }
        }
    }
    
    slide_right(cur_game);     // slide elements right

    return moved;
};


// THIS FUNCTION BELOW IS NOT USED
// ******************************************************************************
// this function will be called by legal_move_check
// it compares if the two game are the same
/* int compare_game(game * game1, game * game2) {
	int rows = game1->rows;		// assign rows
	int cols = game1->cols;		// assign cols
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {		// loop through every cell
			if (game1->cells[i*cols+j] != game2->cells[i*cols+j]) {
				return 0;		// if they are not the same, return 0
			}
		}
	}
	return 1;		// if they are the same, return 1
}
*/

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	int rows = cur_game->rows;		// assign rows
	int cols = cur_game->cols;		// assign cols
	
	// check if the board is full
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {		// loop through every cell
			if (cur_game->cells[i*cols+j] == -1) return 1;		// if a cell is empty, return 1
		}
	}

	// THIS PART BELOW IS NOT USED
	// create a copy of game
	/* game * game_copy = malloc(sizeof(game));
	game_copy->cells = malloc(rows*cols*sizeof(cell));
	
	// copy rows and cols
	game_copy->rows = cur_game->rows;
	game_copy->cols = cur_game->cols;
	
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {		// loop through every cell
			game_copy->cells[i*cols+j] = cur_game->cells[i*cols+j];		// assign each cell to the copy accordingly
		}
	}
	
	game_copy->score = cur_game->score;		// copy score
	
	// check for 4 moves
	move_w(game_copy);		// check move_w
	if (!compare_game(cur_game, game_copy)) return 0;		// if anything changed, return 0
	move_s(game_copy);		// check move_s
	if (!compare_game(cur_game, game_copy)) return 0;		// if anything changed, return 0
	move_a(game_copy);		// check move_a
	if (!compare_game(cur_game, game_copy)) return 0;		// if anything changed, return 0
	move_d(game_copy);		// check move_d
	if (!compare_game(cur_game, game_copy)) return 0;		// if anything changed, return 0
	*/

	// check if four move functions change any cell's value
	if (!move_w(cur_game)) return 0;		// if no cell's value changed, return 0
	if (!move_s(cur_game)) return 0;                // if no cell's value changed, return 0
	if (!move_a(cur_game)) return 0;                // if no cell's value changed, return 0
	if (!move_d(cur_game)) return 0;                // if no cell's value changed, return 0
	
	// if none of the previous conditions matches and returns 0, then it means there are legal moves and return 1
	return 1;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
