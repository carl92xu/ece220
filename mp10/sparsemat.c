#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * This file contains functions load_tuples, gv_tuples, set_tuples, save_tuples, add_tuples, destroy_tuples.
 * They will be called by main.c.
 * set_tuples also has two helper functions, insert_sorted, and delete_node.
 */

sp_tuples *load_tuples(char* input_file) {
	int total_row, total_col;
	FILE *file_ptr = fopen(input_file, "r");	// open the file to read
	fscanf(file_ptr, "%d %d", &total_row, &total_col);	// get row and col numbers from file
	
	sp_tuples *my_tuple = (sp_tuples *) malloc(sizeof(sp_tuples));  // allocate memory for my_tuple
	// assign row and columns to my_tuple
	my_tuple->m = total_row;
	my_tuple->n = total_col;
	
	my_tuple->tuples_head = NULL;	// initialize tuples_head
	my_tuple->nz = 0;	// initialize nz

	int row, col;
	double value;
	while (fscanf(file_ptr, "%d %d %lf", &row, &col, &value) == 3) { // while EOF not reached, get row, col, value, for the node from file
		set_tuples(my_tuple, row, col, value);
	}
	
	fclose(file_ptr);   //close file
	return my_tuple;	// return the tuple's pointer
}



double gv_tuples(sp_tuples * mat_t,int row,int col) {
	sp_tuples_node **head = &mat_t->tuples_head;	// for the sack of simplicity
	
	while (*head) { // loop thorugh the linked list
		if (((*head)->row == row) && ((*head)->col == col)) { // if found the node
			return (*head)->value; // return the value
		}
		head = &((*head)->next);	// move on to the next node's pointer
	}
	
	return 0;	// return 0 if the node is not found
}



// implement insert_sorted, and delete_node helper functions
/*
 * inset_sorted funciton will insert a node in the position sorted according to row and col
 * assume row and col will be in bound
 */
void insert_sorted(sp_tuples * mat_t, sp_tuples_node ** head, int row, int col, double value) {	// modification needed
	// sp_tuples_node *head = mat_t->tuples_head;	// for the sack of simplicity
	int total_col = mat_t->n;

	// if I dont have a list yet
	if (!*head) {
		// allocate memory first
		sp_tuples_node *tmp = malloc(sizeof(sp_tuples_node));
		// assign attributes in the node
		tmp->row = row;
		tmp->col = col;
		tmp->value = value;
		
		// adjust the pointers
		tmp->next = *head;
		*head = tmp;
		
		mat_t->nz++;	// increment nz
	}
	// if the position to insert is at head
	else if (row*total_col+col < ((*head)->row)*total_col+(*head)->col) {
		sp_tuples_node *tmp = malloc(sizeof(sp_tuples_node));	// assign memory for the node
		
		// assign attributes in the node
		tmp->row = row;
		tmp->col = col;
		tmp->value = value;
		
		// adjust the pointers
		tmp->next = *head;
		*head = tmp;
		
		mat_t->nz++;	// increment nz
	} else {	// if the position to insert is not at head
		while (*head && (((*head)->row)*total_col+(*head)->col < row*total_col+col)){  // check if it's the end and check the coordinate position
			head = &((*head)->next);	// move on to the next node's pointer
		}
		
		if (*head && (((*head)->row)*total_col+(*head)->col == row*total_col+col)) {	// if need to replace a node
			(*head)->value = value;
		} else {	// insert a node
			sp_tuples_node *tmp = malloc(sizeof(sp_tuples_node));	// assign memory for the node
			// assign attributes in the node
			tmp->row = row;
			tmp->col = col;
			tmp->value = value;

			// adjust the pointers
			tmp->next = *head;
			*head = tmp;

			// if (((*head)->row)*total_col+(*head)->col != row*total_col+col)	// if the node doesn't already exsist
			mat_t->nz++;	// increment nz
		}
	}
}


// delete_node function deletes a node specified by arguemnts row and col
void delete_node(sp_tuples * mat_t, sp_tuples_node ** head, int row, int col) {
	// sp_tuples_node *head = mat_t->tuples_head;	// for the sack of simplicity
	// int total_col = mat_t->n;
	
	// if (!head) return;	// if the tuple is empty, exit
	
	// if head need to be deleted
	if (((*head)->row == row) && ((*head)->col == col)) {
		mat_t->tuples_head = (*head)->next;
		free(head);
		mat_t->nz--;
	}
	else {
		// need to find the one before it, hence check head-next
		while ((*head)->next && ((((*head)->next->row) != row) || (((*head)->next->col) != col))) {	
		//while ((*head)->next && (((*head)->row)*total_col+(*head)->col < row*total_col+col)) {	// check if it's the end and check if it's the coordinate
			head = &((*head)->next);	// move on to the next node's pointer
		}

		// if the coordinate is found
		if ((*head)->next && (((*head)->next->row) == row) && (((*head)->next->col) == col)) {	// if the coordinate is found
			sp_tuples_node *tmp;
			tmp = (*head)->next;	// get the node that needs to be deleted
			*head = tmp->next;	// adjust pointer
			free(tmp);	// free up the memory space of the node deleted
			mat_t->nz--;	// decrement nz
		}
		// if the node is the tail
		else if (((*head)->row == row) && ((*head)->col == col)) {	
			sp_tuples_node *tmp;
			tmp = *head;	// get the node that needs to be deleted
			*head = NULL;	// adjust pointer
			free(tmp);	// free up the memory space of the node deleted
			mat_t->nz--;	// decrement nz
		}
	}
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value) {
	if (value) {	// if value is not 0
		insert_sorted(mat_t, &mat_t->tuples_head, row, col, value);  // insert the node
	} else {	// if value is 0
		 delete_node(mat_t, &mat_t->tuples_head, row, col);   // delete the node
	}
}



void save_tuples(char * file_name, sp_tuples * mat_t) {
	FILE *file_ptr = fopen(file_name, "w");	// open the file to write
	fprintf(file_ptr, "%d %d\n", mat_t->m, mat_t->n);	// write dimensions of the matrix to the file
	
	sp_tuples_node **head = &mat_t->tuples_head;	// for the sake of simplicity
	
	while (*head) {	// loop through every node in the tuple
		fprintf(file_ptr, "%d %d %lf\n", (*head)->row, (*head)->col, (*head)->value);	// write every node into the file in a new line
		head = &((*head)->next);	// move on to the next node's pointer
	}
	
	fclose(file_ptr);   //close file
}



sp_tuples *add_tuples(sp_tuples * matA, sp_tuples * matB){
	if ((matA->m != matB->m) || (matA->n != matB->n)) return NULL;	// if the addition is impossible, return NULL
	
	// if the addition is possible
	sp_tuples *retmat = (sp_tuples *) malloc(sizeof(sp_tuples));  // allocate memory for retmat
		// assign row and columns to retmat
		retmat->m = matA->m;
		retmat->n = matA->n;
	
		retmat->tuples_head = NULL;	// initialize tuples_head
	retmat->nz = 0;	// initialize nz
	
	// traversing matA	
	sp_tuples_node *head_A = matA->tuples_head;	// for the sake of simplicity
	
	while (head_A) {	// loop through every node in matA
		set_tuples(retmat, head_A->row, head_A->col, head_A->value);	// I guess I could use set_tuple
		
		head_A = (head_A->next);	// move on to the next node's pointer in matA
	}
	
	// traversing matB
	sp_tuples_node *head_B = matB->tuples_head;	// for the sake of simplicity
	
	while (head_B) {	// loop through every node in matB
		double value = gv_tuples(retmat, head_B->row, head_B->col);	// get the value in retmat at the coordinate
		
		if (value == 0) {	// if the node doesn't exsist in retmat
			set_tuples(retmat, head_B->row, head_B->col, head_B->value);	// I guess I could use set_tuple
		} else {	// if the node exsist
			set_tuples(retmat, head_B->row, head_B->col, (value+head_B->value));	// replace the value in retmat with the sum
		}
		
		head_B = (head_B->next);	// move on to the next node's pointer in matB
	}
	
	return retmat;	// return the address of the resulting matrix
}



// I didn't do it
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
	return NULL;
}



void destroy_tuples(sp_tuples * mat_t) {
	sp_tuples_node *head = mat_t->tuples_head;
	
	while (head) { // loop thorugh the linked list
		sp_tuples_node *tmp = head;
		free(tmp);	// free up every node, idk if this is correct
		head = (head->next);	// move on to the next node's pointer
	}
	free(mat_t);	// free up the whole tuple
}






