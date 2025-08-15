#include "Solver.h"



double (*fx)(double*, int);
double (*fy)(double*, int);
double (*fz)(double*, int);

Constraint* halfCircleConstraints(int size)
{
	Constraint* cons = new Constraint[size];
	for (int i = 0; i < size; i++)
	{
		cons[i] = {-s_PI /2, s_PI /2};
	}
	return cons;
}

double* gradient(double* inputs, double* answer, int size, double (*f)(double*, double*, int)) //f1 = cos total, f2 = sin total
{
	double* grads = new double[size];
	double y0 = f(inputs, answer, size);
	for (int i = 0; i < size; i++)
	{
		inputs[i] += GRAD_DIFF;
		double y1 = f(inputs, answer, size);
		inputs[i] -= GRAD_DIFF;

		double grad = (y1 - y0) / GRAD_DIFF;
		grads[i] = grad;
	}
	return grads;
}

double distanceToAnswer(double* inputs, double* answer, int size) //fx = final x coord, fy = final y coord, fz = final z coord
{
	double x = fx(inputs, size);
	double y = fy(inputs, size);
	double z = fz(inputs, size);

	double dx = answer[0] - x;
	double dy = answer[1] - y;
	double dz = answer[2] - z;

	double diff = dx*dx + dy*dy + dz*dz;
	return diff;
}

double* getRotation(double* targetPosition, struct_constraint* constraints, int size, double (*_fx)(double*, int), double (*_fy)(double*, int), double (*_fz)(double*, int), double min_error, double min_square_error_change) //position is 3-Dimensional
{
	double* rotations = zeroVector(size);
	fx = _fx;
	fy = _fy;
	fz = _fz;
	//solve using gradient descent
	double error = distanceToAnswer(rotations, targetPosition, size);
	double change = 1;
	while (error > min_error && change*change > min_square_error_change)
	{
		double* grad = gradient(rotations, targetPosition, size, distanceToAnswer);
		scaleSelf(grad, -STEP_SIZE, size);
		addTo(rotations, grad, size);
		for (int i = 0; i < size; i++)
		{
			rotations[i] = clamp(rotations[i], constraints[i].min, constraints[i].max);
		}
		double newError = distanceToAnswer(rotations, targetPosition, size);
		change = newError - error;
		error = newError;
		delete[] grad;
	}

	return rotations;
}