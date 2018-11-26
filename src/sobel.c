#include "file.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

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
