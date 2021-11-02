#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 4;
    }

    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        fprintf(stderr, "Cannot open for reading\n");
        return 1;
    }

    BYTE* images = malloc(sizeof(BYTE) * 512);
    if(images == NULL)
    {
        fprintf(stderr, "Cannot assign memory\n");
        return 1;
    }
    int counter = 0;

    //Creating a char array to store the filename that will be used to open and store the bytes of memory.
    char buffer[13];

    //Creating a File pointer that will be reused for every jpeg image.
    FILE *img = NULL;

    while(fread(images, sizeof(BYTE), 512, file) != 0) //returns the # of items read so when it reaches 0 it means that there are no more 512 block bytes to read.
    {
        //Start of new jpeg header file
        if(images[0] == 0xff && images[1] == 0xd8 && images[2] == 0xff && (images[3] & 0xf0) == 0xe0)
        {
            //Just for the first jpeg because there is no previous file to close at iteration 0.
            if(counter == 0)
            {
                sprintf(buffer, "%03i.jpg", counter);//prints the formatted string to the char array/string  buffer
                img = fopen(buffer,"w"); //opens the file with the mode to write
                counter++;
            }
            else
            {
                //For all the other jpeg files we first need to close the previous jpeg file and then open a new one reusing the same file pointer.
                fclose(img);
                sprintf(buffer, "%03i.jpg", counter);
                img = fopen(buffer, "w");
                counter++;
            }

        }
        //As long as the file pointer img returns an address means that we have an open file to write.
        if(img != NULL)
        {
            fwrite(images, sizeof(BYTE), 512, img); //reading from (address of first byte of memory) images array and storing it at the file pointer img
        }

    }
    //freeing the malloc memory from the heap.
    free(images);
    printf("Done!\n");
}
