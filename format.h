#ifndef FORMAT_H
#define FORMAT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

struct number{
	int sign;

	char* exponent;
	char* mantissa;
	bool negative;
	char* original;
	signed long decimal;
};

struct node{
	int val;
	struct node *next;
};

typedef struct number wholeNum;
typedef signed long int lu;

/*Displays Help Function*/
void help(char* error);
/*Check the arguments*/
void checkArgs(char* arg1, char* arg2);
/*Checks valid binary number*/
void checkBin(char* binary);
/*Checks valid decimal number*/
void checkDe(char* binary);
/*Checks valid hexadecimal number*/
void checkHex(char* binary);
/*Checks valid Octal number*/
void checkOct(char* binary);

/*formats 32 bit sequence*/
void format(char* binary, char* type);
/*Removes First character of String*/
char *removeFirst(char *charBuffer);
/*Reverses String*/
char* reverseString(char *str);
/*twos complement*/
char* twoComp(char* str);
/*Parses IEEE 754 to float*/
char* floatParse(char* number);
/*Converts total to Scientific notation*/
char* sigFig(float total);

/*Converts Binary to Decimal Lower than 0*/
float conBinToDec0(char* binary);
/*Converts Binary to Decimal*/
signed long conBinToDec(char* binary);
/*Converts Decimal to Binary*/
char * conDecToBin(signed long dec);

/*Adds to front of list given a linked list*/
struct number * addFront(char c, struct number * front);
/*Creates linked list of binary numbers in string format*/
struct node * binList(char * binary);
#endif

