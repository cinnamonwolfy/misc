#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate(double nums[], char op){
	switch(op){
		case '+':
			return nums[0] + nums[1];
		case '-':
			return nums[0] - nums[1];
		case '*':
			return nums[0] * nums[1];
		case '/':
			return nums[0] / nums[1];
	}
}

int main(int argc, const char* argv[]){
	if(argc - 1 < 3){
		printf("Error: Invocation should include 3 parameters, only %d parameters were provided\n", argc - 1);
		exit(1);
	}

	double numbers[2] = {atof(argv[1]), atof(argv[3])};
	double result = calculate(numbers, argv[2][0]);

	printf("%f\n", result);
	exit(0);
}
