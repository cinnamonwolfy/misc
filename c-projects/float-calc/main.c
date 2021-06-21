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
		printf("Error: Invocation should include at least 3 parameters, only %d parameters were provided\n", argc - 1);
		exit(1);
	}else if((argc - 1) % 2 != 1){
		printf("Error: Invocation should include a parameter amount of an odd number. An even number of parameters were provided: %d\n", argc - 1);
		exit(1);
	}

	double result = 0;

	for(int i = 1; i < argc - 1; i+=2){
		double numbers[2];
		if(i == 1){
			numbers[0] = atof(argv[i]);
			numbers[1] = atof(argv[i + 2]);
		}else{
			numbers[0] = result;
			numbers[1] = atof(argv[i + 2]);
		}
		result = calculate(numbers, argv[i + 1][0]);
	}

//	double numbers[2] = {atof(argv[1]), atof(argv[3])};
//	double result = calculate(numbers, argv[2][0]);

	printf("%f\n", result);
	exit(0);
}
