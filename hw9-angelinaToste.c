// Angelina Toste

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graphNode
{
	char name[100];        //Establishment name
	int arcCnt;           // Number of outgoing arc from this node
	int weights[10];      // Weights of each outgoing arc from this node
	struct graphNode *arcs[10];

};

struct listNode
{
    char name[100];            //Establishment name
    struct listNode *next;
    struct graphNode *graph;  // Pointer into graph
};

typedef struct graphNode GRAPH;
typedef struct listNode LINK;

LINK *NODE_INSERT(char name[100], LINK *head)
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


		    	//printf("name inserted: %s\n", name);

	}
	else
	{
        // if the entry belongs at the end of the list

		//create the new node
		newNode = (LINK *)(malloc(sizeof(LINK)));

		//put the name into the new node
		strcpy(newNode-> name, name);

		// store head reference in another variable

		// point newNode-> next to NULL
		newNode->next = NULL;

		//get the last node
		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = newNode;

		// create a corresponding graph for the link list node
		current->next->graph = (GRAPH *)(malloc(sizeof(GRAPH)));
		strcpy(current->next->graph->name, name);
		current->next->graph->arcCnt = 0;
		//printf("name inserted: %s\n", name);

	}

	current = current -> next;
	return head;
}

LINK *NODE_ADD_INFO(char start[100], char end[100], int weight,  LINK *head)
{ // this function will search the linked list for startName,
	// add the endName to the arcs, add the weight, and increment the arcCnt

    LINK *current;
    current = head;
    while (current != NULL)
    {

        if (strcmp(current -> name, start)==0)
        {


        	//printf("%s ", current -> name);
        	//printf("MATCH MADE\n");

            (current->graph->arcCnt)++;
           // printf("new arc count: %s %d\n", current->graph->name, current->graph->arcCnt);


        	//search for next available space in the weights array
        	// and arc arrays to add the corresponding info
        	int i = 0;

        	while ((i < 10))
        	{
        		if ((current->graph->weights[i] == 0) && (current->graph->arcs[i]->name == NULL))
        		{
        			current->graph->weights[i] = weight;

        			// need to point arc[i] to the next graph node arcNode->graph
        			// arcNode is a linked list node with the same name as "end"
        			LINK *arcNode;
        			arcNode = head;
        			while (arcNode != NULL)
        			{

        			        if (strcmp(arcNode -> name, end)==0)
        			        {
                                /*arcNode->graph->arcCnt++;
                                //printf("new arc count: %s %d\n", arcNode->graph->name, arcNode->graph->arcCnt);

                                int x = 0;
                                while (x<10)
                                {
                                    if ((arcNode->graph->weights[x] == 0) && (arcNode->graph->arcs[x]->name == NULL))
                                    {
                                        arcNode->graph->weights[x] = weight;
                                        arcNode->graph->arcs[x] = current->graph;
                                    }
                                    else
                                    {
                                    	x++;
                                    }
                                }
                                */


                                //set the arcs[i] to be the graph of the end location
                                current->graph->arcs[i] = arcNode->graph;


                                return head;

        			        }
        			        arcNode = arcNode -> next;
        			}

        		}
        		else
        		{
        			i++;
        		}

        	}

        }

        current = current -> next;
    }

    return head;
}

int choosePath(int arcCnt)
{ // parameters: the number of arcs at a given node (NOTE: if this number is 0, index = 0
  // uses a random number generator with the seed 2021
  // returns a random Number

	int index;

	if (arcCnt == 0)
	{
		index = 0;
	}
	else
	{

	    index = (random() % (arcCnt));
	}

	//printf("%d\n", index);

	return index;
}

int drunkWalk(char start[100], char end[100], LINK *head)
{ // uses the starting point (start) to "walk" through the graph using the linked list.
	// returns the accumulated cost of the walk

	int accumulatedCost = 0, arcCount, index;
	char nextName[100];

	// find start in the linked list

	LINK *current;
	current = head;

	while (current != NULL)
	{

	    if (strcmp(current -> name, start)==0)
	    {
            //printf("%s ", current -> name);
	        //printf("FOUND START\n");
	        break;

	    }

	    current = current -> next;

	}

	// get arcCnt from Start
	arcCount = current->graph->arcCnt;

	// put the arcCnt into the choosePath() function to get a random index for the next path
	index = choosePath(arcCount);

	// use the random index to access the list->graph->weights[index] and list->graph->arcs[index]->name
	//----save the currentName
	strcpy(nextName, current->graph->arcs[index]->name);

	//-----add the weight to the accumulatedCost
    accumulatedCost = accumulatedCost + current->graph->weights[index];
    //printf("Accumulated Cost: %d\n", accumulatedCost);

	//while loop until home is reached (while not home) or (while strcmp(arc name, end)!=0)
    while (strcmp(nextName, end)!=0)
    {
    	arcCount = 0;
    	index = 0;

	    // find temp in the list
    	LINK *temp;
    	temp = head;
    	while (temp != NULL)
    	{

    	    if (strcmp(temp -> name, nextName)==0)
    	    {
                //printf("%s ", temp -> name);
    	        //printf("FOUND NEXT %s\n", temp->name);
    	        break;

    	    }
    	    temp = temp -> next;

    	}

    	// get the arc count of the current name
    	arcCount = temp->graph->arcCnt;

	    // put the arcCnt into the choosePath() function to get a random index for the next path
    	index = choosePath(arcCount);

		// use the random index to access the list->graph->weights[index] and list->graph->arcs[index]->name
    	//----save the currentName
    	strcpy(nextName, temp->graph->arcs[index]->name);

    	//-----add the weight to the accumulatedCost
    	accumulatedCost = accumulatedCost + temp->graph->weights[index];
    	//printf("Accumulated Cost: %d\n", accumulatedCost);

	    // keep the loop running by grabbing the next list name using current = next arc name
    }

    //print the last node/ end node
    printf("Ending Node: %s\n", nextName);

	return accumulatedCost;

}

LINK *FREE(LINK *head)
{
		LINK *current, *temp;
		current = head;

		while (current != NULL)
		{
			temp = current; // where i am
			current = current -> next; // where i go next

			// delete the place you were in
			free(temp->graph);
			temp->graph = NULL;
			free(temp);

		}
		return head;
}

int main (int argv, char **argc)
{
	// initialize head and current to build the linked list
    LINK *head;
    head = NULL;

	char fileName[] = "hw9.data";
    FILE *dataFile;
    dataFile = fopen(fileName, "r");

    if (dataFile == NULL)
    {
        printf("error: file not found\n");
        return 0;
    }


    //----STEP 1: READ DATA FROM THE FILE UNTIL STOP IS REACHED
    char name[100];
    fscanf(dataFile, "%s\n", name);

            // read up until "STOP" is reached
        while ((strcmp(name, "STOP")!=0) && !feof(dataFile))
        {
        	// insert the new name into the linked list
            head = NODE_INSERT(name, head);

            // read the next line of the data file
            fscanf(dataFile, "%s\n", name);

        }
        //printf("STOP was reached\n");


    //----STEP 2: ADD INFO FOR EACH NODE IN THE LINKED LIST, STOP WHEN "STOP STOP 0" IS REACHED
    char startName[100], endName[100];
    int weight;

    fscanf(dataFile, "%s %s %d", startName, endName, &weight);

    while ((strcmp(startName, "STOP")!=0) && (strcmp(endName, "STOP")!=0) && (weight != 0))
    {
    	// this function will search the linked list for startName,
    	//      add the endName to the arcs, add the weight, and increment the arcCnt
        NODE_ADD_INFO(startName, endName, weight,  head);

        //set the variables back to 0
        startName[100] = 0;
        endName[100] = 0;
        weight = 0;

        // read the next line of the file to check the values of startName, endName, and weight
        fscanf(dataFile, "%s %s %d", startName, endName, &weight);

    }

    //printf("STOP STOP 0 was reached\n");

    char startingLocation[100];
    int accumulatedCost;

    fscanf(dataFile, "%s", startingLocation);

    //-----STEP 3: THE LAST LINE OF THE FILE WILL BE THE STARTING POINT.
    printf("Starting node: %s\n", startingLocation);

    //-----STEP 4: THE DRUNKARD'S WALK/ PRINT THE LAST NODE
	srand(2021); // seeding the random number generator for drunkWalk
    accumulatedCost = drunkWalk(startingLocation, "Home", head);

    //-----STEP 5: PRINT THE ACCUMULATED COST
    printf("Accumulated Cost: %d\n", accumulatedCost);

    fclose(dataFile);
    FREE(head);
}

