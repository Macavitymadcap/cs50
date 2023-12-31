#include "helpers.h"
#include "math.h"
#include "stdlib.h"
#include "stdbool.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            BYTE average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Return the smallest int out of 255 or a calculated sepia colour
int getMinSepiaValue(float sepiaColour)
{
    return (int) fmin(255, round(sepiaColour));
}

// Return the sepia value of a red pixel
int getSepiaRed(RGBTRIPLE image) 
{
    float sepiaRed = (.393 * image.rgbtRed) + (.769 * image.rgbtGreen) + (.189 * image.rgbtBlue);
    
    return getMinSepiaValue(sepiaRed);
}

// Return the sepia value of a green pixel
int getSepiaGreen(RGBTRIPLE image)
{
    float sepiaGreen = (.349 * image.rgbtRed) + (.686 * image.rgbtGreen) + (.168 * image.rgbtBlue);

    return getMinSepiaValue(sepiaGreen);
}

// Return the sepia value of a blue pixel
int getSepiaBlue(RGBTRIPLE image)
{
    float sepiaBlue = (.272 * image.rgbtRed) + (.534 * image.rgbtGreen) + (.131 * image.rgbtBlue);

    return getMinSepiaValue(sepiaBlue);
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = getSepiaBlue(image[i][j]);
            image[i][j].rgbtGreen = getSepiaGreen(image[i][j]);
            image[i][j].rgbtRed = getSepiaRed(image[i][j]);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int length = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < length; j++)
        {
            int columnIndex = width - j - 1;
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][columnIndex];
            image[i][columnIndex] = temp;
        }
    }

    return;
}

// Copy an image into a pre-allocated 2d array of RGBTRIPLE 
void copyImage(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE copy[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = original[i][j];
        }
    }
}

// Determine whether given value is with boundary
bool withinBoundary(int value, int limit)
{
    return value >= 0 && value <= limit -1;
}

// Return the average value of a pixel as an integer
int getAveragePixel(int total, int count)
{
    return (int)round((double)total / (double)count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    copyImage(height, width, image, copy); 
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count, greenAvg, redAvg, blueAvg;
            count = greenAvg = redAvg = blueAvg = 0;

            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (withinBoundary(k, height) && withinBoundary(l, width))
                    {
                        greenAvg += copy[k][l].rgbtGreen;
                        redAvg += copy[k][l].rgbtRed;
                        blueAvg += copy[k][l].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtBlue = getAveragePixel(blueAvg, count);
            image[i][j].rgbtGreen = getAveragePixel(greenAvg, count);
            image[i][j].rgbtRed = getAveragePixel(redAvg, count);
        }
    }

    return;
}
