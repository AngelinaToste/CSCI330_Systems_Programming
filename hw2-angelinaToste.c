// Angelina Toste
/*
 * Homework 2
 * Purpose:
 *
 *Notes:
 *- 9/15 made the array of structs called carData car[] and need to next sort the array using the int values and float values with the bubble sort
 *-
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct carData
{
	char name[50], color[50];
	float model;
	int cost;
};

struct temp
{
	char name[50], color[50];
	float model;
	int cost;
};

//struct temp;

void intLowToHighSort(struct carData *car, int size)
{ // bubble sort to arrange array values in order of low to high

    struct carData *temp;
    for (int x  = 0; x < size - 1; ++x)
    {
    	for (int i = 0; i < size - x - 1; ++i)
    	{
    		if (car[i].cost > car[i + 1].cost)
    		{

    			*temp = car[i];
    			car[i]= car[i + 1];
    			car[i + 1]= *temp;

    			printf("%s %f %d %s \n", car[i].name, car[i].model, car[i].cost, car[i].color);
    		}
    	}
    }
    printf("%d\n", size);
    for (int i = 0; i < 4; ++i)
        {
        	//printf("%d\n", size);
        	printf("%s %f %d %s \n", car[i].name, car[i].model, car[i].cost, car[i].color);
        }
        printf("\n");

}
/*
void printArray (struct carData *car, int size)
{

    for (int i = 0; i < size; ++i)
    {
    	printf("%i\n", size);
    	//printf("%s %f %d %s \n", car[i].name, car[i].model, car[i].cost, car[i].color);
    }
    printf("\n");
}

*/


int main()
{
	FILE* data;
	data  = fopen("hw2.data", "r");

	if (NULL == data)
	{
		printf("File can't be found. \n");
	}

	int numCars = 0; // numCars is the size of the array (according to number of lines in the file)
	struct carData car[numCars + 1];

	// this will continue to read the file and print until the EOF is reached
    int index = numCars;

	while (fscanf(data, "%s %f %i %s\n", car[index].name, &car[index].model, &car[index].cost, car[index].color ) != EOF)
	{
		printf("%s %f %i %s\n", car[index].name, car[index].model, car[index].cost, car[index].color );
		numCars++;
	}


	printf("%d", numCars);

	fclose(data);



	// this operates the menu
	int choice;

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
                printf("%s", "no");
	    	}
	    	else if (choice == 2)
	    	{
	    		printf("%s", "no");
	    	}
	    	else if (choice == 3)
	    	{
	    		printf("%s", "no");
	    	}
	    	else if (choice == 4)
	    	{
	    		printf("%s\n", "choice 4");
	    		//const int numCarsSize = numCars;
	    		intLowToHighSort(car, numCars);
	    		//printf("%s\n", car[0].name);
	    		//printf("%d", numCars);
	    		//printArray(car, numCars);
	    		printf("\n");

	    	}
	    }

	return 0;
}
