#include "TestFunc.h"
#include <math.h>

double cosTotal(double* A, int size)
{
	double total = 0;
	for (int i = 0; i < size; i++)
	{
		total += cos(A[i]);
	}
	return total;
}
double sinTotal(double* A, int size)
{
	double total = 0;
	for (int i = 0; i < size; i++)
	{
		total += sin(A[i]);
	}
	return total;
}

double returnZero(double* A, int size)
{
	return 0;
}