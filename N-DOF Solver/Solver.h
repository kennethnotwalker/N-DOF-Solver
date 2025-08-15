#pragma once
#include "SolverUtil.h"

const double s_PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844;

const double GRAD_DIFF = 10e-5;
const double STEP_SIZE = 10e-2;

typedef struct struct_constraint
{
	double min;
	double max;
} Constraint;

Constraint* halfCircleConstraints(int size);

double* gradient(double* inputs, double* answer, int size, double (*f)(double*, double*, int));

double distanceToAnswer(double* inputs, double* answer, int size);

double* getRotation(double* targetPosition, struct_constraint* constraints, int size, double (*_fx)(double*, int), double (*_fy)(double*, int), double (*_fz)(double*, int), double min_error = 10e-5, double min_square_error_change = 10e-100);
