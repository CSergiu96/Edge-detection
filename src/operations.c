
int convolution(char *x, int *y, int size) 
{
    int sum;
    int index;
    
    sum = 0;
    index = 0;
    while(index < size)
        sum += *(x + index) * *(y + size - index++ - 1);

    return sum;
}

float linear_interpolate(float x,float y,float mu)
 {
    return(x * ( 1 - mu ) + y * mu);
 }