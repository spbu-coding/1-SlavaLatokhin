#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <malloc.h>

#define printf(...) (fprintf(stderr, __VA_ARGS__))

#define MAX_LENGTH_OF_STRING 25

#pragma warning(disable : 4996) /*special for visual studio*/
#pragma warning(disable : 6031) /*special for visual studio*/

double integrate_with_methode_rectangle(int n, double l_b, double r_b) {
	double integral = 0;
	double height = (r_b - l_b) / n;
	double length_of_part = l_b;
	for (int i = 0; i < n; i++) {
		integral += sin(length_of_part + height / 2) * height;
		length_of_part += height;
	}
	return integral;
}

double integrate_with_methode_simps(int n, double l_b, double r_b) {
	double height = (r_b - l_b) / 2 / n;
	double integral = sin(l_b) + sin(r_b);
	double length_of_part = l_b + height;
	for (int i = 1; i < 2 * n; i++) {
		if (i % 2 == 0) integral += 2 * sin(length_of_part);
		else integral += 4 * sin(length_of_part);
		length_of_part += height;
	}
	return (integral *= height / 3);
}

void free_answers(char** answers, unsigned int count) {
	for (unsigned int i = 0; i < count; ++i) {
		free(answers[i]);
	}
	free(answers);
}

char** calculate(int ans[], double l_b, double r_b, int size_of_array_answer) {
	char** answers = (char**)malloc(sizeof(char*) * size_of_array_answer);
	if (!answers) {
		return NULL;
	}
	for (int i = 0; i < size_of_array_answer; i++) {
		double integral_rectangle = integrate_with_methode_rectangle(ans[i], l_b, r_b);
		double integral_simpson = integrate_with_methode_simps(ans[i], l_b, r_b);
		answers[i] = (char*)malloc(sizeof(char) * MAX_LENGTH_OF_STRING);
		if (!answers[i]) {
			free_answers(answers, i);
			printf("Cannot allocate memory for result string in %d experiment\n", i);
			return NULL;
		}
		if (!sprintf(answers[i], "%-4d %.5f %.5f", ans[i], integral_rectangle, integral_simpson)) {
			free_answers(answers, i + 1);
			printf("Cannot write results to string in %d experiment\n", i);
			return NULL;
		}
		ans[i] = 0;
	}
	return answers;
}

int entering_numbers(double* l_b, double* r_b) {
	if (printf("Enter interval's left border: ") < 0) {
		printf("Cannot write to stdout\n");
		return -1;
	}
	if (scanf("%lf", l_b) != 1) {
		printf("Cannot read interval's left border\n");
	}
	if (*l_b < 0) {
		printf("Left border of the interval must be greater or equal than 0\n");
		return -1;
	}
	if (*l_b > M_PI) {
		printf("Left border of the interval must be lower or equal than PI\n");
		return -1;
	}
	if (printf("Enter interval's right border: ") < 0) {
		printf("Cannot write to stdout\n");
		return -1;
	}
	if (scanf("%lf", r_b) != 1) {
		printf("Cannot read interval's right border\n");
	}
	if (*r_b > M_PI) {
		printf("Right border of the interval must be less or equal than pi\n");
		return -1;
	}
	if (*r_b < *l_b) {
		printf("Right border of the interval must be greater than left\n");
		return -1;
	}
	return 0;
}

int main() {
	int number_of_segments[] = { 6, 10, 20, 100, 500, 1000 };
	int size_of_array_answer = (sizeof(number_of_segments) / sizeof(number_of_segments[0]));
	double left_border, right_border;
	if (entering_numbers(&left_border, &right_border)) {
		return 1;
	}
	char** answer = calculate(number_of_segments, left_border, right_border, size_of_array_answer);
	if (!answer) {
		return 1;
	}
	for (int i = 0; i < size_of_array_answer; i++) {
		if (printf("%s\n", answer[i]) < 0) {
			printf("Cannot write %d answer to stdout\n", i);
			break;
		}
	}
	return 0;
}
