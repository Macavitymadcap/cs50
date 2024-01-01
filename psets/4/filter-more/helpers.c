#include "helpers.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    copyImage(height, width, image, copy); 

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

// Determine whether the given value is outside of the boundary
bool outsideBoundary(int value, int limit)
{
    return value < 0 || value > limit - 1;
}

// Return the lowest of either the computed Sobel value or 255
int getSobelValue(int colourX, int colourY)
{
    double sobelValue = round(sqrt(pow(colourX, 2) + pow(colourY, 2)));

    return (int)fmin(sobelValue, 255);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    copyImage(height, width, image, copy);

    int gXMatrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gYMatrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blueX, greenX, redX, blueY, greenY, redY;
            blueX = greenX = redX = blueY = greenY = redY = 0;

            for (int row = -1; row < 2; row++)
            {
                for (int column = -1; column < 2; column++)
                {
                    bool blackPixel = outsideBoundary(i + row, height) || outsideBoundary(j + column, width);
                    if (blackPixel)
                    {
                        continue;
                    }
                    
                    int copyRow = i + row, copyColumn = j + column;
                    int gRow = row + 1, gColumn = column + 1;

                    blueX += copy[copyRow][copyColumn].rgbtBlue * gXMatrix[gRow][gColumn];
                    greenX += copy[copyRow][copyColumn].rgbtGreen * gXMatrix[gRow][gColumn];
                    redX += copy[copyRow][copyColumn].rgbtRed * gXMatrix[gRow][gColumn];

                    blueY += copy[copyRow][copyColumn].rgbtBlue * gYMatrix[gRow][gColumn];
                    greenY += copy[copyRow][copyColumn].rgbtGreen * gYMatrix[gRow][gColumn];
                    redY += copy[copyRow][copyColumn].rgbtRed * gYMatrix[gRow][gColumn];
                }
            }

            image[i][j].rgbtBlue = getSobelValue(blueX, blueY);
            image[i][j].rgbtGreen = getSobelValue(greenX, greenY);
            image[i][j].rgbtRed = getSobelValue(redX, redY);
        }
    }

    return;
}
