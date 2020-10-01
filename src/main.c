#include <stdio.h>
#include <math.h>

#define PI  3.1415926

#define error(...) (fprintf(stderr, __VA_ARGS__))

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

double methode_rectangle(int n, double l_b, double r_b) {
	double integral = 0;
	double h = (r_b - l_b) / n;
	double x = l_b;
	for (int i = 0; i < n; i++) {
		integral += sin(x + h / 2) * h;
		x += h;
	}
	return integral;
}

double methode_simps(int n, double l_b, double r_b) {
	double h = (r_b - l_b) / 2 / n;
	double integral = sin(l_b) + sin(r_b);
	double x = l_b + h;
	for (int i = 1; i < 2 * n; i++) {
		if (i % 2 == 0) integral += 2 * sin(x);
		else integral += 4 * sin(x);
		x += h;
	}
	return (integral *= h / 3);
}

int vizov(int a[], double l_b, double r_b, char answer_vizov[][25]) {
	for (int i = 0; i < 6; i++) {
		int j = 0;
		double integral_rectangle = methode_rectangle(a[i], l_b, r_b);
		double integral_simpson = methode_simps(a[i], l_b, r_b);
		if (!sprintf(answer_vizov[i], "%d %2.5f %2.5f", a[i], integral_rectangle, integral_simpson)) {
			printf("Cannot write results to string in %d experiment\n", i);
			return -1;
		}
		a[i] = 0;
	}
	return 0;
}

int entering_numbers(double* l_b, double* r_b) {
	if (printf("Enter interval's left border: ") < 0) {
		error("Cannot write to stdout\n");
		return -1;
	}
	if (scanf("%lf", l_b) != 1) {
		error("Cannot read interval's left border\n");
	}
	if (*l_b < 0) {
		error("Left border of the interval must be greater or equal than 0\n");
		return -1;
	}
	if (*l_b > PI) {
		error("Left border of the interval must be lower or equal than PI\n");
		return -1;
	}
	if (printf("Enter interval's right border: ") < 0) {
		error("Cannot write to stdout\n");
		return -1;
	}
	if (scanf("%lf", r_b) != 1) {
		error("Cannot read interval's right border\n");
	}
	if (*r_b > PI) {
		error("Right border of the interval must be less or equal than pi\n");
		return -1;
	}
	if (*r_b < *l_b) {
		error("Right border of the interval must be greater than left\n");
		return -1;
	}
	return 0;
}

int main()
{
	int number_of_segments[] = {5, 10, 20, 100, 500, 1000};
	double left_border, right_border;
	char answer[6][25];
	if (entering_numbers(&left_border, &right_border)) {
		return 1;
	}
	if (vizov(number_of_segments, left_border, right_border, answer)) {
		return 1;
	}
	for (int i = 0; i < 6; i++) {
		if (printf("%s\n", answer[i]) < 0) {
			printf("Cannot write %d answer to stdout\n", i);
			break;
		}
	}
	return 0;
}
