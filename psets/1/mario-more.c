#include <stdio.h>
#include <cs50.h>

void print_char(char [], int);

int main(void) 
{
    int height = 0;
    
    do 
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    for (int line = 1; line < height + 1; line++)
    {
        int space = height - line;

        print_char(" ", space);
        print_char("#", line);
        printf(" ");
        print_char("#", line);
        print_char(" ", space);
        printf("\n");
    }
    

    return 0;
}

void print_char(char symbol[], int times)
{
    for (int i = 0; i < times; i++)
        {
            printf("%s", symbol);
        }
}
