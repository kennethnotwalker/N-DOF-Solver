#include "../Solver.h"
#include "iostream"
using namespace std;

double lengths[6] = { 1, 1, 1, 0.5, 0.5, 0.5 };

double cosTotal_6DOF(double* A, int size) //x coordinate of end-point given all angles
{
	double total = 0;
	for (int i = 0; i < size; i++)
	{
		total += lengths[i] * cos(A[i]);
	}
	return total;
}
double sinTotal_6DOF(double* A, int size) //y coordinate of end-point given all angles
{
	double total = 0;
	for (int i = 0; i < size; i++)
	{
		total += lengths[i] * sin(A[i]);
	}
	return total;
}

double returnZero_6DOF(double* A, int size) //z coordinate of end-point given all angles
{
	return 0;
}

int _main(void)
{
	double pos[3] = { 4, 0.2, 0 };
	Constraint* constraints = halfCircleConstraints(3);

	double* rot = getRotation(pos, constraints, 6, cosTotal_6DOF, sinTotal_6DOF, returnZero_6DOF);
	
	delete[] constraints;
	return 0;
}