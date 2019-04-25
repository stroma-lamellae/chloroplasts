#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <string>

#include "f.h"

using namespace std;

double rect(double a, int n, double stepsize, int thread_count);

double trap(double a, double b, int n, double stepsize, int thread_count);

double simpson(double a, double b, int n, double stepsize, int thread_count);

double monte_carlo(double a, double b, int n, double stepsize, int thread_count);

int main(int argc, char* argv[]){
	double global_result=0.0;	

	double start = omp_get_wtime();

	int thread_count = strtol(argv[1], NULL, 10);
	float a = atof(argv[2]);
	float b = atof(argv[3]);
	float stepsize = atof(argv[4]);
	int algorithm = strtol(argv[5], NULL, 10);
	int n = (b-a)/stepsize;

	switch(algorithm) {
		case 0:
			global_result = rect(a, n, stepsize, thread_count);
			break;
		case 1:
			global_result = trap(a, b, n, stepsize, thread_count);
			break;
		case 2:
			global_result = simpson(a, b, n, stepsize, thread_count);
			break;
		case 3:
			global_result = monte_carlo(a, b, n, stepsize, thread_count);
			break;
		default:
			printf("Choice of algorithm not defined!\n");
	}

	double end = omp_get_wtime();

	printf("%f, %f\n", global_result, end-start);
	return 0;
}

//Approximation using left endpoint of each slice
double rect(double a, int n, double stepsize, int thread_count) {
	double approx = 0.0;
	#pragma omp parallel for num_threads(thread_count) \
		reduction (+: approx) schedule(guided)
	for(int i = 0; i < n; ++i){
		approx += f(a + stepsize*i)*stepsize;
	}
	return approx;
}

double trap(double a, double b, int n, double stepsize, int thread_count) {
	double approx = 0.0; 
	#pragma omp parallel for num_threads(thread_count) \
		reduction (+: approx) schedule(guided, chunk)
	for(int i = 1; i < n; ++i){
		approx += 2.0*f(a + stepsize*i);
	}
	approx += (f(a) + f(b));
	approx *= stepsize/2;
	return approx;
}

double simpson(double a, double b, int n, double stepsize, int thread_count) {
	double approx = 0.0;
	int multiplier;
	#pragma omp parallel for num_threads(thread_count) \
		reduction (+: approx) private(multiplier) \
		schedule(guided)
	for(int i = 1; i < n; ++i){
		if (i % 2 == 1) {//odd
			multiplier = 4.0;
		}
		else {
			multiplier = 2.0;
		}
		approx += multiplier*f(a + stepsize*i);
	}
	approx += (f(a) + f(b));
	approx *= stepsize/3;
	return approx;
}

double monte_carlo(double a, double b, int n, double stepsize, int thread_count) {
	double num, approx = 0.0;
	#pragma omp parallel for num_threads(thread_count) \
		reduction (+: approx) private(num) schedule(guided)
	for(int i = 0; i <= n; ++i){
		num = a + drand48()*(b-a);
		approx += f(num);
	}
	return stepsize*approx;
}