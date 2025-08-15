#pragma once

double* add(double* A, double* B, int size);
void addTo(double* A, double* B, int size);
double* sub(double* A, double* B, int size);
double* mult(double* A, double* B, int size);
double* div(double* A, double* B, int size);
double* scale(double* A, double S, int size);
void scaleSelf(double* A, double S, int size);
double magnitudesq(double* A, int size);
double* zeroVector(int size);
double clamp(double x, double min, double max);