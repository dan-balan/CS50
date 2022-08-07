#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "helpers.h"

// function prototyping
int colAvg2(int k, int m, int height, int width, RGBTRIPLE image[height][width], char color);
bool pixelOnEdgeValid(int i, int j, int height, int width);
int colEdgAvg2(int k, int m, int height, int width, RGBTRIPLE image[height][width], char color, int arrayGx[3][3]);

// Gx & Gy kernels
int Gxgrid[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int Gygrid[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0;  i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int greyAverage = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = greyAverage;
            image[i][j].rgbtGreen = greyAverage;
            image[i][j].rgbtBlue = greyAverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // use of a buffer
    RGBTRIPLE buffer;
    for (int i = 0;  i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // 255, 0, 0
            // 0, 0, 255
            buffer.rgbtRed = image[i][j].rgbtRed;
            buffer.rgbtGreen = image[i][j].rgbtGreen;
            buffer.rgbtBlue = image[i][j].rgbtBlue;

            // swap the pixel to opposed array side
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = buffer.rgbtRed;
            image[i][width - 1 - j].rgbtGreen = buffer.rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = buffer.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for a new image -go trough original pixel data
    RGBTRIPLE(*imageRaw)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        fprintf(stderr, "Not enough memory to store image.\n");
        // Free memory for image
        free(image);
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageRaw[i][j].rgbtRed = image[i][j].rgbtRed;
            imageRaw[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageRaw[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0;  i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // red average
            int redAverage = colAvg2(i, j, height, width, imageRaw, 'r');
            //green average
            int greenAverage = colAvg2(i, j, height, width, imageRaw, 'g');
            //blue average
            int blueAverage = colAvg2(i, j, height, width, imageRaw, 'b');

            image[i][j].rgbtRed = redAverage;
            image[i][j].rgbtGreen = greenAverage;
            image[i][j].rgbtBlue = blueAverage;
        }
    }
    free(imageRaw);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // <<<<Allocate memory for a new image -go trough original pixel data>>>>
    RGBTRIPLE(*imageRaw)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        fprintf(stderr, "Not enough memory to store image.\n");
        // Free memory for image
        free(image);
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageRaw[i][j].rgbtRed = image[i][j].rgbtRed;
            imageRaw[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageRaw[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    ///////////</h>//////////
    for (int i = 0;  i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // apply the Gx & Gy grid-box
            //
            int redGx = colEdgAvg2(i, j, height, width, imageRaw, 'r', Gxgrid);
            int redGy = colEdgAvg2(i, j, height, width, imageRaw, 'r', Gygrid);
            int redEdge = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));

            int greenGx = colEdgAvg2(i, j, height, width, imageRaw, 'g', Gxgrid);
            int greenGy = colEdgAvg2(i, j, height, width, imageRaw, 'g', Gygrid);
            int greenEdge = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));

            int blueGx = colEdgAvg2(i, j, height, width, imageRaw, 'b', Gxgrid);
            int blueGy = colEdgAvg2(i, j, height, width, imageRaw, 'b', Gygrid);
            int blueEdge = round(sqrt(pow(blueGx, 2) + pow(blueGy, 2)));

            // verify that the chanel value < 255
            if (redEdge > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = redEdge;
            }
            // green chanel collor
            if (greenEdge > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = greenEdge;
            }
            // blue chanel collor
            if (blueEdge > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blueEdge;
            }
        }
    }
    free(imageRaw);
    return;
}


// average amount of R/G/B collor
// based on blur-grid matrix
int colAvg2(int k, int m, int height, int width, RGBTRIPLE image[height][width], char color)
{
    int sum = 0;
    int counter = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            switch (color)
            {
                case 'r':
                    if (pixelOnEdgeValid(k + i, m + j, height, width))
                    {
                        sum += image[k + i][m + j].rgbtRed;
                        counter += 1;
                    }
                    break;

                case 'g':
                    if (pixelOnEdgeValid(k + i, m + j, height, width))
                    {
                        sum += image[k + i][m + j].rgbtGreen;
                        counter += 1;
                    }
                    break;

                case 'b':
                    if (pixelOnEdgeValid(k + i, m + j, height, width))
                    {
                        sum += image[k + i][m + j].rgbtBlue;
                        counter += 1;
                    }
                    break;
            }
        }
    }
    return round(sum / (float)counter);
}

//check if pixel is in boundaries
bool pixelOnEdgeValid(int i, int j, int height, int width)
{
    if ((i < 0) || (j < 0) || (i >= height) || (j >= width))
    {
        return false;
    }
    return true;
}

// average amount of R/G/B collor
// based on blur-grid matrix
int colEdgAvg2(int k, int m, int height, int width, RGBTRIPLE image[height][width], char color, int arrayGx[3][3])
{
    int sum = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            switch (color)
            {
                case 'r':
                    if (pixelOnEdgeValid(k + i, m + j, height, width))
                    {
                        sum += arrayGx[i + 1][j + 1] * image[k + i][m + j].rgbtRed;
                    }
                    break;

                case 'g':
                    if (pixelOnEdgeValid(k + i, m + j, height, width))
                    {
                        sum += arrayGx[i + 1][j + 1] * image[k + i][m + j].rgbtGreen;
                    }
                    break;

                case 'b':
                    if (pixelOnEdgeValid(k + i, m + j, height, width))
                    {
                        sum += arrayGx[i + 1][j + 1] * image[k + i][m + j].rgbtBlue;
                    }
                    break;
            }
        }
    }
    return sum;
}
