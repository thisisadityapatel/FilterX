#include "helpers.h"
#include<math.h>
#include<cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loops to move throught each element in the matrix
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int avg;
            float blue, green, red;
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;

            //calculating the average
            avg = round((blue + green + red) / 3);

            //transfreeing the final details into image file
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //loops to move throught each element in the matrix
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;

            //formula implementation
            float  sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            float  sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            float  sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);


            //conditions in case the value to individual colour excceedess 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            //transfreeing the final details into temp
            temp[i][j].rgbtRed = sepiaRed;
            temp[i][j].rgbtBlue = sepiaBlue;
            temp[i][j].rgbtGreen = sepiaGreen;

        }
    }

    // transferring the memory finally from temp to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //loops to move throught each element in the matrix
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            temp[i][j] = image[i][width - 1 - j];
        }
    }

    //loop to finally transfer the memory from temo to image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Blur image
//program to check if the pixel exists in the file or not
bool is_true_pixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}



RGBTRIPLE get_blur_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int redValue, greenValue, blueValue;
    redValue = greenValue = blueValue = 0;
    int total_pixel = 0;

    //loop to move around the surrounding element of the main element
    for (int ti = -1; ti <= 1; ti ++)
    {
        for (int tj = -1; tj <= 1; tj ++)
        {
            int ni = i + ti;
            int nj = j + tj;
            if (is_true_pixel(ni, nj, height, width))
            {
                total_pixel ++;
                redValue = redValue + image[ni][nj].rgbtRed;
                greenValue = greenValue + image[ni][nj].rgbtGreen;
                blueValue = blueValue + image[ni][nj].rgbtBlue;
            }
        }
    }

    //creating the stucture element so as to transfer the detail onto another function
    RGBTRIPLE blur_pixel;
    blur_pixel.rgbtRed = round((float)redValue / total_pixel);
    blur_pixel.rgbtBlue = round((float)blueValue / total_pixel);
    blur_pixel.rgbtGreen = round((float)greenValue / total_pixel);
    return blur_pixel;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_image[height][width];
    //loops to move throught each element in the matrix
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            blur_image[i][j] = get_blur_pixel(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j] = blur_image[i][j];
        }
    }
}

