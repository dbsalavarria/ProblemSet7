// Compile like this: gcc Problem7.2.c -lsndfile -o Problem7.2

#include <stdio.h>
#include <sndfile.h>

#define MAX_DATA_SIZE 4096

void cat(SNDFILE *input_sf, SNDFILE *output_sf); // cat function accepts 2 arguments: 2 pointers to SNDFILE

int main()
{
    SNDFILE *input_sf; // declare pointers to SNDFILE
    SNDFILE *output_sf;
    SF_INFO input_sfinfo; // declare variables of data type SF_INFO
    SF_INFO output_sfinfo;

    input_sfinfo.format = 0; // initialize .format inside input_sfinfo

    input_sf = sf_open("sine.wav", SFM_READ, &input_sfinfo); // call to sf_open function, which requires three arguments: name of file, READ or WRITE? and the address in memory of input_sfinfo
    if (input_sf == NULL) // check if file exists
    {
        printf("Failed to open file for reading\n");
        return 1;
    }
    //Because we want to copy the file, we intialize the output with the input values
    output_sfinfo.samplerate = input_sfinfo.samplerate; 
    output_sfinfo.channels = input_sfinfo.channels;
    output_sfinfo.format = input_sfinfo.format;

    output_sf = sf_open("5secs.wav", SFM_WRITE, &output_sfinfo); // call to sf_open, assign the result to output_sf
    if (output_sf == NULL) // check if file exists
    {
        printf("Failed to open file for writing\n");
        return 1;
    }

    for(int i = 0; i < 5; i++)
    {
        cat(input_sf, output_sf);
    }

    if (input_sf != NULL)
    {
        sf_close(input_sf);
    }

    if (output_sf != NULL)
    {
        sf_close(output_sf);
    }

    return 0;
}

void cat(SNDFILE *input_sf, SNDFILE *output_sf) // cat() definition
{
    float data[MAX_DATA_SIZE] = {0};
    int count = 0;

    sf_seek(input_sf, 0, SEEK_SET);
    while ((count = sf_read_float(input_sf, data, MAX_DATA_SIZE)) > 0)
    {
        sf_write_float(output_sf, data, count);
    }
}