/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * Introduction:
 * This file contains several functions used by main.c, and they are defined in prog5.h.
 * I completed the three functions asked in course wiki, set_seed, start_game, make_guess.
 * I wrote them in the way the wiki asked for, and tested them, they should all work fine.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};

int seed;
int score;

/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
    char post[2];

    // return invalid if not only 1 int is entered
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
        printf("set_seed: invalid seed\n");
        return 0;
    }
    // initize random number generator here
    srand(seed);
    return 1;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    guess_number = 1;
    max_score = -1;
    int rand_num;

    // generate solution array here
    for (int i=0; i<4; i++) {
        rand_num = rand() % 8;
        strcpy(solutions[i], pool[rand_num]);	// assign random str from pool to solutions
    }
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
    char check_str[4][10], post[2];

    // check if exactly 4 str has been entered
    if (sscanf(guess_str, "%s%s%s%s%1s", check_str[0], check_str[1], check_str[2], check_str[3], post) != 4) {
        printf("make_guess: invalid guess\n");
        return 0;
    }

    int perfect_match = 0;
    int misplaced_match = 0;
    int checked = 0;
    int marked_solution[4] = {-1,-1,-1,-1};
    int marked_check[4] = {-1,-1,-1,-1};
    score = 0;

    // loop through each of the 4 guess strings
    for (int i=0; i<4; i++) {
        if (is_valid(check_str[i])) {	// when the str is valid
		
	    if (strcmp(check_str[i], solutions[i]) == 0) {	// check if it matches
                perfect_match += 1;
                score += 1000;
		// mark this check_str as marked
		for (int k=0; k<4; k++) {
                    if (marked_check[k] == -1) {
                        marked_check[k] = i;
		    break;
                    }
                }
                // mark this solution as marked
                for (int k=0; k<4; k++) {
                    if (marked_solution[k] == -1) {
                        marked_solution[k] = i;
		    break;
                    }
                }
            }
        } else {	// when a guess string is invalid
            printf("make_guess: invalid guess\n");
            return 0;
        }
    }
	    
    for (int i=0; i<4; i++) {
	checked = 0;
	// check if this check_str has already been marked
	for (int k=0; k<4; k++) {
            if (i == marked_check[k]) {
                checked = 1;
                break;
            }
        }
	if (checked) continue;
        // loop through each of the 4 solution strings
        for (int j=0; j<4; j++) {
            if (strcmp(check_str[i], solutions[j]) == 0) {
                checked = 0;
                // check if this solution has already been marked
                for (int k=0; k<4; k++) {
                    if (j == marked_solution[k]) {
                        checked = 1;
                        break;
                    }
                }
                if (checked) continue;

                misplaced_match += 1;
                score += 100;
	        // mark this solution as marked
                for (int k=0; k<4; k++) {
                    if (marked_solution[k] == -1) {
                        marked_solution[k] = j;
                        break;
                    }
                }
            }
        }
    }

    if (score > max_score) max_score = score;	// adjust max_score
    // print result
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\nYour score is %d and current max score is %d.\n", guess_number, perfect_match, misplaced_match, score, max_score);
    guess_number += 1;          // increment guess counter
    // return values
    if (perfect_match == 4) return 2;
    else return 1;
}
