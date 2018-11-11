#include "file.h"

unsigned char *load_IMG(char *filename)
{
    FILE *imgFile;
	unsigned char *buffer;
	unsigned long fileLen;

    // Open the image file
    imgFile = fopen(filename,"rb");
    // Verify if open
    if (imgFile != NULL)
    {
        // If not stop the operation
		fprintf(stderr, "Unable to open file %s\n", filename);
        fclose(imgFile);
        return NULL;
    }
	//Get file length
	fseek(imgFile, 0, SEEK_END);
	fileLen = ftell(imgFile);
	fseek(imgFile, 0, SEEK_SET);

	//Allocate memory
	buffer=(unsigned char *)malloc(fileLen);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
		fclose(imgFile);
		return NULL;
	}
    // Copy the data
	fread(buffer,fileLen,sizeof(unsigned char),imgFile);
    // Close the file
    fclose(imgFile);
    return buffer;
}

bool write_IMG(char *filename, unsigned char *buffer, int buffer_size) 
{
    // Open
    FILE *imgFile;
	int index;

	imgFile = fopen(filename, "w");
    // Verify if open
    if (imgFile != NULL)
    {
        // If not stop the operation
        fclose(imgFile);
        return false;
    }

    // Write the buffer to the file
    index = 0;
	while(index < buffer_size)
        fputc(*(buffer + index++), imgFile);

    // Close the file
    fclose(imgFile);
    return true;
}
