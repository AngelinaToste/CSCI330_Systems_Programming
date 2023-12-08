#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _data {
	char *firstName;
	char *lastName;
} junk;



int SCAN(FILE *(*stream))
{// open file/ stream, return integer indicating how many lines are in the file

	// open file for reading
	*stream = fopen("hw4c.data", "r");

	// initializing counter for the number of lines in the file
	int numOfContacts = 0;

	if (*stream == NULL)
	{
		printf("error: file not found");
	}
	else
	{

        while ( !feof(*stream)) // count the number of lines in the file
        {
        	junk.firstName = malloc(sizeof(junk.firstName));
            junk.lastName = malloc(sizeof(junk.lastName));
        	fscanf( *stream, "%s %s\n", junk.firstName, junk.lastName);
        	free(junk.firstName);
            free(junk.lastName);
        	numOfContacts++;
        }
	}

	//close the file
	fclose(*stream);

	//returns an integer indicating how many lines are in the file
	return numOfContacts;
}


struct _data *LOAD(FILE *stream, int size)
{ //rewind file, create dynamic array (of size), read data, populate struct dynamic array

	// open file for reading, rewind stream
    stream = fopen("hw4.data", "r");
    rewind(stream);


    //create dynamic array of size
    struct _data *Blackbox;
    Blackbox = calloc(size, sizeof(struct _data));

    //parameters for getline and strtok
    char *lineBuf= NULL;
    size_t lineBufSize = 0;
    int lineCount = 0;
    ssize_t lineSize;

    char *token;
    char *search = " ";


    int counter = 0;

    // get the size of the first line
    lineSize = getline(&lineBuf, &lineBufSize, stream);

    while (lineSize >= 0 && counter < size)
    {
    	// read each line, break it up, assign to variables in struct, increment counters

    	lineCount++;

    	// break up the line on the " " character
    	token  = strtok(lineBuf, search);

    	Blackbox[counter].firstName = malloc(strlen(token));
    	strcpy(Blackbox[counter].firstName, token);

        // get the second half of the line ending at the "\n" character
    	token  = strtok(NULL, "\n");
    	Blackbox[counter].lastName = malloc(strlen(token));
    	strcpy(Blackbox[counter].lastName, token);

    	// get next line and increment counter
    	lineSize = getline(&lineBuf, &lineBufSize, stream);
    	counter++;

    }

    //free and close lineBug and the file opened during the function
    free(lineBuf);
    lineBuf = NULL;
    fclose(stream);

    return Blackbox;

}

void SEARCH(struct _data *Blackbox, char *name, int size)
{//gets dynamic array of struct that was passed to it, name being searched for, size of array
 //searches for name in list

 int counter = 0;
 while( counter < size)
 {
     if( strcmp(Blackbox[counter].firstName, name) == 0 ) // if the name matches a name in the list
     {
    	 printf("\n*******************************************\n The name was found at the %i entry.  \n*******************************************\n", counter);
        return;
     }
    counter++;
 }

 // if NO matches found in the list
 printf("\n*******************************************\n The name was NOT found.  \n*******************************************\n");

}

void FREE(struct _data *Blackbox, int size)
{ // frees up all dynamic memory that was allocated. recall how many times calloc or malloc have been called.
 //need to free() multiple times for all of the "name" pointers in the struct (use size)
 // also need to free Blackbox

	for (int i = 0; i < size; i++)
	{
		free(Blackbox[i].firstName);
        free(Blackbox[i].lastName);
	}
	free(Blackbox);

}


int main (int argv,char **argc)
{

    FILE* data;

    // determine how many lines in the file
    int size = SCAN (&data);

    //populate the dynamic struct array, Blackbox
    struct _data *Blackbox;
    Blackbox= (LOAD(data, size));

    // handles case when no command line argument is provided
    if (argv < 2)
    {
        printf("\n*******************************************\n* You must include a name to search for.  *\n*******************************************\n");
        exit(1);
    }
    else
    {
    	// handles case when a command line argument is provided, searches for argument in the struct array
    	SEARCH(Blackbox, argc[1], size);
    }

    FREE(Blackbox, size);

    return 0;

}

