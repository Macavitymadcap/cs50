#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Enter message > ");
    int count = strlen(message);
    for (size_t i = 0; i < count; i++)
    {
        int char_num = message[i];
        int eight_bit[BITS_IN_BYTE];
        
        for (int j = BITS_IN_BYTE - 1; j > 0; j--)
        {
            eight_bit[j] = char_num % 2;
            char_num /= 2;
        }

        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            print_bulb(eight_bit[k]);
        }

        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

