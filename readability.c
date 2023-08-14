#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string s);
int count_sentences(string s);
int count_words(string s);

int main(void)
{
    string s = get_string("Text: ");

    // Count letters, words, and sentences
    int letters = count_letters(s);
    int sentences = count_sentences(s);
    int words = count_words(s);

    // Plug values into Coleman-Liau formula
    int coleman = round(0.0588 * (100.0 * letters / words)
                        - 0.296 * (100.0 * sentences / words)
                        - 15.8);

    // Print appropriate grade level
    if (coleman >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (coleman < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", coleman);
    }
}

int count_letters(string s)
{
    int count = 0;
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        // Count all alpahbetic characters
        if (isalpha(s[i]))
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string s)
{
    int count = 0;
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        // Count end-of-sentence punctuation
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count++;
        }
    }
    return count;
}

int count_words(string s)
{
    int count = 0;
    bool new_word = true;
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        // Mark next non-space character as a new word
        if (s[i] == ' ')
        {
            new_word = true;
            continue;
        }
        if (new_word)
        {
            count++;
            new_word = false;
        }
    }
    return count;
}
