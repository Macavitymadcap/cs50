#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>

#define MASTER_VISA_LENGTH 16
#define AMEX_LENGTH 15
#define VISA_LENGTH 13

int get_length(long);
int get_checksum(long, int);
void print_invalid(void);
long int get_start_digits(long, int);
bool is_visa(long);
bool is_mastercard(long);
bool is_amex(long);

int main(void) 
{
    long int card = get_long("Number: ");
    int length = get_length(card);
    int checksum = get_checksum(card, length);

    if (checksum % 10 != 0)
    {
        print_invalid();
        return 0;
    }

    long int first_digits = get_start_digits(card, length);

    if (length == MASTER_VISA_LENGTH)
    {
        if (is_visa(first_digits)) 
        {
            printf("VISA\n");
            return 0;
        }
        else if (is_mastercard(first_digits))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            print_invalid();
            return 0;
        }
    }
    else if (length == AMEX_LENGTH)
    {
        if (is_amex(first_digits))
        {
            printf("AMEX\n");
            return 0;
        }
        else
        {
            print_invalid();
            return 0;
        }
    }
    else if (length == VISA_LENGTH)
    {
        if (is_visa(first_digits)) 
        {
            printf("VISA\n");
            return 0;
        }
        else
        {
            print_invalid();
            return 0;
        }
    }
    else
    {
        print_invalid();
    }

    return 0;
}

int get_length(long int number)
{
    int length = 0;
    long cc = number;

    while (cc > 0)
    {
        cc = cc / 10;
        length++;
    }

    return length;
}

int get_checksum(long int card, int length)
{
    long int new_card = card;
    int sum_1 = 0;
    int sum_2 = 0;
    int total;

    for (int i = 1; i <= length; i++)
    {
        if (i % 2 == 0)
        {
            int remainder = (new_card % 10) * 2;

            if (remainder / 10 >= 1)
            {
                sum_1 += remainder / 10;
                sum_1 += remainder % 10;
            }
            else
            {
                sum_1 += remainder;
            }
        }
        else
        {
            sum_2 += new_card % 10;
        }

        new_card /=  10;
    }

    total = sum_1 + sum_2;

    return total;
}

void print_invalid(void)
{
    printf("INVALID\n");
}

long int get_start_digits(long int card, int length)
{
    long int first_digits = card;

    for (int i = 0; i < length - 2; i++)
    {
        first_digits /= 10;
    }

    return first_digits;
}

bool is_visa(long int first_digits)
{
    int visa = 4;
    if (first_digits / 10 == visa) 
    {
        return true;
    }

    return false; 
}

bool is_mastercard(long int first_digits)
{
    bool result = false;
    int mastercard_nums[5] = {51, 52, 53, 54, 54};

    for (int i = 0; i < 5; i++)
    {
        if (first_digits == mastercard_nums[i])
        {
            result = true;
        }
    }

    return result;
}

bool is_amex(long int first_digits)
{
    int amex_nums[2] = {34, 37};

    if (first_digits == amex_nums[0] || first_digits == amex_nums[1])
    {
        return true;
    }

    return false;
}