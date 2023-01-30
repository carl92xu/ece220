#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include <string.h>


/* This file is called by main.c
 * I wrote 4 functions: createMaze, destoryMaze, printMaze, solveMazeDFS
 * createMaze allocates memory for the maze, and copy char from file into a 2D array
 * destoryMaze free up all memory used by the baze
 * printMaze would print the maze in an human understandable way
 * solveMazwDFS is recursive, and it would get a solution to the maze, or determine if it's solvable
 */


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
	int row, col;

	FILE *file_ptr = fopen(fileName, "r");	// open the maze file for read
	fscanf(file_ptr, "%d %d", &row, &col);	// get row and col numbers from file
	
	maze_t *maze = (maze_t *) malloc(sizeof(maze_t));	// allocate memory for maze
	maze->width = col;	// assign attributes of maze
	maze->height = row;

	char** new_double_ptr = (char **) malloc(row*sizeof(char*));	// alloce memory for cells pointer
	maze->cells = new_double_ptr;

	int i;
	for (i=0; i<row; i++) {
		char *new_cell_row = (char *) malloc(col*sizeof(char));	// allocate memory for every row
		maze->cells[i] = new_cell_row;

		int j;
		for (j=0; j<col; j++) {
			fscanf(file_ptr, "%c", &maze->cells[i][j]);	// read a character from the file and assign to a cell in the 2D array
			// deal with '\n'
			if (maze->cells[i][j]=='\n') {
				fscanf(file_ptr, "%c", &maze->cells[i][j]);      // read a character to replace '\n'
			}
			// set startRow etc.
			if (maze->cells[i][j]==START) {	// start position
				maze->startRow = i;
				maze->startColumn = j;
			}
			if (maze->cells[i][j]==END) {	// end position
				maze->endRow = i;
				maze->endColumn = j;
			}
		}
	}
	
	fclose(file_ptr);	// close file
	return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	int row = maze->width;
	
	int i;
	for (i=0; i<row; i++) {
		free(maze->cells[i]);	// free up every row first
	}
	free(maze->cells);	// free up row pointers
	free(maze);	// free up the maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
	int row = maze->height;
	int col = maze->width;

	int i;	
	for (i=0; i<row; i++){
		int j;
		for (j=0; j<col; j++){	// loop through every cell
			printf("%c", maze->cells[i][j]);	// print cell
		}
		printf("\n");	// print new line at the end of each row
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
	// Base Cases
	if ((row>=maze->height)||(row<0)||(col>=maze->width)||(col<0)) return 0;	// If (col, row) outside bounds of the maze return false
	if (maze->cells[row][col]==END) return 1;       // if (col, row) is the end of the maze return true
	if (maze->cells[row][col]!=EMPTY && maze->cells[row][col]!=START) return 0;	// if (col, row) is not an empty cell return false
	//if (maze->cells[row][col]==END) return 1;	// if (col, row) is the end of the maze return true
	
	// Recursive Part
	if (maze->cells[row][col]!=START) {
		maze->cells[row][col] = PATH;	// set (col, row) as part of the solution path in the maze
	}

	if (maze->cells[row][col-1]!=START && solveMazeDFS(maze, col-1, row)) return 1;	// if (solveMaze(left of (col, row) ) == true) return true
	if (maze->cells[row][col+1]!=START && solveMazeDFS(maze, col+1, row)) return 1;	// if (solveMaze(right of (col, row) ) == true) return true
	if (maze->cells[row-1][col]!=START && solveMazeDFS(maze, col, row-1)) return 1;	// if (solveMaze(up of (col, row) ) == true) return true
	if (maze->cells[row+1][col]!=START && solveMazeDFS(maze, col, row+1)) return 1;	// if (solveMaze(down of (col, row) ) == true) return true

	if (maze->cells[row][col]!=START) {	
		maze->cells[row][col] = VISITED;	// unmark (col, row) as part of solution and mark as visited
	}
    return 0;
}
