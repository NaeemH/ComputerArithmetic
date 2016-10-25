## Assignment 2
###Part 1
####Purpose
The purpose of calc is to add and subtract numbers specified in different bases (multiplication is extra credit).
This illustrates the usage of calc:

    calc <op> <number1> <number2> <output base>
The first argument, &lt;op&gt;,is either the string "+", for addition, or "-", for subtraction. And as Extra Credit multiplication, the &lt;op&gt; can also be the string "*", Since * is a wildcard in the terminal, one has to enter it with quotes.


The next two arguments, &lt;number1&gt; and &lt;number2&gt; are integers of arbitrary size. Each of these numbers will be given in the form of:

     -?(b|o|d|x)dndn-1...d1d0
which can be interpreted as: a number can optionally start with a '-' sign, followed by a base indicator, where b means the number is a binary number, o means octal, d means decimal, and x means hexadecimal. dndn-1...d1d0 are the digits of the number.

The final argument, <output base>, gives the base that the resulting number should be printed out in. Like the base indicator for the input numbers, this argument can be one of four strings:

     "b" for binary,
     "o" for octal,
     "d" for decimal,
     "x" for hexadecimal.
The program outputs the answer in the same form as the input numbers.

####Compilation
To compile, cd into the source directory and run make. The default target shall be built, which is the main calc application, and then it is ready.
Furthermore,  make debug will show debugging, and make clean will remove the executable files.

####Usage
     ./calc -h : -h displays usage instructions and help for the program
     ./calc <op> <number1> <number2> <output base> <op> is the operation, <number1> and <number2> are the numbers in either binary, decimal, hexadecimal, or octal which will be applied to the <op>, <output base> is the base in which calc outputs the calculation.

####Implementation
Calc first takes the arguments from main and checks the number of arguments. It then checks arguments specifically for each case, add, subtract, multiply. It then checks the second and third arguments for correct binary, decimal, hexadecimal, and octal representation. If either one of these are incorrect it returns with a specific error.
After the arguments have been checked they are sent either to add, subtract, or multiply. In either one of them the number is parsed: first the function creates a node which has the representation for a number. It then checks for negativity, If it is then it updates the node accordingly and removes the first character. Next it checks for the base and sends it to the corresponding function removes first character again and gets the result.

#####Binary to Decimal
To convert binary to decimal, the function adds all the 1s and 0s by creating a front node which has an int inside of it. It creates it in reverse order linked list out of the string given as input. It then adds to the total the power of 2 through the iteration times either zero or one. At the end the result is returned.

#####Decimal to Decimal
To convert decimal to an integer in C, it uses the atoi function built into C.

#####Hexadecimal to Decimal
To convert hexadecimal to decimal, the function loops through the character array and keeps adding the binary representation of the specific hexadecimal alpha numeric character to a binary string. It then sends it to the binary to decimal function which returns the decimal and the result is thus obtained.

#####Octal to Decimal
To convert octal to decimal, calc uses the same process as for hexadecimal but in a different format suiting base 8 numbers.

#####Decimal to Binary
To convert decimal to binary calc first allocates a string and then apply a series of mod 2 and dividing by 2 by two until the output string is obtained. It is then returned as a string.

#####Decimal to Hexadecimal
To convert decimal to hexadecimal calc first converts the decimal number to binary by using the previous function. It then converts binary to decimal by parsing 4 characters at a time and finding their hexadecimal representations. The output is a hexadecimal string

#####Decimal to Octal
To convert decimal to octal calc first converts the decimal number to binary by using the Decimal to Binary function. It then converts binary to decimal by parsing 4 characters at a time and finding their octal representations. The output is a octal string

#####Linked List
Calc uses linked list as a way to represent binary, however it does it in a reversed so that calculations can be much easier. So whenever a character is encountered it is automatically added to the front of the list as an integer.

When calc goes through all these conversions it is left with two numbers in C long format and it adds, subtracts, or multiplies then using C arithmatic and prints it in binary, hexadecimal, decimal, and octal and thereafter exits.

###Part 2
####Purpose
The purpose of format is that it will print the decimal values of bit sequences representing integer and floating point data types.
This illustrates the usage of format:

    format <input bit sequence> <type>

The first argument, &lt;input bit sequence&gt;, is a sequence of 32 bits.
The format program will get it as a string of 1 and 0 characters in the argv[1] argument to main.
This sequence of bits represents the binary values stored in 4 contiguous bytes in memory. The leftmost
bits are stored in the byte with the smallest address while the rightmost bits are stored in the byte
with the largest address.
The second argument, &lt;type&gt;, gives the type that is used to interpret the input bit
sequence, and can be either int (integer) or float.
The formats for the input bit sequence is as follows. If the type is:

     int: the format is two’s complement;
     float: the format is IEEE 754 single precision;

The program prints out the decimal representation of the input bit sequence, assuming a
big endian byte ordering. Floating point numbers are also printed in scientific notation. For positive infinity, the program outputs pinf, for negative infinity,
it outputs ninf, and for “NaN”, it outputs NaN.

####Compilation
To compile, cd into the source directory and run make. The default target shall be built, which is the main format application, and then it is ready.
Furthermore,  make debug will show debugging, and make clean will remove the executable files.

####Usage

     ./format -h : -h displays usage instructions and help for the program
     ./format <input bit sequence> <type> : <input bit sequence> is the is a sequence of 32 bits,  <type> gives the type used to interpret the input bit sequence, and can be either int (integer) or float.

####Implementation
Format first takes the arguments from main and checks the number of arguments. It then checks arguments specifically for each case, int and float. It then checks the first argument for correct bit representation. If either one of these are incorrect it returns with a specific error.

After the arguments have been checked they are checked for negativity and a new node is created holding the exponent, and the mantissa.

If the type is integer and positive it converts it into integer using Binary to Decimal conversion and prints it.

If it is an integer and negative it finds the twos complement and does the same process as for the positive integer.

If it is type float and positive it first splits the string into the mantissa and exponent. It then checks for special cases such as zero, positive infinity, negative infinity, and NaN. It then computes the mantissa by adding a decimal at the beginning and converting into a float. It then calculates 2 to the power of the exponent and saves it in an integer.Then it multiplies the result of both and finds the float representation of the 32-bits. The same follows for negative floats expcept that first it is converted to twos complement.

After that it converts it into scientific notation by dividing and multiplying by 10 for greater than 1 and less than 1 respectively. It then returns the string and the program prints it and exits. To convert from binary it uses the functions used by calc.


=======
## Assignment 2
###Part 1
####Purpose
The purpose of calc is to add and subtract numbers specified in different bases (multiplication is extra credit).
This illustrates the usage of calc:

    calc <op> <number1> <number2> <output base>
The first argument, &lt;op&gt;,is either the string "+", for addition, or "-", for subtraction. And as Extra Credit multiplication, the &lt;op&gt; can also be the string "*", Since * is a wildcard in the terminal, one has to enter it with quotes.

The first argument, &lt;op&gt;, is either the string "+", for addition, or "-", for subtraction. And as Extra Credit multiplication, the &lt;op&gt; can also be the string "*", Since * is a wildcard in the terminal, one has to enter it with quotes.

The next two arguments, &lt;number1&gt; and &lt;number2&gt; are integers of arbitrary size. Each of these numbers will be given in the form of:

     -?(b|o|d|x)dndn-1...d1d0
which can be interpreted as: a number can optionally start with a '-' sign, followed by a base indicator, where b means the number is a binary number, o means octal, d means decimal, and x means hexadecimal. dndn-1...d1d0 are the digits of the number.

The final argument, <output base>, gives the base that the resulting number should be printed out in. Like the base indicator for the input numbers, this argument can be one of four strings:

     "b" for binary,
     "o" for octal,
     "d" for decimal,
     "h" for hexadecimal.
The program outputs the answer in the same form as the input numbers.

####Compilation
To compile, cd into the source directory and run make. The default target shall be built, which is the main calc application, and then it is ready.
Furthermore,  make debug will show debugging, and make clean will remove the executable files.

####Usage
     ./calc -h : -h displays usage instructions and help for the program
     ./calc <op> <number1> <number2> <output base> <op> is the operation, <number1> and <number2> are the numbers in either binary, decimal, hexadecimal, or octal which will be applied to the <op>, <output base> is the base in which calc outputs the calculation.

####Implementation
Calc first takes the arguments from main and checks the number of arguments. If then checks arguments specifically for each case, add, subtract, multiply. It then checks the second and third arguments for correct binary, decimal, hexadecimal, and octal representation. If either one of these are incorrect it returns with a specific error.
After the arguments have been checked they are sent either to add, subtract, or multiply. In either one of them the number is parsed: first the function creates a node which has the representation for a number. It then checks for negativity, If it is then it updates the node accordingly and removes the first character. Next it checks for the base and sends it to the corresponding function removes first character again and get the result.

#####Binary to Decimal
To convert binary to decimal, the function creates a front node which has an int inside of it. Next it creates a reverse linked list out of the string given as input. It then adds to the total the power of 2 times either zero or one. At the end the result is returned.

#####Decimal to Decimal
To convert decimal to an integer in C, it uses the atoi function.

#####Hexadecimal to Decimal
To convert hexadecimal to decimal, the function loops through the character array and keeps adding the binary representation of the specific alpha numeric character to a binary string. It then sends it the the binary to decimal function which returns the decimal and the result is thus obtained.

#####Octal to Decimal
To convert octal to decimal, calc uses the same process as for hexadecimal but in a different format suiting base 8 numbers.

#####Decimal to Binary
To convert decimal to binary calc first allocates a string and then apply a series of mod 2 and divide by two until the output string is obtained. It is then returned

#####Decimal to Hexadecimal
To convert decimal to hexadecimal calc first converts the decimal number to binary by using the previous function. It then converts binary to decimal by parsing 4 characters at a time and finding their hexadecimal representations. The output is a hexadecimal string

#####Decimal to Octal
To convert decimal to octal calc first converts the decimal number to binary by using the previous function. It then converts binary to decimal by parsing 4 characters at a time and finding their octal representations. The output is a octal string

#####Linked List
Calc uses linked list as a way to represent binary, however it does it in a reversed so that calculations can be much easier.So whenever a character is encountered it is automatically added to the front of the list as an integer.

When calc goes through all these conversions it is left with two numbers in C long format and it adds, subtracts, or multiplies then using C arithmatic and prints it in every format and then exits.

###Part 2
####Purpose
The purpose of format is that it will print the decimal values of bit sequences representing integer and floating point data types.
This illustrates the usage of format:

    format <input bit sequence> <type>

The first argument, &lt;input bit sequence&gt;, is a sequence of 32 bits.
The format program will get it as a string of 1 and 0 characters in the argv[1] argument to main.
This sequence of bits represents the binary values stored in 4 contiguous bytes in memory. The leftmost
bits are stored in the byte with the smallest address while the rightmost bits are stored in the byte
with the largest address.
The second argument, &lt;type&gt;, gives the type that is used to interpret the input bit
sequence, and can be either int (integer) or float.
The formats for the input bit sequence is as follows. If the type is:

     int: the format is two’s complement;
     float: the format is IEEE 754 single precision;

The program prints out the decimal representation of the input bit sequence, assuming a
big endian byte ordering. Floating point numbers are also printed in scientific notation, where a
number 1.5x105 would be printed as 1.5e5. For positive infinity, the program outputs pinf, for negative infinity,
it outputs ninf, and for “NaN”, it outputs NaN.

####Compilation
To compile, cd into the source directory and run make. The default target shall be built, which is the main format application, and then it is ready.
Furthermore,  make debug will show debugging, and make clean will remove the executable files.

####Usage

     ./format -h : -h displays usage instructions and help for the program
     ./format <input bit sequence> <type> : <input bit sequence> is the is a sequence of 32 bits,  <type> gives the type used to interpret the input bit sequence, and can be either int (integer) or float.

####Imlementation
Format first takes the arguments from main and checks the number of arguments. It then checks arguments specifically for each case, int and float. It then checks the first argument for corrent bit representation. If either one of these are incorrect it returns with a specific error.
After the arguments have been checked they are checked for negative and a new node is creating holding the exponent, and the mantissa. If the type is integer and positive it converts it into integer using Binary to Decimal conversion and prints it. If it is an integer and negative it finds the twos complement and does the same process as for the positive integer. If it is type float it first splits the string into the mantissa and exponent. It then checks for special cases such as zero, positive infinity, negative infinity, and NaN. It then computes the mantissa by adding a decimal at the beginning and converting into a float. It then calculates 2 to the power of the exponent and saves it in an integer.
Then it multiplies the result of both and finds the float representation of the 32-bits. After that it converts it into scientific notation by dividing and multiplying my zero for greater than 1 and less than 1 respectively. It then returns the string and the program prints it and exits. To convert from binary it uses the functions used by calc.



"# ComputerArithmetic" 
