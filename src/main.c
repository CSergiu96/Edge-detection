#include "file.h"
#include "sobel.h"

int main(int argc, char *argv[])
{
    unsigned char *imgIn, *imgOut;

    if(argc > 2)
        imgIn = load_IMG(argv[1]);
    else
        imgIn = load_IMG(IMG_default_path);
    
    if(imgIn == NULL)
    {
		printf("Image not loaded\n");
        return -1;
    }
    else
        printf("Image loaded\n");
    imgOut = sobel_filtering(imgIn, IMG_default_width, IMG_default_height);
    if(!write_IMG(argv[2],imgOut, IMG_default_width * IMG_default_height))
        printf("error");
}