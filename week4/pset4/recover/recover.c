/*
JPEG signature/header
buffer[0] == 0xff
buffer[1] == 0xd8
buffer[2] == 0xff
(buffer[3] & 0xf0) == 0xe0

filename format: ###.jpg, starting at 000.jpg
sprintf(filename, "%03i.jpg", 2);

FILE *img = fopen(filename, "w");

fwrite(data, size, number, outptr); return: number of elements size

Pseudocode
Open memory card
Repeat until end of card
    Read 512 bytes into buffer
    if start of new JPEG
        if first JPEG
        ...
        Else
        ...
    Else
        If already found JPEG
        ...

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
enum { SIZE = 512 };

// images counter
int imgCounter = 0;

// function prototype
bool isJpegSign(BYTE *buffer);


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }


    // Open raw file
    FILE *inputraw = fopen(argv[1], "r");
    if (inputraw == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //flags
    bool openImg = false;
    bool firstImg = false;
    //temporary pointer for created document while scope to global
    FILE *temp = NULL;

    while (1)
    {
        // Read a FAT 512 bytes block size
        BYTE buffer[SIZE];
        size_t hdlong = fread(buffer, sizeof(BYTE), SIZE, inputraw);

        if (isJpegSign(buffer))
        {
            if (!firstImg)
            {
                char filename[10];
                sprintf(filename, "%03i.jpg", imgCounter);
                imgCounter++;
                // Open a New JPEG file
                FILE *img = fopen(filename, "w");
                if (img == NULL)
                {
                    printf("Could not create image.\n");
                    fclose(inputraw);
                    return 7;
                }
                //write the jpeg Header
                fwrite(&buffer, sizeof(BYTE), hdlong, img);
                // while scope to global
                temp = img;
                openImg = true;
                firstImg = true;
            }
            else
            {
                fclose(temp);

                char filename[10];
                sprintf(filename, "%03i.jpg", imgCounter);
                imgCounter++;
                // Open a New JPEG file
                FILE *img = fopen(filename, "w");
                if (img == NULL)
                {
                    printf("Could not create image.\n");
                    fclose(inputraw);
                    return 7;
                }
                fwrite(&buffer, sizeof(BYTE), hdlong, temp);
                openImg = true;
                // while scope to global
                temp = img;
            }
        }
        else
        {
            // write only if open IMG
            if (openImg)
            {
                fwrite(&buffer, sizeof(BYTE), hdlong, temp);
                //
                if (!(hdlong == SIZE))
                {
                    fclose(temp);
                    break;
                }
            }
        }
    }
    // Close infile
    fclose(inputraw);
    return 0;
}


// check if the buffer represent a JPEG signature
bool isJpegSign(BYTE *buffer)
{
    if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
    {
        return true;
    }
    return false;
}

