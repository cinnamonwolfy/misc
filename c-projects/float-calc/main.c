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
	double numbers[argc / 2];
	char ops[argc / 2 - 1];

	for(int i = 0; i < argc / 2; i++){
		numbers[i] = atof(argv[1 + (i * 2)]);
		if(i < argc / 2 - 1){
			ops[i] = argv[2 + (i * 2)][0];
		}
	}

	for(int i = 0; i < argc / 2 - 1; i++){
		if(ops[i] == '*' || ops[i] == '/'){
			if(i != 0 && (ops[i - 1] == '*' || ops[i - 1] == '/')){
				double tempNums[2] = {result, numbers[i + 1]};
				result = calculate(tempNums, ops[i]);
				numbers[i + 1] = 0;
			}else if(argc / 2 - 1 == 1 || i == 0){
				double tempNums[2] = {numbers[i], numbers[i + 1]};
				result = calculate(tempNums, ops[i]);
			}else{
				double tempNums[2] = {numbers[i], numbers[i + 1]};
				if(ops[i - 1] == '-'){
					result -= calculate(tempNums, ops[i]);
				}else if(ops[i - 1] == '+'){
					result += calculate(tempNums, ops[i]);
				}else{
					printf("Error: Unsupported operation: %c", ops[i]);
					exit(2);
				}
				numbers[i] = 0;
				numbers[i + 1] = 0;
			}
		}
	}

	for(int i = 0; i < argc / 2 - 1; i++){
		if(ops[i] == '+' || ops[i] == '-'){
			if(result == 0 || i == 0){
				double tempNums[2] = {numbers[i], numbers[i + 1]};
				result += calculate(tempNums, ops[i]);
			}else{
				double tempNums[2] = {result, numbers[i + 1]};
				result = calculate(tempNums, ops[i]);
			}
		}
	}

	printf("%f\n", result);
	exit(0);
}
