/*
 *      Author: Kenneth Baldridge
 */

#include<stdio.h>
#include<stdlib.h>

//function declarations
double toDouble(char *theBinaryString);
void toBinary(double num, char *binaryString);
double calculate(double num1, char op, double num2);

/* Program starts here. Takes input and has it processed.
 */
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	char input[64], num1[64], op, num2[64], binaryResult[64], toExit;
	double num1_Double, num2_Double, results;

	while (1) {
		printf("Enter an expression using binary numbers or Q to quit: ");
		fgets(input, sizeof(input), stdin);

		toExit = input[0];

		if (toExit == 'q' || toExit == 'Q') {
			break;
		}

		//get inputs and assign values
		sscanf(input, "%s %c %s", num1, &op, num2);

		//collect required numbers/binaries
		num1_Double = toDouble(num1);
		num2_Double = toDouble(num2);
		results = calculate(num1_Double, op, num2_Double);
		toBinary(results, binaryResult);

		//display results
		printf("%.10f %c %.10f = %.10f\n", num1_Double, op, num2_Double,
				results);
		printf("%s %c %s = %s\n", num1, op, num2, binaryResult);
	}

	return 0;

}

/* Converts a char array representation of a binary number into a double.
 *
 * parameter: *theBinaryString   Pointer to a char array of a binary number
 * return:       double                 The double representation of the binary number
 */
double toDouble(char *theBinaryString) {

	double result;

	//beginning of converting int part
	int intPart = 0;
	for (; *theBinaryString != '.' && *theBinaryString != '\0';
			theBinaryString++) {

		intPart = intPart * 2 + (*theBinaryString - '0');

	}
	//end of int part

	result = intPart;

	// Beginning of converting fraction part
	if (*theBinaryString == '.') {  //checks if fraction
		double decimalBase = 0.5;
		double bitValue = 0.5;
		double fractionPart = 0.0;
		theBinaryString++;
		for (; *theBinaryString != '\0'; theBinaryString++) {

			int bit = *theBinaryString - '0';
			fractionPart += (double) bit * bitValue;
			bitValue *= decimalBase;
		}
		result += fractionPart;
	}
	// End of fraction part

	return result;
}

/* Converts a double into a char array representation of a binary number.
 *
 * parameter: *theBinaryString   A pointer to a char array to hold the binary number.
 * parameter: num                    The double to be converted into binary.
 * return        void
 */
void toBinary(double num, char *binaryString) {
	char tempString[64];
	int intPart = (int) num, index = 0, remainder;
	double fractionPart = num - intPart;

	//integer part
	if (intPart == 0) {
		binaryString[index++] = '0' + 0;
	} else {
		do {
			remainder = intPart % 2;
			intPart /= 2;
			tempString[index++] = '0' + remainder;
		} while (intPart > 0);
		//reverses string
		for (int k = 0; k < index; k++) {
			binaryString[k] = tempString[index - k - 1];
		}
	}

	binaryString[index++] = '.';

	///fraction part
	if (fractionPart == 0) {
		binaryString[index++] = '0' + 0;
	} else {
		remainder = 0;
		do {
			fractionPart *= 2;
			remainder = (int) fractionPart;
			fractionPart -= remainder;
			binaryString[index++] = '0' + remainder;
		} while (fractionPart != 0);
	}

	binaryString[index] = '\0';
}

/* Performs the calculations on the two numbers given the specified operation.
 *
 * parameter: num1    Number on left side of operation.
 * parameter: op         The operation to be performed.
 * parameter: num      Number on right side of operation.
 * return:       double   The result of the calcuation as a double.
 */
double calculate(double num1, char op, double num2) {

	double result;

	switch (op) {
	case '*':
		result = num1 * num2;
		break;
	case '/':
		result = num1 / num2;
		break;
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	}
	return result;
}
