#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char name[256];

    string name = get_string("Enter name: ");
    printf("hello, %s\n", name);
}