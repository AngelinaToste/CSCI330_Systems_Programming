//Angelina Toste ~revised as of 11/09/2023, changes: new scan function

/* Modification made to homework 4 to allow for two names specified, first and last name
 * to account for this, modifications have been made to each of the functions from hw4.
 * the following functions are included in this program:
 * -SCAN()
 * -LOAD()
 * -SEARCH()
 * -FREE()
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _data {
	char *firstname;
	char *lastname;
	long number;
} junk;

int SCAN(FILE *(*stream))
{// open file/ stream, return integer indicating how many lines are in the file

	// open file for reading
	*stream = fopen("midterm.data", "r");

	// initializing counter for the number of lines in the file
	int numOfContacts = 0;

	if (*stream == NULL)
	{
		printf("error: file not found");
	}
	else
	{
		char* line = NULL;
		size_t size = 0;
		size_t nread;

        while ( (nread = getline(&line, &size, *stream)) != -1) // count the number of lines in the file
        {

        	numOfContacts++;
        }
        free(line);

	}

	//close the file
	fclose(*stream);

	//returns an integer indicating how many lines are in the file
	return numOfContacts;
}

// the following scan is incorrect because of how junk first and last names are malloced
// the sizeof operator only gets the size of a type
/*int SCAN(FILE *(*stream))
{// open file/ stream, return integer indicating how many lines are in the file

	// open file for reading
	*stream = fopen("midterm.data", "r");

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
        	junk.firstname = malloc(sizeof(junk.firstname));
        	junk.lastname = malloc(sizeof(junk.lastname));
        	fscanf( *stream, "%s %s %li\n", junk.firstname, junk.lastname, &junk.number);
        	free(junk.firstname);
        	free(junk.lastname);
        	numOfContacts++;
        }
	}

	//close the file
	fclose(*stream);

	//returns an integer indicating how many lines are in the file
	return numOfContacts;
}
*/

struct _data *LOAD(FILE *stream, int size)
{ //rewind file, create dynamic array (of size), read data, populate struct dynamic array

	// open file for reading, rewind stream
    stream = fopen("midterm.data", "r");
    rewind(stream);


    //create dynamic array of size
    struct _data *Blackbox;
    Blackbox = calloc(size, sizeof(struct _data));

    //parameters for getline and strtok
    char *lineBuf= NULL;
    char *lineBuf2 = NULL;
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

    	// break up the line on the " " character to get the first name
    	token  = strtok(lineBuf, search);

    	Blackbox[counter].firstname = malloc(strlen(token));
    	strcpy(Blackbox[counter].firstname, token);

    	// gets the last name
    	token = strtok(lineBuf2, search);

    	Blackbox[counter].lastname = malloc(strlen(token));
    	strcpy(Blackbox[counter].lastname, token);

        // get the second half of the line ending at the "\n" character
    	token  = strtok(NULL, "\n");
    	Blackbox[counter].number = atol(token);

    	// get next line and increment counter
    	lineSize = getline(&lineBuf, &lineBufSize, stream);
    	counter++;

    }

    //free and close lineBuf and the file opened during the function
    free(lineBuf);
    lineBuf = NULL;
    free(lineBuf2);
    lineBuf = NULL;
    fclose(stream);

    return Blackbox;

}

void SEARCH(struct _data *Blackbox, char *firstname, char *lastname, int size)
{//gets dynamic array of struct that was passed to it, name being searched for, size of array
 //searches for name in list

 int counter = 0;
 while( counter < size)
 {
     if( (strcmp(Blackbox[counter].firstname, firstname) == 0) &&  (strcmp(Blackbox[counter].lastname, lastname) == 0)) // if the name matches a name in the list
     {
    	 printf("\n*******************************************\n[%s %s] was found at the %i entry.  \n*******************************************\n", firstname, lastname, counter);
        return;
     }
    counter++;
 }

 // if NO matches found in the list
 printf("\n*******************************************\n[%s %s] was not found.  \n*******************************************\n", firstname, lastname);

}

void FREE(struct _data *Blackbox, int size)
{ // frees up all dynamic memory that was allocated. recall how many times calloc or malloc have been called.
 //need to free() multiple times for all of the "name" pointers in the struct (use size)
 // also need to free Blackbox

	for (int i = 0; i < size; i++)
	{
		free(Blackbox[i].firstname);
		free(Blackbox[i].lastname);
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

    // handles case when no command line arguments are provided
    if (argv < 3)
    {
        printf("\n*******************************************\n* You must include a name to search for.  *\n*******************************************\n");
        exit(1);
    }
    else
    {
    	// handles case when a command line argument is provided, searches for argument in the struct array
    	SEARCH(Blackbox, argc[1], argc[2], size);
    }

    FREE(Blackbox, size);

    return 0;

}


