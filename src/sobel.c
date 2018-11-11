/*
char sobel_check_threshold ( char pixel ,const size_t threshold )
{
     if ( pixel >= threshold )
          return (char )255 ;
     else
          return (char )0 ;
}

void sobel_operation(unsigned char *imgIn, unsigned char *imgOut, const int width, const int height, const size_t threshold)
{
	int rows,cols;
	float gradient_h, gradient_v;
	char pixel;

	imgOut = (unsigned char*)malloc(sizeof(imgIn));

	for (rows = 0; rows < height; rows++)
	{
		for (cols = 0; cols < width; cols++)
		{
			if ((rows != 0) && (cols != 0) && 
				(rows != height - 1) && (cols != width -1 ))
			{
				
				gradient_v = -(- imgIn [ (rows-1)*width + (cols-1 )] 
							   + imgIn [(rows-1)*width + (cols+1) ] 
							   - 2*imgIn [rows*width + (cols-1)] 
							   + 2*imgIn [ rows*width + (cols+1) ] 
							   - imgIn[ (rows+1)*width + (cols-1)] 
							   + imgIn [ (rows+1)*width + (cols+1)] ) /8 ;
					
				gradient_h = -(- imgIn [(rows-1)*width + (cols-1)] 
							   - 2*imgIn [ (rows-1)*width + cols ] 
							   - imgIn [(rows-1)*width + (cols+1)] 
							   + imgIn [(rows+1)*width + (cols-1)] 
							   + 2*imgIn [(rows+1)*width + cols ]  
							   + imgIn [(rows+1)*width + (cols+1)] ) /8 ;
			
				//Assign to image
				pixel = ( char ) sqrtf ( gradient_h * gradient_h + gradient_v * gradient_v ) ;
						Output[ ( rows - 1 )*width  + (cols- 1 ) ]   =  sobel_check_threshold  ( pixel, threshold );
			}
		}
	}
}
*/

#include "file.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

float kernelx[3][3] = { { -1, 0, 1 },
                        { -2, 0, 2 },
                        { -1, 0, 1 } };

float kernely[3][3] = { { -1, -2, -1 },
                        {  0,  0,  0 },
                        {  1,  2,  1 } };


unsigned char *sobel_filtering(unsigned char *imgIn, int width, int height)
{
	unsigned char *imgOut;
	float pixel_value;
  	float min, max;
  	int x, y, i, j; 

	imgOut = (unsigned char*)malloc(sizeof(imgIn));
	printf("Started filtering the image.\n\n");
	min = LONG_MAX;
	max = LONG_MIN;

	for (y = 1; y < height - 1; y++) 
	{
    	for (x = 1; x < width - 1; x++) 
		{
      		pixel_value = 0.0;
      		for (j = -1; j <= 1; j++) 
			{
      		    for (i = -1; i <= 1; i++) 
      		      pixel_value += kernelx[j + 1][i + 1] * (float)(imgIn[y + j + width * x + i]);
      		    
      		}
      		if (pixel_value < min) min = pixel_value;
      		if (pixel_value > max) max = pixel_value;
    	}
  	}

	for (y = 1; y < height - 1; y++) 
	{
    	for (x = 1; x < width - 1; x++) 
		{
      		pixel_value = 0.0;
      		for (j = -1; j <= 1; j++) 
			{
          		for (i = -1; i <= 1; i++) 
            	pixel_value += kernelx[j + 1][i + 1] * (float)(imgIn[y + j + width * x + i]);
          	}
      	}
      	pixel_value = (pixel_value - min) / (max - min);
      	imgOut[y + width * x] = (unsigned char)pixel_value;
  	}

  	return imgOut;
}
