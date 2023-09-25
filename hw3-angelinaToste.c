// Angelina Toste
/*
 * Homework 3
 * Purpose: using a menu, sort a dynamic struct array from high to low or low to high based on the int values and float values in the struct array.
 *
 *-
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEBUG 0

struct carData
{
	char name[50], color[50];
	float model;
	int cost;
} *car, temp, junk;

void floatSort(struct carData *car, int size, int isLowToHigh)
{ // bubble sort to arrange array float values
	// the third parameter determines sort type: high to low(0) OR low to high(1)


    struct carData temp;
    for (int x  = 0; x < size - 1; ++x)
    {
    	for (int i = 0; i < size - x - 1; ++i)
    	{
    		if (car[i].model > car[i + 1].model)
    		{

    			temp = car[i];
    			car[i]= car[i + 1];
    			car[i + 1]= temp;

    		}
    	}
    }
    if (isLowToHigh == 1)
    { // sorts from low to high
        for (int i = 0; i < size; i++)
        {
        	printf("%s %f %d %s \n", car[i].name, car[i].model, car[i].cost, car[i].color);
        }
        printf("\n");
    }
    else if (isLowToHigh == 0)
    { // sorts from high to low
    	for (int i = size - 1; i >= 0 ; i--)
    	{
    	    printf("%s %f %d %s \n", car[i].name, car[i].model, car[i].cost, car[i].color);
    	}
    	printf("\n");
    }

}


void intSort(struct carData *car, int size, int isLowToHigh)
{ // bubble sort to arrange array int values
	// the third parameter determines sort type: high to low(0) OR low to high(1)
    struct carData temp;
    for (int x  = 0; x < size - 1; ++x)
    {
    	for (int i = 0; i < size - x - 1; ++i)
    	{
    		if (car[i].cost > car[i + 1].cost)
    		{

    			temp = car[i];
    			car[i]= car[i + 1];
    			car[i + 1]= temp;

    		}
    	}
    }

    if (isLowToHigh == 1)
    { // sorts from low to high
        for (int i = 0; i < size; i++)
        {
            printf("%s %f %d %s \n", car[i].name, car[i].model, car[i].cost, car[i].color);
        }
        printf("\n");
     }
     else if (isLowToHigh == 0)
     { // sorts from high to low
         for (int i = size - 1; i >= 0 ; i--)
         {
        	    printf("%s %f %d %s \n", car[i].name, car[i].model, car[i].cost, car[i].color);
         }
         printf("\n");
      }
}



int fillStructArray(struct carData **car)
{ //opens the file, updates the struct array with the file data, returns the number of lines in the file or the size of the array
	    FILE* data;
		data  = fopen("hw3.data", "r");

		//numCars is the size of the array (according to number of lines in the file)

		int numCars = 0;

		//checks if file is found
		if (NULL == data)
		{
			printf("File can't be found. \n");
		}

		//reads and updates the struct array until an EOF has been found
		while (fscanf(data, "%s %f %i %s\n", junk.name, &junk.model, &junk.cost, junk.color ) != EOF)
		{
			numCars++;
		}

		rewind(data);

		// allocate space according to the size of the data file or number of cars listed in the data file (numCars)
		*car = (struct carData*)calloc(numCars, sizeof(struct carData));


		for (int i = 0; i < numCars; i++)
		{
			fscanf(data, "%s %f %i %s\n", (*car)[i].name, &(*car)[i].model, &(*car)[i].cost, (*car)[i].color);


			if(DEBUG)
			{
				printf("%s %f %i %s\n", (*car)[i].name, (*car)[i].model, (*car)[i].cost, (*car)[i].color);
			}

		}

		fclose(data);

		return numCars;
}

int main()
{


	// initializing variables
	struct carData *car;
	int numCars = fillStructArray(&car), choice;


	// this operates the menu

	    while (choice != 5)
	    {
	    	printf("Menu\n");
	    	printf("1. Sort data by the float value & print high to low\n");
	    	printf("2. Sort data by the float value & print low to high\n");
	    	printf("3. Sort data by the int value & print high to low\n");
	    	printf("4. Sort data by the int value & print low to high\n");
	    	printf("5. Exit\n\n");

	    	printf("Please choose an option: ");
	    	scanf("%d", &choice);
	    	printf("\n\n");

	    	if (choice == 1)
	    	{
                floatSort(car, numCars, 0);
                printf("\n");
	    	}
	    	else if (choice == 2)
	    	{
	    		floatSort(car, numCars, 1);
	    		printf("\n");
	    	}
	    	else if (choice == 3)
	    	{
	    		intSort(car, numCars, 0);
	    		printf("\n");
	    	}
	    	else if (choice == 4)
	    	{
	    		intSort(car, numCars, 1);
	    		printf("\n");

	    	}
	    }

	return 0;
}
