#include <math.h>

#include "helpers.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            // Compute sum of values of surrounding pixels
            for (int row = MAX(0, i - 1); row <= MIN(height - 1, i + 1); row++)
            {
                for (int col = MAX(0, j - 1); col <= MIN(width - 1, j + 1); col++)
                {
                    count++;

                    red += image[row][col].rgbtRed;
                    green += image[row][col].rgbtGreen;
                    blue += image[row][col].rgbtBlue;
                }
            }

            // Set new pixel value
            new_image[i][j].rgbtRed = round((float) red / count);
            new_image[i][j].rgbtGreen = round((float) green / count);
            new_image[i][j].rgbtBlue = round((float) blue / count);
        }
    }

    // Replace existing image with new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            RGBTRIPLE pixel = image[i][j];
            int avg = round((float) (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3);

            // Update pixel values
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all rows
    for (int i = 0; i < height; i++)
    {
        // Swap pixels in first half of row with second half
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    // Kernels for Sobel edge filtering
    int xkernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int ykernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create variables for gradient in each direction
            int xred = 0, yred = 0, xgreen = 0, ygreen = 0, xblue = 0, yblue = 0;

            // Loop over surrounding pixels
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    // Set the horizontal and vertical edge adjustments
                    int xadj = xkernel[x + 1][y + 1];
                    int yadj = ykernel[x + 1][y + 1];

                    // If pixel is out of bounds, use all black
                    if (i + x < height && i + x >= 0 && j + y < width && j + y >= 0)
                    {
                        RGBTRIPLE pixel = image[i + x][j + y];

                        // Update pixel values
                        xred += xadj * pixel.rgbtRed;
                        xgreen += xadj * pixel.rgbtGreen;
                        xblue += xadj * pixel.rgbtBlue;
                        yred += yadj * pixel.rgbtRed;
                        ygreen += yadj * pixel.rgbtGreen;
                        yblue += yadj * pixel.rgbtBlue;
                    }
                }
            }

            // Calculate new RGB values using Sobel formula
            int red = round(sqrt((xred * xred) + (yred * yred)));
            int green = round(sqrt((xgreen * xgreen) + (ygreen * ygreen)));
            int blue = round(sqrt((xblue * xblue) + (yblue * yblue)));

            // Handle out of range calculations
            red = (red > 255) ? 255 : red;
            green = (green > 255) ? 255 : green;
            blue = (blue > 255) ? 255 : blue;

            // Update new image
            new_image[i][j].rgbtRed = red;
            new_image[i][j].rgbtGreen = green;
            new_image[i][j].rgbtBlue = blue;

        }
    }

    // Replace image with new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}

