#ifndef FILE_H
#define FILE_H

#include "types.h"
#include <stdio.h>

#define IMG_default_path    "/res/lena.bmp"
#define IMG_default_width   128
#define IMG_default_height  128

unsigned char *load_IMG(char *filename);
bool write_IMG(char *filename, unsigned char *buffer, int buffer_size) ;

#endif