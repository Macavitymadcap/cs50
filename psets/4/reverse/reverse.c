#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input output\n");

        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Unable to open file %s\n", argv[1]);
        fclose(input);
        
        return 1;
    }  

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);  

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("File %s is not wav format\n", argv[1]);
        fclose(input);

        return 1;
    } 

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Unable to write to file %s\n", argv[2]);
        fclose(input);
        fclose(output);

        return 1;
    } 

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output); 

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE buffer[block_size];
    int start_offset = 0 -block_size;
    int end_offset = sizeof(header) - block_size;
    int jump_offset = 0 - (block_size * 2);

    for (fseek(input, start_offset, SEEK_END); ftell(input) > end_offset; fseek(input, jump_offset, SEEK_CUR))
    {
        fread(&buffer, block_size, 1, input);
        fwrite(&buffer, block_size, 1, output);
    }

    // Tidy up allocated memory and opened files
    fclose(input);
    fclose(output);

    return 0;
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    
    return 0;
}

int get_block_size(WAVHEADER header)
{
    return header.numChannels * (header.bitsPerSample / sizeof(BYTE));
}