Calc
Naeem Hossain
October 21, 2016
Computer Architecture


This assignment is designed to help you learn the representation, interpretation, and manipulation of data as bits. There are two parts. In the first part, you will implement a program calc to add and subtract numbers specified in different bases (multiplication is extra credit). In the second part, you will implement a program format that will print the decimal values of bit sequences representing integer and floating point data types. 


To compile, cd into src dir and run “make”. This builds the default target application. 




How calc.c works:


Input:
calc <op> <number1> <number2> <output base>


“b” = Binary
“o” = Octal
“d” = Decimal
“X” = Hexadecimal
	
The program uses a doubly Linked List to represent the different parts of binary.  Whenever a character is counted, it is queued to the front of the List as an int. Much of the program basically converts to binary and then work magic from there.


Binary -> Dec
Adds all bits through the linked list, reverses the order, then adds 
[(iteration times) * 1 ]^2  or [(iteration times) * 0 ]^2  and returns end result.


Dec -> Dec
Uses atoi function to convert string into int, then returns converted integral number in desired Dec form.


Hexa -> Dec
Loops through a char array and adds the binary representation of the specific hexa  alpha numberic char to a binary string. Calls Bin -> Dec function and returns. 


Octal -> Dec
Loops through a char array and adds the representation of specific char and turns it into binary. Sends the element back to the decimal function and returns result.


Dec -> Binary
	Allocates a string and applies %2 or /2 until it gets the output string. Then returns the string since it’s in binary.


Dec -> Hexa
	Uses Dec -> Binary function. Then uses Binary -> Dec to find Hexa representations, and outputs the Hexa string.


Dec -> Octal
	Uses Dec -> Binary function. Then uses Binary -> Dec to find octal representations, and outputs the Octal string. 


USAGE: 


./calc -h : displays help and usage instr for the program
./calc <op> <number1> <number2> <output base> : Runs calc program




How format.c works:


Input: format <input bit sequence> <type> 


“int” = the format is two’s complement
“float” = the format is IEEE 754 single precision


The program receives arguments. First, it checks the number of args. Then, it checks arguments for cases of ints and floats. Then, it checks 1st arg for correct bit formatting. It returns an error if any of these is incorrect. After it checks the args, a new node is created holding the exponent and number. 
If the type is a positive int, it calls Binary -> Dec and prints output
If the type is a negative int, it finds the square’s complement and does same process for a positive int.
If the type is a positive float, it splits the string, checks for edge cases, and computes the number by converting it into a float. It then calculates 2 to the power of the exponent and saves it in an int. Then it multiplies the result and finds the float rep of the 32 bits. 
If the type is a negative float, it repeats the same process as the positive float but it is first converted to the two’s complement. 
Format then converts the result into scientific notation, and then returns the string which the program prints. 


USAGE: 


./format -h : displays help and usage instr for the program
./format <input bit sequence> <type> : Runs format program
