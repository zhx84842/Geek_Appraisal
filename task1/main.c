#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	double size_length = 0.001;
	double a,y;
	double x = 0;
	
	printf("Please enter your initial value: ");
	scanf("%lf",  &a);
	y = a; 
	printf(" x\t y\n");
	
	while (y>= 0.001)//y-(1-size_length) * y = size_length * y>= 0.001 * size_length
	{
		printf("%.3lf\t%.8lf\n", x, y);
		x = x + size_length;
		y = (1-size_length) * y;
	}
	printf("\nThe number is %.8lf.", y);

	return 0;

}

