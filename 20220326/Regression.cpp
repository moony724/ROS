#include <iostream>
#include <cmath>
#define N 20

using namespace std;

float datax[N];
float datay[N];
float n = 0.0;

float EE(float x0, float x1, float y0, float y1);
float dis(float x, float y, float a, float b);
float avg(float a, float b);
float dfabda(float a, float b, float da);
float dfabdb(float a, float b, float db);

int main() 
{  
	for (int i = 0; i < N; i++)
    {
        datax[i] = i-0.5;
        datay[i] = i+0.5;
        n += i;
        printf("%f %f\n", datax[i], datay[i]);
    }
	
	float a0 = 0, b0 = 0;
	int iteration = 0;                                                 
	float eta = 0.0001;
	float psi = 0.005;
	float da = 0.01;
	float db = 0.01;
	float a1 = 2, b1 = 0;                                               
	while (EE(a0, b0, a1, b1) > eta && iteration < 100000) 
	{
		a0 = a1;
		b0 = b1;
		a1 -=   psi * dfabda(a0, b0, da);
		b1 -=   psi * dfabdb(a0, b0, db);
		iteration++;
	}
	cout << " y  = " << a1 << "x + " << b1 << endl;
	cout << iteration << "-th  E = " << EE(a0, b0, a1, b1) << endl;
	return 0;
}

float EE(float x0, float x1, float y0, float y1)                     
{
	return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

float dis(float x, float y, float a, float b)                        
{
	return abs(a * x - y + b) / sqrt(a * a + b * b);
}

float avg(float a, float b)                                         
{
	float sum;
	sum = 0.0;
	for (int i = 0; i < n; i++) 
	{
		sum += dis(datax[i], datay[i], a, b) / n;
	}
	return sum;
}

float dfabda(float a, float b, float da)                      // a val     
{
	return (avg(a + da, b) - avg(a, b)) / da;
}
  
float dfabdb(float a, float b, float db)                     // b val
{
	return (avg(a, b + db) - avg(a, b)) / db;
}
