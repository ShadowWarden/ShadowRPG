#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows = 2000, cols = 2000;
    for(int i = 0; i < 2000; i++){
        for(int j = 0; j < 2000; j++)
            printf("%d",((int)((rand() % 5) + 1))); // generating numbers between 1 and 5
        printf("\n");
   }

   return 0;
}