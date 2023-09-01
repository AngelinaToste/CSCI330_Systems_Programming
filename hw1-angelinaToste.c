// Angelina Toste

/*
 * Homework 1
 * Purpose: calculate the interest paid on a loan (monthly), take the user to a point when balance
 * is zero or negative, calculate total interest paid
 *
 */

# include <stdio.h>
#include <stdlib.h>

int main()
{
    float r = 0.22, B = 5000.0, P = 0, Io = (r/12) * B, In, totalInterest = Io, prevInterest, prevBalance;

    //initializing counter
    int counter = 1;

    // accepts monthly payment amount from the user
    printf("Enter your monthly payment: ");
    scanf( "%f", &P);

    //prints values for interest rate, balance, and payment amount
    printf("\nr = %1.2f", r);
    printf("\nB = %1.2f", B);
    printf("\nP = %1.2f", P);

    //loop runs until balance is lower than payment amount, before B is negative
    while (B >= P)
   {

    	if (counter == 1)
    	{

    		printf("\n\n%d %1.2f %1.2f\n", counter, Io, B);
    		prevInterest = Io;
    		prevBalance = B;
    		counter ++;
    	}
    	else
    	{

    	    In = (r/12)*(prevBalance - P + prevInterest);
    	    B = prevBalance - P + prevInterest;
    	    printf("%d %1.2f %1.2f\n", counter, In, B);

    	    //update variables
    	    B = prevBalance - P + prevInterest;
    	    prevBalance = B;
    	    prevInterest = In;
    	    totalInterest = totalInterest + prevInterest;
    	    counter++;
    	}

   }

    printf("\nTotal Interest: %1.2f\n", totalInterest);
}



