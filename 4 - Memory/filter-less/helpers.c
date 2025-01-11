#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiared = round(0.393*image[i][j].rgbtRed + 0.769*image[i][j].rgbtGreen + 0.189*image[i][j].rgbtBlue);
            if (sepiared > 255) sepiared = 255;

            int sepiagreen = round(0.349*image[i][j].rgbtRed + 0.686*image[i][j].rgbtGreen + 0.168*image[i][j].rgbtBlue);
            if (sepiagreen > 255) sepiagreen = 255;

            int sepiablue = round(0.272*image[i][j].rgbtRed + 0.534*image[i][j].rgbtGreen + 0.131*image[i][j].rgbtBlue);
            if (sepiablue > 255) sepiablue = 255;

            image[i][j].rgbtRed = sepiared;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtBlue = sepiablue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int ji = 0;
        int jf = width - 1;
        while (ji < jf)
        {
            int temp;

            temp = image[i][ji].rgbtRed;
            image[i][ji].rgbtRed = image[i][jf].rgbtRed;
            image[i][jf].rgbtRed = temp;

            temp = image[i][ji].rgbtGreen;
            image[i][ji].rgbtGreen = image[i][jf].rgbtGreen;
            image[i][jf].rgbtGreen = temp;

            temp = image[i][ji].rgbtBlue;
            image[i][ji].rgbtBlue = image[i][jf].rgbtBlue;
            image[i][jf].rgbtBlue = temp;

            ji++;
            jf--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            double sumred = 0;
            double sumblue = 0;
            double sumgreen = 0;
            double count = 0;

            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = col - 1; j <= col + 1; j++)
                {
                    if (i >= 0 && j >= 0 && i < height && j < width)
                    {
                        sumred += image[i][j].rgbtRed;
                        sumblue += image[i][j].rgbtBlue;
                        sumgreen += image[i][j].rgbtGreen;
                        count++;
                    }
                }
            }

            copy[row][col].rgbtRed = round(sumred/count);
            copy[row][col].rgbtBlue = round(sumblue/count);
            copy[row][col].rgbtGreen = round(sumgreen/count);
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col].rgbtRed = copy[row][col].rgbtRed;
            image[row][col].rgbtBlue = copy[row][col].rgbtBlue;
            image[row][col].rgbtGreen = copy[row][col].rgbtGreen;
        }
    }
    return;
}
