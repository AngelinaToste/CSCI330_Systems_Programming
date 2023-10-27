// Angelina Toste

/*
 * Purpose: program that uses a pointer based linked list. The progra must contain the following functions:
 * - LIST_SEARCH()
 * - LIST_INSERT()
 * - LIST_DELETE()
 * - LIST_DISPLAY()
 * - LIST_FREE()
 */

// 10/26/2023 7:24pm added changes to handle the case where names are added to the end of the tail

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
// modified version for first and last name with operator // uses hw5c.txt file
struct node{
    char *firstName;
    char *lastName;
    struct node *next;
};

typedef struct node LINK;

LINK *LIST_INSERT(char firstName[], char lastName[],  LINK *head)
{ // need to sort the names in increasing order, alphabetical order.

	    LINK *current, *newNode;
	    current = head;
	    if (current == NULL)// base case -- if the list is empty, insert the item
	    {
	    	current = (LINK *)(malloc(sizeof(LINK)));

	    	// we need to allocate space for name otherwise we are just creating aliases to the same memory location
	    	current->firstName = malloc(strlen(firstName));
	    	strcpy(current-> firstName, firstName);
	    	current->lastName = malloc(strlen(lastName));
	    	strcpy(current-> lastName, lastName);
	    	current-> next = head;
	    	head = current;
	    	//printf("name inserted: %s\n", name);

	    	return head;
	    }

	    while (current != NULL) // while the list is not empty
	    {
	    	if ((strcmp(head -> firstName, firstName) > 0) ) // if the entry belongs at the start of the list
	        {

	            newNode = (LINK *)(malloc(sizeof(LINK)));

	    		// we need to allocate space for name otherwise we are just creating aliases to the same memory location
	    		newNode->firstName = malloc(strlen(firstName));
	    		strcpy(newNode-> firstName, firstName);
	    		newNode->lastName = malloc(strlen(lastName));
	    		strcpy(newNode-> lastName, lastName);
	    		newNode->next = head;
	    		head = newNode;

	    		//printf("name inserted: %s\n", name);
	    		return head;

	    	}
	    	else if ((strcmp(current -> firstName, firstName) < 0) && (strcmp(current -> next -> firstName, firstName) > 0))
	        { // if the entry belongs between two entries on the list

	        	newNode = (LINK *)(malloc(sizeof(LINK)));

	        	// we need to allocate space for name otherwise we are just creating aliases to the same memory location
	        	newNode->firstName = malloc(strlen(firstName));
	        	strcpy(newNode-> firstName, firstName);
	        	newNode->lastName = malloc(strlen(lastName));
	        	strcpy(newNode-> lastName, lastName);

	        	newNode->next = current-> next;

	        	current->next = newNode;
	        	//printf("name inserted: %s\n", name);
	        	return head;
	        }
	    	// added elif for tail handling
	    	else if ((strcmp(current -> next-> firstName, firstName) < 0) && (current->next->next == NULL))
	    	{ // if the entry belongs at the end of the list

	    		 newNode = (LINK *)(malloc(sizeof(LINK)));

	    		 // we need to allocate space for name otherwise we are just creating aliases to the same memory location
	    		 newNode->firstName = malloc(strlen(firstName));
	    		 strcpy(newNode-> firstName, firstName);
	    		 newNode->lastName = malloc(strlen(lastName));
	    		 strcpy(newNode-> lastName, lastName);

	    		 newNode->next = current-> next->next;

	    		 current->next->next = newNode;
	    		 //printf("name inserted: %s\n", name);
	    		 return head;
	        }

	        current = current -> next;
	    }
	    return head;

}

void LIST_DELETE(char firstName[], LINK *(*head))
{ // delete routine, name is the name that is being deleted from the list

	 LINK *current, *obsoleteNode;
	    current = *head;

	    while (current != NULL)
	    {
	    	// search to see if upcoming name is the name that needs to be deleted
	        if (strcmp(current -> next -> firstName, firstName) == 0)
	        {

                obsoleteNode = current->next;
                current-> next = current -> next->next;

                free(obsoleteNode->firstName);
                obsoleteNode->lastName = NULL;
                free(obsoleteNode->lastName);
                obsoleteNode->lastName = NULL;
                free(obsoleteNode);
                obsoleteNode = NULL;
                //printf("Name deleted: %s\n", name);

                return;
	        }

	        current = current -> next;
	    }

}


int LIST_SEARCH(char firstName[], LINK *head)
{
	// do this to find out if a name exists in the list, no need to add a name already in list, cannot delete a name that dne
	// list traversal, done before insertion or deletion is made
	// returns 1 if found, else returns 0

    LINK *current;
    current = head;
    while (current != NULL)
    {

        if (strcmp(current -> firstName, firstName)==0)
        {
        	//printf("%s\n", current -> name);
        	return 1;
        }

        current = current -> next;
    }
    //printf("name not found: %s\n", name);
    return 0;
}

void LIST_DISPLAY(LINK *head)
{
	LINK *current;
	    current = head;
	    while (current != NULL)
	    {
	        printf("%s %s\n", current -> firstName, current -> lastName);

	        current = current -> next;
	    }

}


LINK *LIST_FREE(LINK *head)
{
	LINK *current, *temp;
	current = head;


	while (current != NULL)
	{
		temp = current; // where i am
		current = current -> next; // where i go next

		// delete the place you were in
		free(temp->firstName);
		temp->firstName = NULL;
		free(temp->lastName);
		temp->lastName = NULL;
	    free(temp);
	}
	return head;
}

int main(int argv,char **argc)
{
    // initialize head and current to build the linked list
    LINK *head;
    head = NULL;

   // handles case when no command line argument is provided
    if (argv < 2)
    {
        printf("\n*******************************************\n* You must include a filename to load.  *\n*******************************************\n");
        exit(1);
    }
    else
    {
    	// handles case when a command line argument is provided, loads the file in the linked list using search(), insert(), and delete()
        // open file for reading
    	FILE* stream;
    	stream = fopen(argc[1], "r");

         if (stream == NULL)
    	 {
    	        printf("error: file not found");
    	 }
    	 else
    	 {

    	        while(!feof(stream) )
    	        {
                     //parameters for getline and strtok
    	        	 char *lineBuf= NULL, *lineBuf2= NULL;;
    	        	 size_t lineBufSize = 40;
    	        	 int lineCount = 0;
    	        	 ssize_t lineSize;

    	        	 char *token, *op, *token2;
    	        	 char *search = " ";

    	        	  // get the size of the first line
    	        	  lineSize = getline(&lineBuf, &lineBufSize, stream);

                       while (lineSize > 0 && strcmp(lineBuf, "\n"))
    	        	    {

    	        	    	// read each line, break it up, assign to variables in struct, increment counters

    	        	    	lineCount++;

    	        	    	// break up the line on the " " character
    	        	    	token  = strtok(lineBuf, search);
    	        	    	token2 = strtok(lineBuf2, search); //the last name


    	        	        // get the second half of the line ending at the "\n" character
    	        	    	op = strtok(NULL, "\n");

    	        	    	int isFound = LIST_SEARCH(token, head); //search for the firstname in the list, 0 false, 1 true

    	        	    	if (strcmp(op,"a")==0) // ADD operation
    	        	    	{

    	        	    	    if (isFound == 0) // not found
    	        	    	    {
    	        	    	    	//add the name if it is not found
    	        	    	    	head = LIST_INSERT(token,token2, head);


    	        	    	    }

    	        	    	 }
    	        	    	 else if (strcmp(op,"d") == 0) // DELETE operation
    	        	    	 {
    	        	    	    if (isFound == 1) // is found
    	        	    	    {
    	        	    	    	//delete the name if it IS found
    	        	    	    	LIST_DELETE(token, &head);
    	        	    	    	//printf("name found\n");

    	        	    	    }

    	        	    	  }
    	        	    	  else
    	        	    	  { //handles case where a and d are not provided or there is a different letter
    	        	    	      printf("Unknown Operation");
    	        	    	  }

    	        	    	// get next line
    	        	    	lineSize = getline(&lineBuf, &lineBufSize, stream);


    	        	    }

                       free(lineBuf);
                       lineBuf = NULL;
                       free(lineBuf2);
                       lineBuf2 = NULL;
                 }

         fclose(stream);
         LIST_DISPLAY(head);
         LIST_FREE(head);

         }
    }
    return 0;
} */


struct node{
    char *name;
    struct node *next;
};

typedef struct node LINK;

LINK *LIST_INSERT(char name[], LINK *head)
{ // need to sort the names in increasing order, alphabetical order.

	    LINK *current, *newNode;
	    current = head;
	    if (current == NULL)// base case -- if the list is empty, insert the item
	    {
	    	current = (LINK *)(malloc(sizeof(LINK)));

	    	// we need to allocate space for name otherwise we are just creating aliases to the same memory location
	    	current->name = malloc(strlen(name));
	    	strcpy(current-> name, name);
	    	current-> next = head;
	    	head = current;
	    	//printf("name inserted: %s\n", name);

	    	return head;
	    }

	    while (current != NULL) // while the list is not empty
	    {
	    	if ((strcmp(head -> name, name) > 0) ) // if the entry belongs at the start of the list
	        {

	            newNode = (LINK *)(malloc(sizeof(LINK)));

	    		// we need to allocate space for name otherwise we are just creating aliases to the same memory location
	    		newNode->name = malloc(strlen(name));
	    		strcpy(newNode-> name, name);
	    		newNode->next = head;
	    		head = newNode;

	    		//printf("name inserted: %s\n", name);
	    		return head;

	    	}
	    	else if ((strcmp(current -> name, name) < 0) && (strcmp(current -> next -> name, name) > 0))
	        { // if the entry belongs between two entries on the list

	        	newNode = (LINK *)(malloc(sizeof(LINK)));

	        	// we need to allocate space for name otherwise we are just creating aliases to the same memory location
	        	newNode->name = malloc(strlen(name));
	        	strcpy(newNode-> name, name);

	        	newNode->next = current-> next;

	        	current->next = newNode;
	        	//printf("name inserted: %s\n", name);
	        	return head;
	        }
	    	// added elif for tail handling
	    	else if ((strcmp(current -> next-> name, name) < 0) && (current->next->next == NULL))
	    	{ // if the entry belongs at the end of the list

	    		 newNode = (LINK *)(malloc(sizeof(LINK)));

	    		 // we need to allocate space for name otherwise we are just creating aliases to the same memory location
	    		 newNode->name = malloc(strlen(name));
	    		 strcpy(newNode-> name, name);

	    		 newNode->next = current-> next->next;

	    		 current->next->next = newNode;
	    		 //printf("name inserted: %s\n", name);
	    		 return head;
	        }

	        current = current -> next;
	    }
	    return head;

}

void LIST_DELETE(char name[], LINK *(*head))
{ // delete routine, name is the name that is being deleted from the list

	 LINK *current, *obsoleteNode;
	    current = *head;

	    while (current != NULL)
	    {
	    	// search to see if upcoming name is the name that needs to be deleted
	        if (strcmp(current -> next -> name, name) == 0)
	        {

                obsoleteNode = current->next;
                current-> next = current -> next->next;

                free(obsoleteNode->name);
                obsoleteNode->name = NULL;
                free(obsoleteNode);
                obsoleteNode = NULL;
                //printf("Name deleted: %s\n", name);

                return;
	        }

	        current = current -> next;
	    }

}


int LIST_SEARCH(char name[], LINK *head)
{
	// do this to find out if a name exists in the list, no need to add a name already in list, cannot delete a name that dne
	// list traversal, done before insertion or deletion is made
	// returns 1 if found, else returns 0

    LINK *current;
    current = head;
    while (current != NULL)
    {

        if (strcmp(current -> name, name)==0)
        {
        	//printf("%s\n", current -> name);
        	return 1;
        }

        current = current -> next;
    }
    //printf("name not found: %s\n", name);
    return 0;
}

void LIST_DISPLAY(LINK *head)
{
	LINK *current;
	    current = head;
	    while (current != NULL)
	    {
	        printf("%s\n", current -> name);

	        current = current -> next;
	    }

}


LINK *LIST_FREE(LINK *head)
{
	LINK *current, *temp;
	current = head;


	while (current != NULL)
	{
		temp = current; // where i am
		current = current -> next; // where i go next

		// delete the place you were in
		free(temp->name);
		temp->name = NULL;
	    free(temp);
	}
	return head;
}

int main(int argv,char **argc)
{
    // initialize head and current to build the linked list
    LINK *head;
    head = NULL;

   // handles case when no command line argument is provided
    if (argv < 2)
    {
        printf("\n*******************************************\n* You must include a filename to load.  *\n*******************************************\n");
        exit(1);
    }
    else
    {
    	// handles case when a command line argument is provided, loads the file in the linked list using search(), insert(), and delete()
        // open file for reading
    	FILE* stream;
    	stream = fopen(argc[1], "r");

         if (stream == NULL)
    	 {
    	        printf("error: file not found");
    	 }
    	 else
    	 {

    	        while(!feof(stream) )
    	        {
                     //parameters for getline and strtok
    	        	 char *lineBuf= NULL;
    	        	 size_t lineBufSize = 40;
    	        	 int lineCount = 0;
    	        	 ssize_t lineSize;

    	        	 char *token, *op;
    	        	 char *search = " ";

    	        	  // get the size of the first line
    	        	  lineSize = getline(&lineBuf, &lineBufSize, stream);

                       while (lineSize > 0 && strcmp(lineBuf, "\n"))
    	        	    {

    	        	    	// read each line, break it up, assign to variables in struct, increment counters

    	        	    	lineCount++;

    	        	    	// break up the line on the " " character
    	        	    	token  = strtok(lineBuf, search);


    	        	        // get the second half of the line ending at the "\n" character
    	        	    	op = strtok(NULL, "\n");

    	        	    	int isFound = LIST_SEARCH(token, head); //search for the name in the list, 0 false, 1 true

    	        	    	if (strcmp(op,"a")==0) // ADD operation
    	        	    	{

    	        	    	    if (isFound == 0) // not found
    	        	    	    {
    	        	    	    	//add the name if it is not found
    	        	    	    	head = LIST_INSERT(token, head);


    	        	    	    }

    	        	    	 }
    	        	    	 else if (strcmp(op,"d") == 0) // DELETE operation
    	        	    	 {
    	        	    	    if (isFound == 1) // is found
    	        	    	    {
    	        	    	    	//delete the name if it IS found
    	        	    	    	LIST_DELETE(token, &head);
    	        	    	    	//printf("name found\n");

    	        	    	    }

    	        	    	  }
    	        	    	  else
    	        	    	  { //handles case where a and d are not provided or there is a different letter
    	        	    	      printf("Unknown Operation");
    	        	    	  }

    	        	    	// get next line
    	        	    	lineSize = getline(&lineBuf, &lineBufSize, stream);


    	        	    }

                       free(lineBuf);
                       lineBuf = NULL;
                 }

         fclose(stream);
         LIST_DISPLAY(head);
         LIST_FREE(head);

         }
    }
    return 0;
}

