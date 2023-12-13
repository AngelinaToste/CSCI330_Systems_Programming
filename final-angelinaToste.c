//Angelina Toste

// CSCI 330 Final: based on hw 5 with addition of last name and abilities to sort based on first and last name


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
    char *firstname;
    char *lastname;
    struct node *next;
};

typedef struct node LINK;

LINK *LIST_INSERT(char firstname[], char lastname[], LINK *head)
{ // need to sort the names in increasing order, alphabetical order.
	// if firstOrLast is f, sorted in order by first name, if l, sorted in order by last name
	LINK *current, *newNode;
	current = head;
	if (current == NULL)// base case -- if the list is empty, insert the item
	{
		current = (LINK *)(malloc(sizeof(LINK)));

		// we need to allocate space for name otherwise we are just creating aliases to the same memory location
		current->firstname = malloc(strlen(firstname));
		strcpy(current-> firstname, firstname);

		// we need to allocate space for name otherwise we are just creating aliases to the same memory location
		current->lastname = malloc(strlen(lastname));
		strcpy(current-> lastname, lastname);


		current-> next = head;
		head = current;
		//printf("name inserted: %s %s\n", firstname, lastname);

		return head;
	}

	while (current != NULL) // while the list is not empty
	{
		if ((strcmp(head -> firstname, firstname) > 0) ) // if the entry belongs at the start of the list
		{

			newNode = (LINK *)(malloc(sizeof(LINK)));

			// we need to allocate space for name otherwise we are just creating aliases to the same memory location
			newNode->firstname = malloc(strlen(firstname));
			strcpy(newNode-> firstname, firstname);

			// we need to allocate space for name otherwise we are just creating aliases to the same memory location
			newNode->lastname = malloc(strlen(lastname));
			strcpy(newNode-> lastname, lastname);

			newNode->next = head;
			head = newNode;

			//printf("name inserted: %s\n", name);
			return head;

		}
		else if ((strcmp(current -> firstname, firstname) < 0) && (current->next == NULL))
		{ // if the entry belongs at the end of the list

		   newNode = (LINK *)(malloc(sizeof(LINK)));

			// we need to allocate space for name otherwise we are just creating aliases to the same memory location
			newNode->firstname = malloc(strlen(firstname));
			strcpy(newNode-> firstname, firstname);

			// we need to allocate space for name otherwise we are just creating aliases to the same memory location
			newNode->lastname = malloc(strlen(lastname));
			strcpy(newNode-> lastname, lastname);

			newNode->next = current->next;

			current->next = newNode;
			//printf("name inserted: %s\n", name);
			return head;
		}
		else if ((strcmp(current -> firstname, firstname) < 0) && (strcmp(current -> next -> firstname, firstname) > 0))
		{ // if the entry belongs between two entries on the list

			newNode = (LINK *)(malloc(sizeof(LINK)));

			// we need to allocate space for name otherwise we are just creating aliases to the same memory location
			newNode->firstname = malloc(strlen(firstname));
			strcpy(newNode-> firstname, firstname);

			// we need to allocate space for name otherwise we are just creating aliases to the same memory location
			newNode->lastname = malloc(strlen(lastname));
			strcpy(newNode-> lastname, lastname);

			newNode->next = current-> next;

			current->next = newNode;
			//printf("name inserted: %s\n", name);
			return head;
		}

	    current = current -> next;

	}
	return head;

}

void LIST_DELETE(char firstname[], LINK *(*head)) // no repeat names, no need to account for occurrences where last name is also needed to delete
{ // delete routine, name is the name that is being deleted from the list

	    LINK *current, *obsoleteNode;
	    current = *head;

	    if (strcmp(current->firstname, firstname) == 0)
	    {
            obsoleteNode = current;
	        (*head) = (*head) -> next;

	        free(obsoleteNode->firstname);
	        obsoleteNode->firstname = NULL;
	        free(obsoleteNode);
	        obsoleteNode = NULL;

	        //printf("Name deleted: %s\n", firstname);
            return;
	    }

	    while (current->next != NULL)
	    {
	    	// search to see if upcoming name is the name that needs to be deleted
	        if (strcmp(current -> next -> firstname, firstname) == 0)
	        {

                obsoleteNode = current->next;
                current-> next = current -> next->next;

                free(obsoleteNode->firstname);
                obsoleteNode->firstname = NULL;
                free(obsoleteNode);
                obsoleteNode = NULL;
                //printf("Name deleted: %s\n", firstname);

                return;
	        }

	        current = current -> next;
	    }

}


int LIST_SEARCH(char firstname[], LINK *head)
{
	// do this to find out if a name exists in the list, no need to add a name already in list, cannot delete a name that dne
	// list traversal, done before insertion or deletion is made
	// returns 1 if found, else returns 0

    LINK *current;
    current = head;
    while (current != NULL)
    {

        if (strcmp(current -> firstname, firstname)==0)
        {
        	//printf("%s\n", current -> firstname);
        	return 1;
        }

        current = current -> next;
    }
    //printf("name not found: %s\n", firstname);
    return 0;
}

void LIST_DISPLAY(LINK *head)
{
	LINK *current;
	    current = head;
	    while (current != NULL)
	    {
	        printf("%s %s\n", current -> firstname, current -> lastname);

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
		free(temp->firstname);
		temp->firstname = NULL;
		free(temp->lastname);
		temp->lastname = NULL;
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
    	        //printf("error: file not found");
    	 }
    	 else
    	 {

    		 while(!feof(stream))
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
    		     	        //printf("name found %s %s\n", token, token2);

    		     	      }

    		     	  }
    		     	  else
    		     	  { //handles case where a and d are not provided or there is a different letter
    		     	      //printf("Unknown Operation");
    		     	  }

    		     	  // get next line
    		     	  lineSize = getline(&lineBuf, &lineBufSize, stream);


    		     }

    		     free(lineBuf);
    		     lineBuf = NULL;
    		     free(lineBuf2);
    		     lineBuf2 = NULL;
    		  }

        }

         fclose(stream);
         LIST_DISPLAY(head);
         LIST_FREE(head);

    }
    return 0;
}

