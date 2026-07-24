/*
    Movie Ticket Discount Calculator
        Description:
         Calculates the best available movie ticket discount based on the customer's age and VIP membership. If multiple discounts apply, only the highest discount is used.
        Author: Aneeshka C. Ramoutar
 */


#include <stdio.h>
#include <string.h>

int main(void) {
    // Declare variables
    int age;
    char vipStatus;
    double ticketPrice;
    double discountedPrice;
    double bestDiscount = 0.0;
    char discountType[20];

    // Define discount percentages
    const double CHILD_DISCOUNT = 0.50;   // 50%
    const double SENIOR_DISCOUNT = 0.30;  // 30%
    const double VIP_DISCOUNT = 0.20;     // 20%

    // Default values
    strcpy(discountType, "No Discount");

    // Get user input
    printf("Enter the ticket price: $");
    scanf("%lf", &ticketPrice);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Are you a VIP member? (Y/N): ");
    scanf(" %c", &vipStatus);

    // Check for child discount
    if (age < 13) {
        bestDiscount = CHILD_DISCOUNT;
        strcpy(discountType, "Child Discount");
    }

    // Check for senior discount
    if (age >= 65 && SENIOR_DISCOUNT > bestDiscount) {
        bestDiscount = SENIOR_DISCOUNT;
        strcpy(discountType, "Senior Discount");
    }

    // Check for VIP discount
    if ((vipStatus == 'Y' || vipStatus == 'y') &&
        VIP_DISCOUNT > bestDiscount) {
        bestDiscount = VIP_DISCOUNT;
        strcpy(discountType, "VIP Discount");
    }

    // Calculate final price
    discountedPrice = ticketPrice * (1.0 - bestDiscount);

    // Display results
    printf("\n----- Ticket Summary -----\n");
    printf("Original Ticket Price: $%.2f\n", ticketPrice);
    printf("Discount Applied: %s (%.0f%%)\n",
           discountType, bestDiscount * 100);
    printf("Final Ticket Price: $%.2f\n", discountedPrice);

    return 0;
}