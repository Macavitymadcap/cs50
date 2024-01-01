#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

bool isStartOfJpeg(BYTE buffer[BLOCK_SIZE]);

void closeImageIfNotNull(FILE *image);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");

        return 1;
    }

    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        printf("Could not open file %s\n", argv[1]);

        return 2;
    }

    int count = 0;
    FILE *image = NULL;   
    char *nameBuffer = malloc(8 * sizeof(char));

    if (nameBuffer == NULL)
    {
        fclose(image);
        printf("Memory allocation error\n");

        return 3;
    }

    BYTE imageBuffer[BLOCK_SIZE];
    
    while(fread(imageBuffer, sizeof(BYTE), BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        if (isStartOfJpeg(imageBuffer))
        {
            closeImageIfNotNull(image);

            sprintf(nameBuffer, "%03i.jpg", count);
            image = fopen(nameBuffer, "w");

            if (image == NULL)
            {
                free(nameBuffer);
                fclose(infile);
                printf("Error writing file\n");

                return 4;
            }

            count++;
        }

        if (image != NULL)
        {
            fwrite(imageBuffer, sizeof(BYTE), BLOCK_SIZE, image);
        }
    }

    closeImageIfNotNull(image);
    
    fclose(infile);
    free(nameBuffer);

    return 0;
}

// Determine whether buffer of bytes is the beginning of a JPEG
bool isStartOfJpeg(BYTE buffer[BLOCK_SIZE])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}

// Close given image file if it is not NULL
void closeImageIfNotNull(FILE *image)
{
    if (image != NULL)
    {
        fclose(image);
    }
}