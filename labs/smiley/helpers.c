#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    BYTE black = 0x00;

    RGBTRIPLE purple;
    purple.rgbtRed = 0xa0;
    purple.rgbtGreen = 0x02;
    purple.rgbtBlue = 0xf0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            if (image[i][j].rgbtBlue == black && image[i][j].rgbtGreen == black && image[i][j].rgbtRed == black)
            {
                image[i][j].rgbtRed = purple.rgbtRed;
                image[i][j].rgbtGreen = purple.rgbtGreen;
                image[i][j].rgbtBlue = purple.rgbtBlue;
            }
        }
    }
}
