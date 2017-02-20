#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int my_atoi(char *);
// compile using
// gcc atoi_benchmarks.c -lm
int main()
{
    int value;

    char *string = "5555555";

    time_t start, end;

    start = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0; i <= 100000000; i++)
        value = atoi(string);
    
    end = (float)clock()/CLOCKS_PER_SEC;

    printf("Running the inbuilt atoi function 100 million times took %ld seconds", end - start);

    start = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0; i <= 100000000; i++)
        value = my_atoi(string);

    end = (float)clock()/CLOCKS_PER_SEC;

    printf("\nRunning my custom atoi function 100 million times took %ld seconds", end - start);

    printf("\n%d", value);
    return 0;
}


int my_atoi(char *string)
{
    int length = strlen(string);
    int length_copy = length, number = 0;


    // we can have an array with the powers of 10 as an improvement
    // as well. This way we don't ahve to find out the powers again
    // and again.

    for (int i = 0; i < length; i++)
    {
        if (string[i] >= 48 && string[i] <= 57) {
            length_copy--;
            number += ((int)pow(10, length_copy)) * string[i];
        }
    }
    
    return number;
}
