#ifndef CALC_H
#define CALC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

struct number{
	char* binary;
	char* hex;
	char* oct;
	signed long decimal;
	bool negative;
	char* original;
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
void checkArgs(char* arg1, char* arg2, char* arg3, char* arg4);
/*Checks valid binary number*/
void checkBin(char* binary);
/*Checks valid decimal number*/
void checkDec(char* decimal);
/*Checks valid hexadecimal number*/
void checkHex(char* hex);
/*Checks valid Octal number*/
void checkOct(char* oct);

/*Parses string to int*/
struct number * parseNum(char* number);
/*Removes First character of String*/
char* removeFirst(char *charBuffer);
/*Reverses String*/
char* reverseString(char *str);


/*Add the arguments*/
void add(char* number1, char* number2, char* outbase);
/*Substract the arguments*/
void subs(char* number1, char* number2, char* outbase);
/*Multiply the arguments*/
void mult(char* number1, char* number2, char* outbase);

/*Converts Binary to Decimal*/
signed long conBinToDec(char* binary);
/*Converts Decimal to Binary*/
char* conDecToBin(signed long dec);
/*Converts Hexadecimal to Decimal*/
signed long conHexToDec(char* hex);
/*Converts Decimal to Binary*/
char* conDecToHex(signed long dec);
/*Converts Octal to Decimal*/
signed long conOctToDec(char* oct);
/*Converts Decimal to Binary*/
char* conDecToOct(signed long dec);

/*Adds to front of list given a linked list*/
struct number * addFront(char c, struct number * front);
/*Creates linked list of binary numbers in string format*/
struct node * binList(char * binary);
#endif

