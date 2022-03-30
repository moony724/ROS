#include <stdio.h>
#include <math.h>
#define SIZE 4

double x[SIZE], y[SIZE];
double x_sum, x_avg, y_sum, y_avg;
double numerator, denominator, a, b;

int main(void)
{
	int i = 0;
	
	printf("please enter the x values (%d) : ", SIZE);
	for(i = 0; i < SIZE; i++)
	scanf("%lf", &x[i]);
	printf("please enter the y values (%d) : ", SIZE);
	for(i = 0; i < SIZE; i++)
	scanf("%lf", &y[i]);
	
	for(i = 0; i < SIZE; i++)
	{
		x_sum += x[i];
		y_sum += y[i];
	}
	x_avg = x_sum / SIZE;
	y_avg = y_sum / SIZE;
	
	for(i = 0; i < SIZE; i++)
	{
		numerator += (x[i] - x_avg) * (y[i] - y_avg); // a값 분자
		denominator += pow((x[i] - x_avg),2);         // a값 분모
	}
	
	a = numerator / denominator;
	b = y_avg - (x_avg * a);
	
	printf("\nresult ==> y = %.1lfx + %.0lf\n\n", a, b); 
	
	
	return 0;
}
