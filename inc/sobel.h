#ifndef SOBEL_H
#define SOBEL_H

void sobel_operation(unsigned char *imgIn, unsigned char *imgOut, const int width, const int height, const size_t threshold);
unsigned char *sobel_filtering(unsigned char *imgIn, int width, int height);
#endif