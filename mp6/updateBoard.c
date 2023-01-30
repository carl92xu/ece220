/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	// follow the instructions on the wiki
	int live_neighbor = 0;
	for (int i=row-1; i<=row+1; i++) {				// loop through every row
		if ((i>=0) && (i<boardRowSize)) {			// check if within the boundary
			for (int j=col-1; j<=col+1; j++) {		// loop through every column
				if ((j>=0) && (j<boardColSize)) {	// check if within the boundary
					if ((i!=row) || (j!=col)) {	// check if it's the cell itself
						// increment live neighbor counter if a neighbot is alive
						if (board[i*boardColSize+j]) live_neighbor++;
					}
				}
			}
		}
	}
	return live_neighbor;	// return the number of live neighbor
}


/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int live_neighbor = 0;
	int boardSize = boardRowSize*boardColSize;
        int boardCopy[boardSize];
	// deep copy the board
	/* for (int i=0; i<boardSize; i++) {
                boardCopy[i] = board[i];
        } */

	// loop through every row
	for (int i=0; i<boardRowSize; i++) {
		// loop through every column
		for (int j=0; j<boardColSize; j++) {
			live_neighbor = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);

			if (board[i*boardColSize+j] == 1) {	// if the cell is alive
				if ((live_neighbor<2) || (live_neighbor>3)) {   // check if a cell turns dead
                                	boardCopy[i*boardColSize+j] = 0;
                        	} else {
					boardCopy[i*boardColSize+j] = 1;
				}
			} else { 
				if (live_neighbor==3) {  // check if a dead cell turns back alive
                                	boardCopy[i*boardColSize+j] = 1;
                        	} else {
					boardCopy[i*boardColSize+j] = board[i*boardColSize+j];
				}
			}

			// update the status of this cell
			/* if ((live_neighbor<2) || (live_neighbor>3)) {	// check if a cell turns dead
				boardCopy[i*boardColSize+j] = 0;
			} else if ((!board[i*boardColSize+j]) && (live_neighbor==3)) {	// check if a dead cell turns back alive
				boardCopy[i*boardColSize+j] = 1;
			} else if ((live_neighbor==3) || (live_neighbor==2)) {
				continue;
			} */
		}
	}

	// copy content back to the original board
	for (int i=0; i<boardSize; i++) {
                board[i] = boardCopy[i];
        }
}


/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int boardSize = boardRowSize*boardColSize;
	int boardCopy[boardSize];
	// deep copy the board
	for (int i=0; i<boardSize; i++) {
		boardCopy[i] = board[i];
	}
	// update the board
	updateBoard(board, boardRowSize, boardColSize);
    	// check if they are the same
	for (int i=0; i<boardSize; i++) {
		if (board[i] != boardCopy[i]) return 0;
	}
	return 1;
}

				
				
			

