#include "../Solver.h"
#include "iostream"
using namespace std;

double lengths_3DOF[2] = { 1, 0.75 };

//angle 0 rotates in the xy plane while angles 1 and 2 rotate in the plane aligned in the z direction (think of a stereotypical robotic arm)

double x_3DOF(double* A, int size) //x coordinate of end-point given all angles
{
	return (lengths_3DOF[0] * cos(A[1]) + lengths_3DOF[1] * cos(A[2])) * cos(A[0]);
}
double y_3DOF(double* A, int size) //y coordinate of end-point given all angles
{
	return (lengths_3DOF[0] * cos(A[1]) + lengths_3DOF[1] * cos(A[2])) * sin(A[0]);
}

double z_3DOF(double* A, int size) //z coordinate of end-point given all angles
{
	return (lengths_3DOF[0] * sin(A[1]) + lengths_3DOF[1] * sin(A[2]));
}

int _main(void)
{
	double pos[3] = { 0.5, 0.2, 0.2 };
	Constraint* constraints = halfCircleConstraints(3);

	constraints[0] = {0, 2*s_PI};
	constraints[1].min = 0;

	double rotations[3] = { 0, 0, 0 };

	double* rot = getRotation(pos, constraints, 3, x_3DOF, y_3DOF, z_3DOF);
	double r0 = rot[0];
	double r1 = rot[1];
	double r2 = rot[2];
	delete[] constraints;
	return 0;
}