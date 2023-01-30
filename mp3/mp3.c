// This program prints out a row of Pascal's Tringle specified by user
// User inputs a row number
// Then the program calculates the numbers in that row
// It calculates one and prints out one, and then move on to the next number
// Until it reaches the end of the row


#include <stdio.h>
#include <stdlib.h>

int calc_num(float n, float k);	// function prototype

int main()
{
  int row;
  unsigned long num;

  // get user input
  printf("Enter a row index: ");
  scanf("%d",&row);

  for (int i=0; i<=row; i++){	// calculate a number and print a number
    if (i==0) num = 1;		// if it's the 1st item in the row, 
				// it will just be 1, or a math error will be produced
    else num = calc_num(row, i);

    printf("%lu ", num);	// print out calculated number
  }

  return 0;
}


int calc_num(float n, float k){
  unsigned long res = 1;

  for (float j=1; j<=k; j++){	// implement the math func provided
    res *= (n+1-j);
    res /= j;
  }

  return res;
}
