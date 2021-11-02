#include "helpers.h"
#include <math.h>
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    int count;
    int Gx_sum, Gy_sum;
    int red_Gx, red_Gy, green_Gx, green_Gy, blue_Gx, blue_Gy;

    for (int i = 0, red, green, blue; i < height; i++)
    {
        for (int j = 0, v, w, v_end, w_end; j < width; j++)
        {
            red_Gx = red_Gy = green_Gx = green_Gy = blue_Gx = blue_Gy = 0;
            red = green = blue;
            //Calculating the 3x3 pixel sobel operator matrix multiplication.
            for(int m = -1; m < 2; m++)
            {
                if(i + m < 0 || i + m > height - 1) //if the pixel is at the top or bottom edges then we continue because we cannot get those pixel values since they will outside the boundary
                    continue;

                for (int n = -1; n < 2; n++)
                {
                    if (j + n < 0 || j + n > width - 1) //if the pixel is at the left or right edges then we continue because we cannot get those pixel values since they will outside the boundary
                        continue;

                    //Calculating the sum of vertical and horizontal edges for each color.
                    red_Gx += image[i + m][j + n].rgbtRed * Gx[m+1][n+1];
                    red_Gy += image[i + m][j + n].rgbtRed * Gy[m+1][n+1];
                    green_Gx += image[i + m][j + n].rgbtGreen * Gx[m+1][n+1];
                    green_Gy += image[i + m][j + n].rgbtGreen * Gy[m+1][n+1];
                    blue_Gx += image[i + m][j + n].rgbtBlue * Gx[m+1][n+1];
                    blue_Gy += image[i + m][j + n].rgbtBlue * Gy[m+1][n+1];

                }
            }

            red = (int) sqrt((float) pow(red_Gx, 2) + pow(red_Gy, 2));
            green = (int) sqrt((float) pow(green_Gx, 2) + pow(green_Gy, 2));
            blue = (int) sqrt((float) pow(blue_Gx, 2) + pow(blue_Gy, 2));

            // Capping each color at 255.
            if(red > 255)
                red = 255;
            if(blue > 255)
                blue = 255;
            if(green > 255)
                green = 255;

            //Storing at the 2D temporary array of struct RGBTRIPLE
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;
        }
    }

    //Copying the elements of the temp to the image.
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
