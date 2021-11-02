#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<cs50.h>

int main(void)
{
    string text;
    text = get_string("Text: ");

    // count letters
    int n = strlen(text);
    int letter_count = 0; //checks for uppercase and lowercase characters
    int word_count = 1; //counting the number of space, so to get the word count need to add 1.
    int sentence_count = 0; //checks for sentences including characters .!?

    for (int i = 0; i < n; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letter_count++;

        }
        else if (isspace(text[i]))
        {
            word_count++;

        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence_count++;

        }

    }

    printf("Letters: %i\n", letter_count);
    printf("Words: %i\n", word_count);
    printf("Sentences: %i\n", sentence_count);

    //Converting the letters and sentences to per letters per 100 and sentences per 100
    float letters_per100 = (float)(letter_count * 100) / (float) word_count;
    float sentences_per100 = (float)(sentence_count * 100) / (float) word_count;

    printf("lettersper100 = %.2f\n", letters_per100);
    printf("sentencesper100 = %.2f\n", sentences_per100);

    // Coleman-Liau index
    int index = round(0.0588 * letters_per100 - 0.296 * sentences_per100 - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("GRADE %i\n", index);
    }

}