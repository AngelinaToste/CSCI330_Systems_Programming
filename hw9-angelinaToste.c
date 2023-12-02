// Angelina Toste

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graphNode
{
	char name[42];        //Establishment name
	int arcCnt;           // Number of outgoing arc from this node
	int weights[10];      // Weights of each outgoing arc from this node
	struct graphNode *arcs[10];

};

struct listNode
{
    char name[42];            //Establishment name
    struct listNode *next;
    struct graphNode *graph;  // Pointer into graph
};

typedef struct graphNode GRAPH;
typedef struct listNode LINK;

LINK *NODE_INSERT(char name[42], LINK *head)
{
	LINK *current, *newNode;
	current = head;
	// if the entry belongs at the end of the list

	if (current == NULL)// base case -- if the list is empty, insert the item
	{
		    	current = (LINK *)(malloc(sizeof(LINK)));
		    	strcpy(current-> name, name);
		    	current-> next = head;
		    	head = current;

		    	// create a corresponding graph for the link list node
		    	current->graph = (GRAPH *)(malloc(sizeof(GRAPH)));
		    	strcpy(current->graph->name, name);
		    	current->graph->arcCnt = 0;

		    	printf("name inserted: %s\n", name);

	}
	else
	{
        // if the entry belongs at the end of the list


		//create the new node
		newNode = (LINK *)(malloc(sizeof(LINK)));

		//put the name into the new node
		strcpy(newNode-> name, name);

		// store head reference in another variable
		//LINK last = *head;

		// point newNode-> next to NULL
		newNode->next = NULL;

		//get the last node
		while (current!= NULL)
		{
			current = current->next;
		}

		//newNode->next = current-> next->next;

		current->next = newNode;  //<-------segfault occurred here

		// create a corresponding graph for the link list node
		current->next->graph = (GRAPH *)(malloc(sizeof(GRAPH)));
		strcpy(current->next->graph->name, name);
		current->next->graph->arcCnt = 0;
		printf("name inserted: %s\n", name);


	}

	current = current -> next;
	return head;
}

LINK *NODE_ADD_INFO(char start[42], char end[42], int weight,  LINK *head)
{ // this function will search the linked list for startName,
	// add the endName to the arcs, add the weight, and increment the arcCnt

    LINK *current;
    current = head;
    while (current != NULL)
    {

        if (strcmp(current -> name, start)==0)
        {


        	printf("%s ", current -> name);
        	printf("MATCH MADE\n");

        	//check if arcCnt is null, if so, set it to 0
        	//printf("%d", current->graph->arcCnt);
        	//current->graph->arcCnt = 1;


            (current->graph->arcCnt)++;

        	//search for next available space in the weight
        	// and arc arrays to add the corresponding info
        	int i = 0;
        	//int infoAdded = 0; // flag to determine  if info was added successfully

        	while ((i < 10))  //&& !infoAdded)
        	{

        		if ((current->graph->weights[i] == 0) && (current->graph->arcs[i]->name == NULL))
        		{
        			current->graph->weights[i] = weight;
        			//current = current -> next;

        			strcpy(current->graph->arcs[i]->name, end);
        			//infoAdded = 1;
        			//break;
        			return head;
        		}
        		else
        		{
        			i++;
        		}

        	}

        }

        current = current -> next;
    }
    //printf("name not found: %s\n", start);

    return head;
}

int choosePath(int arcCnt)
{ // parameters: the number of arcs at a given node
  // uses a random number generator with the seed 2021
  // returns a random Number

	int index;
	srand(2021);
	index = (random() % arcCnt);
	return index;
}

int main (int argv, char **argc)
{
	// initialize head and current to build the linked list
    LINK *head;
    head = NULL;

	char fileName[] = "hw9.data";
    FILE *dataFile;
    dataFile = fopen(fileName, "r");
    int arraySize = 0; // counter for how many elements will be added to the array

    if (dataFile == NULL)
    {
        printf("error: file not found\n");
        //fclose(dataFile);
        return 0;
    }


    //----STEP 1: READ DATA FROM THE FILE UNTIL STOP IS REACHED
    char name[42];
    fscanf(dataFile, "%s\n", name);

            // read up until "STOP" is reached
        while ((strcmp(name, "STOP")!=0) && !feof(dataFile))
        {

            // read each line, break it up, assign to variables in struct, increment counters
            //lineCount++;

            // break up the line on the "\n" character
            //token  = strtok(lineBuf, search);
            head = NODE_INSERT(name, head);
            arraySize++;

            // get next line
            //lineSize = getline(&lineBuf, &lineBufSize, dataFile);
            //token  = strtok(lineBuf, search);
            fscanf(dataFile, "%s\n", name);

        }
        printf("STOP was reached\n");
        //free(lineBuf);
        //lineBuf = NULL;


        // read up until "STOP STOP 0" is reached
    char startName[42], endName[42];
    int weight;

    fscanf(dataFile, "%s %s %d", startName, endName, &weight);

    while ((strcmp(startName, "STOP")!=0) && (strcmp(endName, "STOP")!=0) && (weight != 0))
    {
    	// this function will search the linked list for startName,
    	//      add the endName to the arcs, add the weight, and increment the arcCnt
        NODE_ADD_INFO(startName, endName, weight,  head);

        //set the variables back to 0
        startName[42] = 0;
        endName[42] = 0;
        weight = 0;

        // read the next line of the file to check the values of startName, endName, and weight
        fscanf(dataFile, "%s %s %d", startName, endName, &weight);

    }
    printf("STOP STOP 0 was reached\n");

    char startingLocation[42];
    fscanf(dataFile, "%s", startingLocation);

    //-----STEP 4: THE LAST LINE WILL BE THE STARTING POINT.
    printf("Starting node: %s", startingLocation);

    //-----


    //free(current);
    fclose(dataFile);
}

