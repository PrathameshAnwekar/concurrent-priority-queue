#include <stdlib.h>
#include <stdio.h>

int readData(int numbers[]);

int MAX_NUMBERS = 100;

int main(int argc, char *argv[])
{
    int numbers[MAX_NUMBERS];
    int count = readData(numbers);

    return 0;
}

int readData(int numbers[])
{
    FILE *fp;

    int count = 0;
    int number = 0;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    while (fscanf(fp, "%d", &number) != EOF)
    {
        // Store the integer in the array
        if (count >= MAX_NUMBERS)
        {
            printf("Too many numbers in file\n");
            return 1;
        }
        numbers[count] = number;
        count++;
    }

    fclose(fp);

    // Print the contents of the array
    printf("The integers are: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return count;
}