// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));

}

string replace(string word)
{
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        switch (word[i])
        {
        case 'a':
            word[i] = (char) '6';
            break;
        
        case 'e':
            word[i] = (char) '3';
            break;
        
        case 'i':
            word[i] = (char) '1';
            break;
        
        case 'o':
            word[i] = (char) '0';
            break;
        
        default:
            word[i] = (char) word[i];
            break;
        }
    }
     
     return word;
}