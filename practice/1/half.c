// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

float half(float bill, float tax, int tip)
{
    double tip_percentage = tip / 100.0;
    double tax_precentage = tax / 100.0;
    double bill_tax = bill + (bill * tax_precentage);
    double total_tip = bill_tax * tip_percentage;
    float total_bill = bill_tax + total_tip;

    return total_bill / 2.00;
}
