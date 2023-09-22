/*
9/22/2023 --> creates a dynamic struct array. 
The data file contents look like:

Bob 90
Sue 50
Blaire 100
James 77
Keanu 80
Harry 55

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct classData {
    char name[20];
    int score;
}*class, junk;

int main()
{
    struct classData junk;
    FILE *data;
    data = fopen("data.txt", "r");
    if (data==NULL)
    {
        printf("%s", "file not found");
    }
    
    int counter = 0;
    
    while (fscanf(data, "%s %i\n", junk.name, &junk.score) != EOF)
    {
        counter++;
    }
    
    printf("%d\n", counter);
    rewind(data);
    
    //struct classData class;
    class = (struct classData*) calloc(counter, sizeof(struct classData));
    
    for (int x = 0; x < counter; x++)
    {
        fscanf(data, "%s %i\n", class[x].name, &class[x].score);
    }
    fclose(data);
    
    for (int x = 0; x < counter; x++)
    {
        printf("%s %i\n", class[x].name, class[x].score);
    }

    return 0;
}
