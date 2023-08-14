#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for pyramids' height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // iterate over pyramid's rows
    for (int i = 0; i < height; i++)
    {
        // number of spaces to print
        int spaces = height - 1 - i;

        // print spaces
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        // print lefthand pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // print spaces between pyramids
        printf("  ");

        // print righthand pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // print newline
        printf("\n");
    }
}
