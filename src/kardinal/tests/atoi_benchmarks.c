#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int my_atoi(char *);
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
    for (int i = 0; i < 100000000; i++)
        value = my_atoi(string);

    end = (float)clock()/CLOCKS_PER_SEC;

    printf("\nRunning my custom atoi function 100 million times took %ld seconds", end - start);
    
    return 0;
}


int my_atoi(char *string)
{
    int number = 0;

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= 48 && string[i] <= 57) {
            number = number * 10 + (string[i] - 48);
        }
    }
    
    return number;
}
