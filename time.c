#include <stdio.h>
#include <time.h>

int main() {
    int year, currentYear, numYears;

    printf("Enter the year: ");
    scanf("%d", &year);

    time_t now = time(NULL); // Get the current time
    struct tm *t = localtime(&now); // Convert to a struct with local time information
    currentYear = t->tm_year + 1900; // Get the current year from the struct

    numYears = currentYear - year; // Calculate the number of years

    printf("Number of years completed: %d\n", numYears);

    return 0;
}
