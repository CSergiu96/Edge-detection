#ifndef SOBEL_H
#define SOBEL_H

float kernelx[3][3] = { { -1, 0, 1 },
                        { -2, 0, 2 },
                        { -1, 0, 1 } };

float kernely[3][3] = { { -1, -2, -1 },
                        {  0,  0,  0 },
                        {  1,  2,  1 } };


#endif