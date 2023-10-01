#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string);
int count_words(string);
int count_sentences(string);
int calculate_grade(int, int, int);
void print_grade(int);

int main(void) 
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    int grade = calculate_grade(letters, words, sentences);
    print_grade(grade);
}

int count_letters(string text)
{
    int count = 0, index = 0;
    while (text[index] != '\0')
    {
        char lowercase = tolower(text[index]);

        if (lowercase >= 97 && lowercase <= 122)
        {
            count++;
        }
        index++;
    }

    return count;
}

int count_words(string text)
{
    int count = 0, index = 0;

    while (text[index] != '\0')
    {
        if (text[index] == ' ')
        {
            count++;
        }
        index++;
    }

    return count + 1;
}

int count_sentences(string text)
{
    int count = 0, index = 0;

    while (text[index] != '\0')
    {
        if (text[index] == '.' || text[index] == '?' || text[index] == '!')
        {
            count++;
        }
        index++;
    }

    return count;
}

int calculate_grade(int letters, int words, int sentences)
{
    double L = ((double) letters / (double) words) * 100;
    double S = ((double) sentences / (double) words) * 100;
    double grade = 0.0588 * L - 0.296 * S - 15.8;

    return (int) round(grade);
}

void print_grade(int grade)
{
    if (grade < 1)
    {
        puts("Before Grade 1");
    }
    else if (grade >= 16)
    {
        puts("Grade 16+");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}