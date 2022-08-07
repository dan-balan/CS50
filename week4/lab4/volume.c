// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t BYTEx2;

// prototype of func Volume Transformer
void volTransformer(BYTEx2 *sample, float vol);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    BYTE header[HEADER_SIZE];

    // Copy header from input file to headerbuffer array
    size_t hdlong = fread(&header, sizeof header[0], HEADER_SIZE, input);
    // copy headear to output file
    size_t hdlong2 = fwrite(&header, sizeof header[0], HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    BYTEx2 buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        volTransformer(&buffer, factor);
        fwrite(&buffer, sizeof(buffer), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}

void volTransformer(BYTEx2 *sample, float vol)
{
    *sample = *sample * vol;

    return;
}