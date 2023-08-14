#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ALPHASIZE 26

int main(int argc, string argv[])
{

    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate key length
    string key = argv[1];
    if (strlen(key) != ALPHASIZE)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Validate key characters
    char substitution[ALPHASIZE] = {0};
    bool used[ALPHASIZE] = {false};
    for (int i = 0; i < ALPHASIZE; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        char c = toupper(key[i]);
        if (used[c - 'A'])
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        used[c - 'A'] = true;
        substitution[i] = c;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

    // Encrypt plaintext with substitution
    printf("ciphertext: ");
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char c = plaintext[i];
        if (isupper(c))
        {
            printf("%c", substitution[c - 'A']);
        }
        else if (islower(c))
        {
            printf("%c", tolower(substitution[c - 'a']));
        }
        else
        {
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}
