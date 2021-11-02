#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>

bool repeated_characters(string key, int n);
char plain_to_cipher_char(string key, char cipher_char, bool uppercase);

int main(int argc, string argv[])
{
    // checks if there are 2 command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //checks if there are 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int n = strlen(argv[1]);
    string key = argv[1];
    char lower_char;
    //checks if the argument contains 26 alphabetical letters and converts them to lowercase. Converting to lowercase because it is much easier to have all the text in one case so that
    // can index the alphabets to a range between 0 and 25.
    for (int i = 0; i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain 26 letters.\n");
            return 1;
        }
        else
        {
            if (isupper(key[i]))
            {
                // lower_char = key[i] - 'A';
                // lower_char = 'a' + lower_char;
                // key[i] = lower_char;
                key[i] = tolower(key[i]);
            }
        }
    }


    // Checks if there are repeated characters of the alphabets
    if (repeated_characters(key, n))
    {
        printf("key contains repeated characters\n");
        return 1;
    }

    string plain_text = get_string("plain_text: ");
    int plain_length = strlen(plain_text);
    char cipher_char;
    printf("lower_key: %s\n", key);


    for (int i = 0; i < plain_length; i++)
    {
        if (!isalpha(plain_text[i])) //checks if the characters are alphabetical.
        {
            continue;
        }
        //if the character is an uppercase, need to make sure that we convert it back to uppercase before storing it in the plain_text string.
        if (isupper(plain_text[i]))
        {
            plain_text[i] = tolower(plain_text[i]);
            //function converts the plain_text character to the cipher_text character.
            plain_text[i] = plain_to_cipher_char(key, plain_text[i], true);
        }
        else
        {
            //function converts the plain_text character to the cipher_text character.
            plain_text[i] = plain_to_cipher_char(key, plain_text[i], false);
        }

    }

    printf("ciphertext: %s\n", plain_text);
}


// Checks for repeated characters using a counter, when the counter hits 2 then key provided by the user has a repeated character.
bool repeated_characters(string key, int n)
{
    char check;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        check = key[i];

        for (int j = 0; j < n; j++)
        {
            if (check == key[j])
            {
                count++;
            }
            if (count == 2)
            {
                return true;
            }
        }
        count = 0;
    }

    return false;


}

// converting the plain_text character to the cipher character by first obtaining the range between 0 and 25 and using that value to obtain the character from the key.
char plain_to_cipher_char(string key, char cipher_char, bool uppercase)
{
    cipher_char = cipher_char - 'a';
    cipher_char = key[(int)(cipher_char)];
    if (uppercase)
    {
        cipher_char = cipher_char - 'a';
        cipher_char = cipher_char + 'A';
    }

    return cipher_char;
}