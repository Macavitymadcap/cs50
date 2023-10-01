#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define UPPER_A 65
#define LOWER_A 97

void print_error(void);
bool only_digits(string);
char set_char(char, int, int);
char rotate(char, int);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        print_error();
        return 1;
    }

    if (!only_digits(argv[1]))
    {
        print_error();
        return 1;
    }

    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");
    int length = strlen(plaintext);
    char ciphertext[length];

    for (int i = 0; i < length + 1; i++)
    {
        ciphertext[i] = rotate(plaintext[i], key);
    }
    
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

void print_error(void)
{
    printf("Usage: ./caesar key\n");
}

bool only_digits(string argv_1)
{
    int length = strlen(argv_1);
    bool state = false;

    for (size_t i = 0; i < length; i++)
    {
        if (isdigit(argv_1[i]))
        {
            state = true;
        }
        else 
        {
            return false;
        }
    }
    
    return state;
}

char set_char(char character, int char_num, int key)
{
    int char_int = character - char_num;
    char new_char = (char_int + key) % 26;
    new_char += char_num;

    return new_char;
}

char rotate(char character, int key)
{
    char new_char;

    if (!isalpha(character))
    {
        return character;
    }

    if (isupper(character))
    {
        new_char = set_char(character, UPPER_A, key);
    }
    else if (islower(character))
    {
        new_char = set_char(character, LOWER_A, key);
    }

    return new_char;
}