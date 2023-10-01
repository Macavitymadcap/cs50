#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS 26
#define UPPER_A 65
#define LOWER_A 97

bool wrong_count(int);
bool wrong_length(string);
bool not_alpha(string);
bool has_repeats(string);
int is_invalid(int, string);
void print_error(int);
char get_upper(char, string);
char get_lower(char, string);
char encipher(char, string);

int main(int argc, string argv[]) 
{
    int validity = is_invalid(argc, argv[1]);
    if (validity != 0)
    {
        print_error(validity);
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    int length = strlen(plaintext);
    char ciphertext[length];

    for (int i = 0; i < length + 1; i++)
    {
        ciphertext[i] = encipher(plaintext[i], argv[1]);
    }
    
    printf("ciphertext: %s\n", ciphertext);

    return 0;

}

bool wrong_count(int count)
{
    if (count != 2)
    {
        return true;
    }
    return false;
}

bool wrong_length(string key)
{
    if (strlen(key) != NUM_LETTERS)
    {
        return true;
    }

    return false;
}

bool not_alpha(string key)
{
    bool state = false;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (isdigit(key[i]))
        {
            state = true;
        }
    }

    return state;
}

bool has_repeats(string key)
{
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        for (int j = i + 1; j < NUM_LETTERS; j++)
        {
            if (key[i] == key[j])
            {
                return true;
            }
        }
    }
    return false;
}

int is_invalid(int count, string key)
{
    if (wrong_count(count))
    {
        return 1;
    }

    if (wrong_length(key))
    {
        return 2;
    }

    if (not_alpha(key))
    {
        return 3;
    }

    if (has_repeats(key))
    {
        return 4;
    }

    return 0;
}

void print_error(int errorcode)
{
    switch (errorcode)
    {
    case 1:
        printf("Usage: ./substitution key\n");
        break;

    case 2:
        printf("Key must contain 26 characters.\n");
        break;

    case 3:
        printf("Key must only contain alphabetic characters.\n");
        break;

    case 4:
        printf("Key must not contain repeating characters.\n");
        break;
    
    default:
        break;
    }
}

char get_upper(char character, string key)
{
    char new_char;
    int char_int = character - UPPER_A;

    if (islower(key[char_int]))
    {
        new_char = toupper(key[char_int]);
    }
    else
    {
        new_char = key[char_int];
    }

    return new_char;
}

char get_lower(char character, string key)
{
    char new_char;
    int char_int = character - LOWER_A;

    if (isupper(key[char_int]))
    {
        new_char = tolower(key[char_int]);
    }
    else
    {
        new_char = key[char_int];
    }

    return new_char;
}

char encipher(char character, string key)
{
    char new_char;

    if (!isalpha(character))
    {
        return character;
    }

    if (isupper(character))
    {
        new_char = get_upper(character, key);
    }
    else if (islower(character))
    {
        new_char = get_lower(character, key);
    }

    return new_char;
}