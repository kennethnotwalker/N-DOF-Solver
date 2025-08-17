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

int main_1(void)
{
	double pos[3] = { 4, 0.8, 0 };
	Constraint* constraints = halfCircleConstraints(6);
	double* rot = new double[6];
	for (int i = 0; i < 6; i++)
	{
		rot[i] = 0;
	}
	int iter = 0;

	getRotation(rot, pos, constraints, 6, cosTotal_6DOF, sinTotal_6DOF, returnZero_6DOF, -1, 1.0e-4, 1.0e-99, 0, &iter);
	cout << "iterations until solution: " << iter << endl;
	
	delete[] constraints;
	delete[] rot;
	return 0;
}