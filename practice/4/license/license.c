#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int LICENSE_PLATE_LENGTH = 7;
int NUMBER_OF_PLATES = 8;

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char *buffer = malloc(LICENSE_PLATE_LENGTH);

    // Create a pointer to an array to store plate numbers
    char (*plates)[LICENSE_PLATE_LENGTH] = malloc(NUMBER_OF_PLATES * sizeof(buffer)); 

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int idx = 0;

    while (fread(buffer, 1, LICENSE_PLATE_LENGTH, infile) == LICENSE_PLATE_LENGTH)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }

    // Feee memory of the buffer and close the file
    free(buffer);
    fclose(infile);

    for (int i = 0; i < NUMBER_OF_PLATES; i++)
    {
        printf("%s\n", plates[i]);
    }

    // Free memory of array 
    free(plates);

    return 0;
}
