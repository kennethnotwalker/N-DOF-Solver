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

double* getRotation(double* rotations, double* targetPosition, struct_constraint* constraints, int size, double (*_fx)(double*, int), double (*_fy)(double*, int), double (*_fz)(double*, int), int max_iter, double min_error, double min_error_change, double momentum, int* iteration_counter) //position is 3-Dimensional
{
	fx = _fx;
	fy = _fy;
	fz = _fz;
	//solve using gradient descent
	double error = distanceToAnswer(rotations, targetPosition, size);
	double* velocity = zeroVector(size);
	int gradCount = 0;

	double change = 1;
	double step = STEP_SIZE;
	double changeScale = 1;
	int iter = 0;
	while (error > min_error && change > min_error_change*changeScale && (max_iter < 0 || iter < max_iter))
	{
		double* delta = scale(velocity, -STEP_SIZE * momentum, size);
		double* input = add(rotations, delta, size);
		double* scaledGrad = gradient(input, targetPosition, size, distanceToAnswer);
		delete[] delta;
		delete[] input;

		scaleSelf(velocity, momentum, size);
		addTo(velocity, scaledGrad, size);
		delete[] scaledGrad;

		double* velocityAdded = scale(velocity, -step, size);
		addTo(rotations, velocityAdded, size);
		delete[] velocityAdded;

		for (int i = 0; i < size; i++)
		{
			rotations[i] = clamp(rotations[i], constraints[i].min, constraints[i].max);
		}
		double newError = distanceToAnswer(rotations, targetPosition, size);
		change = newError - error;
		if (change < 0) { change *= -1; }
		error = newError;
		
		iter++;
		step *= 1 - STEP_DECAY;
		changeScale *= 1 - STEP_DECAY;
	}

	if (iteration_counter != nullptr)
	{
		(*iteration_counter) = iter;
	}

	return rotations;
}