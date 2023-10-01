// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool upper = false;
    bool lower = false;
    bool number = false;
    bool symbol = false;

    int length = strlen(password);

    for (int i = 0; i < length; i++)
    {
        char character = password[i];
        if (isupper(character))
        {
            upper = true;
        }
        else if (islower(character))
        {
            lower = true;
        }
        else if (isdigit(character))
        {
            number = true;
        }
        else if (ispunct(character))
        {
            symbol = true;
        }  
    }
    
    return upper && lower && number && symbol;
}
