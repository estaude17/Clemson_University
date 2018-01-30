#include <stdio.h>

int swapper(int array[], int count)
{
    int i, j, temp;
    int swaps = 0;
    
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
                swaps++; 
            }
        }
    }
return (swaps);
}

int main (void)
{
    int array[100];
    int counter = 0;
    int input;
    int s;
    int i = 0;
    
    while(counter < 100 && scanf("%d", &input) != EOF)
{
    array[counter] = input;
    counter++;
}

    while(i < counter)
{
    s = swapper(array, counter);
    printf("%d\n", s);
    i++; 
}
  
    i = 0;
    while(i < counter)
{
    swapper(array, counter);
    printf("%d\n", array[i]);  
    i++;
}
    
return 0;
}
