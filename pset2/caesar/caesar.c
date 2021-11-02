#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, string argv[])
{
    //Checks if there are 2 arguments provided.
    if (argc != 2)
    {
        printf("Please provide 1 command-line argument as an integer for the k value\n");
        printf("Usage: ./caesar key\n");
        return 1;
    }



    string k_value = argv[1];
    int n = strlen(k_value);
    char c;

    //checks if the argument contains all digits.
    for (int i = 0; i < n; i++)
    {
        c = k_value[i];
        // printf("%c\n", c);
        if (!isdigit(c))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]); //converting char to int


    string plain_text = get_string("plaintext: ");
    printf("%s\n", plain_text);
    n = strlen(plain_text);
    char UPPERCASE = 'A';
    char LOWERCASE = 'a';
    char cipher_letter;
    char plain_char;
    for (int i = 0; i < n; i++)
    {
        plain_char = plain_text[i];
        if (isalpha(plain_char))
        {
            if (isupper(plain_char))
            {
                cipher_letter = plain_char - UPPERCASE; // converting ASCII to aplhabetical index
                cipher_letter = (cipher_letter + k) % 26; // Shift alphabetical index using formula
                plain_text[i] = cipher_letter + UPPERCASE; // Convert result back to ASCII
            }
            else
            {
                cipher_letter = plain_char - LOWERCASE;
                cipher_letter = (cipher_letter + k) % 26;
                plain_text[i] = cipher_letter + LOWERCASE;
            }
        }
        else
        {
            continue;
        }
    }

    printf("ciphertext: %s\n", plain_text);

    // char text = 'Y';
    // printf("text: %i\n", text);
    // text = text - UPPERCASE;
    // printf("text: %i\n", text);
    // char c_i = (text + 3) % 26;
    // printf("c_i: %i\n", c_i);
    // c_i += UPPERCASE;
    // printf("New: %c, integer_value: %i\n", c_i,c_i);



}