#include "helpers.h"
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];
            int average = (pixel->rgbtBlue + pixel->rgbtGreen + pixel->rgbtRed) / 3;
            pixel->rgbtBlue = average;
            pixel->rgbtGreen = average;
            pixel->rgbtRed = average;
        }
    }
    return;
}

BYTE get_min(BYTE value_one, BYTE value_two)
{
    if (value_one < value_two)
        return value_one;

    return value_two;
}

BYTE safe_add_bytes(BYTE one, BYTE two)
{
    if (two > 255 - one)
        return 255;
    return one + two;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
      for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];
            BYTE original_red = pixel->rgbtRed;
            BYTE original_green = pixel->rgbtGreen;
            BYTE original_blue = pixel->rgbtBlue;
            pixel->rgbtRed = safe_add_bytes(safe_add_bytes(.393 * original_red, .769 * original_green), .189 * original_blue);
            pixel->rgbtBlue = safe_add_bytes(safe_add_bytes(.349 * original_red, .686 * original_green), .168 * original_blue);
            pixel->rgbtGreen = safe_add_bytes(safe_add_bytes(.272 * original_red, .534 * original_green), .131 * original_blue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE reversed[width];

        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            reversed[width - 1 - j] = image[i][j];
        }

        for (int j = 0; j < width; j++)
        {
            image[i][j] = reversed[j];
        }
    }
    return;
}

typedef struct {
    int x;
    int y;
} position;
enum direction{UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};
int direction_count = 8;

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image_copy[i][j];

            int pixel_count = 1;
            RGBTRIPLE *pixels = calloc(pixel_count, sizeof(RGBTRIPLE));
            pixels[0] = pixel;

            for (int k = 0; k < direction_count; k++)
            {
                position neighbor = { .x = j, .y = i };

                if (k == UP_LEFT || k == UP || k == UP_RIGHT)
                    neighbor.y--;

                if (k == UP_RIGHT || k ==  RIGHT || k == DOWN_RIGHT)
                    neighbor.x++;

                if (k == DOWN_RIGHT || k == DOWN || k == DOWN_LEFT)
                    neighbor.y++;

                if (k == DOWN_LEFT || k == LEFT || k == UP_LEFT)
                    neighbor.x--;

                if (neighbor.x < 0 || neighbor.x > width - 1 || neighbor.y < 0 || neighbor.y > height - 1)
                    continue;

                pixel_count++;
                pixels = realloc(pixels, sizeof(RGBTRIPLE) * pixel_count);
                pixels[pixel_count - 1] = image[neighbor.y][neighbor.x];
            }

            // find the average for red green and blue
            int red_sum = 0;
            int blue_sum = 0;
            int green_sum = 0;

            for (int l = 0; l < pixel_count; l++)
            {
                red_sum += pixels[l].rgbtRed;
                blue_sum += pixels[l].rgbtBlue;
                green_sum += pixels[l].rgbtGreen;
            }

            image[i][j].rgbtRed = red_sum / pixel_count;
            image[i][j].rgbtBlue = blue_sum / pixel_count;
            image[i][j].rgbtGreen = green_sum / pixel_count;
        }
    }
    return;
}