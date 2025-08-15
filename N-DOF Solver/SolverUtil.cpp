#include "SolverUtil.h"

double* add(double* A, double* B, int size)
{
	double* C = new double[size];
	for (int i = 0; i < size; i++)
	{
		C[i] = A[i] + B[i];
	}
	return C;
}

void addTo(double* A, double* B, int size)
{
	for (int i = 0; i < size; i++)
	{
		A[i] += B[i];
	}
}

double* sub(double* A, double* B, int size)
{
	double* C = new double[size];
	for (int i = 0; i < size; i++)
	{
		C[i] = A[i] - B[i];
	}
	return C;
}

double* mult(double* A, double* B, int size)
{
	double* C = new double[size];
	for (int i = 0; i < size; i++)
	{
		C[i] = A[i] * B[i];
	}
	return C;
}

double* div(double* A, double* B, int size)
{
	double* C = new double[size];
	for (int i = 0; i < size; i++)
	{
		C[i] = A[i] / B[i];
	}
	return C;
}

double* scale(double* A, double S, int size)
{
	double* C = new double[size];
	for (int i = 0; i < size; i++)
	{
		C[i] = A[i] * S;
	}
	return C;
}

void scaleSelf(double* A, double S, int size)
{
	for (int i = 0; i < size; i++)
	{
		A[i] *= S;
	}
}

double magnitudesq(double* A, int size)
{
	double mag = 0;
	for (int i = 0; i < size; i++)
	{
		mag += A[i] * A[i];
	}
	return mag;
}

double* zeroVector(int size)
{
	double* vec = new double[size];

	for (int i = 0; i < size; i++)
	{
		vec[i] = 0;
	}
	return vec;
}

double clamp(double x, double min, double max)
{
	double y = x;
	if (y > max)
	{
		y = max;
	}
	if (y < min)
	{
		y = min;
	}
	return y;
}