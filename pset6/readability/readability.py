from cs50 import get_string
# from math import round

def main():
    text = get_string("Text: ")
    letter_count = sentence_count = 0
    word_count = 1
    for i in text:

        if (i.isupper() or i.islower()):
            letter_count += 1

        elif (i.isspace()):
            word_count += 1

        elif(i == '.' or i == '?' or i == '!'):
            sentence_count += 1

    letters_per100 = (letter_count*100) / word_count
    sentences_per100 = (sentence_count*100) / word_count

    index = round(0.0588 * letters_per100 - 0.296 * sentences_per100 - 15.8)

    if(index < 1):
        print("Before Grade 1")
    elif(index >= 16):
        print("Grade 16+")
    else:
        print(f"Grade {index}")

main()


