#include "Solver.h"
#include "iostream"
using namespace std;

double arm_lengths[6] = { 2, 1};


//every other rotation is other axis
double x_6DOF(double* A, int size) //x coordinate of end-point given all angles
{
	double total = 0;
	double totalAngle = 0;
	for (int i = 1; i < size; i++)
	{
		total += arm_lengths[i-1] * cos(totalAngle + A[i]);
		totalAngle += A[i];
	}
	return total * cos(A[0]);
}
double y_6DOF(double* A, int size) //y coordinate of end-point given all angles
{
	double total = 0;
	double totalAngle = 0;
	for (int i = 1; i < size; i++)
	{
		total += arm_lengths[i-1] * sin(totalAngle + A[i]);
		totalAngle += A[i];
	}
	return total * cos(A[0]);
}

double z_6DOF(double* A, int size) //z coordinate of end-point given all angles
{
	double total = 0;
	double totalAngle = 0;
	for (int i = 1; i < size; i++)
	{
		total += arm_lengths[i-1] * sin(totalAngle + A[i]);
		totalAngle += A[i];
	}
	return total;
}

int main(void)
{
	double pos[3] = { 2.7, 0.01, 0.3 };
	int size = 6;
	Constraint* constraints = halfCircleConstraints(size);
	double* rot = new double[size];
	for (int i = 0; i < size; i++)
	{
		rot[i] = 0;
	}
	int iter_total = 0;
	int min_iter = 99999999;
	double min_momentum = 0;
	for (double m = 0; m < 1; m += 1e-2) {
		for (int i = 0; i < size; i++)
		{
			rot[i] = 0;
		}
		getRotation(rot, pos, constraints, size, x_6DOF, y_6DOF, z_6DOF, 10000, 1.0e-4, 1.0e-100, m, &iter_total);
		cout << "iterations until solution w/ momentum  " << m << ": " << iter_total << endl;
		cout << "w/ error: " << distanceToAnswer(rot, pos, size) << endl;
		for (int i = 0; i < size; i++)
		{
			rot[i] = 0;
		}
		if (iter_total < min_iter)
		{
			min_iter = iter_total;
			min_momentum = m;
		}
	}
	for (int i = 0; i < size; i++)
	{
		rot[i] = 0;
	}
	cout << "min iterations: " << min_iter << " with momentum " << min_momentum << endl;
	getRotation(rot, pos, constraints, size, x_6DOF, y_6DOF, z_6DOF, 1000, 1.0e-4, 1.0e-100, 0, &iter_total);
	cout << "iterations until solution: " << iter_total << endl;
	cout << "w/ error: " << distanceToAnswer(rot, pos, size) << endl;

	delete[] constraints;
	delete[] rot;
	return 0;
}