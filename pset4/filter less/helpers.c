#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sameValue;
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sameValue = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = sameValue;
            image[i][j].rgbtGreen = sameValue;
            image[i][j].rgbtRed = sameValue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaBlue, sepiaGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle;
    RGBTRIPLE temp;
    if (width % 2 == 0) // if even number ex: 8, the middle is 4 but we need to include the 4th element tooo
    {
        middle = (width / 2) + 1;
    }
    else
    {
        middle = width / 2;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width-1; j < middle; j++, k--)
        {
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int count;

    for(int i = 0; i < height; i++)
    {
        for (int j = 0, red, green, blue; j < width; j++)
        {
            count = 0;
            red = green = blue = 0;

            // Going from -1 to 1 and checking if current element exceeds the boundaries
            for(int m = -1; m < 2; m++)
            {
                if(i + m < 0 || i + m > height - 1) //if the pixel is at the top or bottom edges then we continue because we cannot get those pixel values since they will outside the boundary
                    continue;

                for (int n = -1; n < 2; n++)
                {
                    if(j + n < 0 || j + n > width - 1) //if the pixel is at the left or right edges then we continue because we cannot get those pixel values since they will outside the boundary
                        continue;

                    count ++;
                    red += image[i + m][j + n].rgbtRed;
                    green += image[i + m][j + n].rgbtGreen;
                    blue += image[i + m][j + n].rgbtBlue;

                }

            }

            temp[i][j].rgbtRed = red / count;
            temp[i][j].rgbtGreen = green / count;
            temp[i][j].rgbtBlue = blue / count;

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
