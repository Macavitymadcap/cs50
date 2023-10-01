#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int start, end, years = 0;
    char tar_str[50];

    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    do
    {
        years ++;
        start = start + (start / 3) - (start / 4);
    }
    while (start < end);

    printf("Years: %d\n", years);

    return 0;
}