#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHASIZE 26

char encrypt(char letter, char base, int key);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Ensure key is non-negative and contains only digits
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    if (key < 0)
    {
        printf("Key must be a non-negative integer.\n");
        return 1;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

    // Encrypt plaintext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", encrypt(plaintext[i], 'A', key));
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", encrypt(plaintext[i], 'a', key));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}

// Encrypts a character using the caesar cipher formula
char encrypt(char letter, char base, int key)
{
    return (letter - base + key) % ALPHASIZE + base;
}
