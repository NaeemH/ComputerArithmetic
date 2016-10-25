 // calc.c
 // Naeem Hossain
 // nh302
 // October 16, 2016
 // Computer Architecture

//Program that adds and subtracts numbers specified in different bases
 
#include "calc.h"

/* minimum required number of parameters */
#define MIN_REQUIRED 5

/* display usage */
void help(char* error) {
#ifdef DEBUG
	printf("IN HELP\n");
#endif
	printf("%s\n", error);
	printf("Usage: ./calc <OPTIONS>\n\n<OPTIONS>\n [-h]\t\t help\n [argument]\t <op> <number1> <number2> <output base>\n");
	exit(EXIT_FAILURE);
#ifdef DEBUG
	printf("OUT HELP\n");
#endif
}



int main  ( int argc, char **argv ) {
	double time_spent;
	clock_t tic=clock(), toc;
#ifdef DEBUG
	printf("IN MAIN\n");
#endif
	// Displays help command

	if(argc!=MIN_REQUIRED) {	help("WRONG NUMBER OF ARGUMENTS");}
	if(!strcmp(argv[1], "-h")){	help("HELP: ");}
	if(argc == 5){	checkArgs(argv[1], argv[2], argv[3], argv[4]);}

	if(!strcmp(argv[1], "+")){	add(argv[2], argv[3], argv[4]);	}
	if(!strcmp(argv[1], "-")){	subs(argv[2], argv[3], argv[4]);}
	if(!strcmp(argv[1], "*")){	mult(argv[2], argv[3], argv[4]);}

	toc = clock();
	time_spent=(double)(toc-tic)/CLOCKS_PER_SEC;
	time_spent=time_spent/1000000;
#ifdef DEBUG
	printf("\n =========\n TIME SPENT: %.032f \n =========\n", time_spent);
#endif
#ifdef DEBUG
	printf("OUT OF MAIN\n");
#endif
	return 0;
}

//checks arguments for validity
void checkArgs(char* arg1, char* arg2, char* arg3, char* arg4){
	int i;
#ifdef DEBUG
	printf("IN ARG CHECK\n");
#endif
	/*check for correct operation*/
	if(arg1[0] != '+' && arg1[0] != '-' && arg1[0] != '*'){
		help("WRONG OPERATION");
	}
	if(arg2[0] == '-'){
		arg2 = removeFirst(arg2);
	}
	if(arg3[0] == '-'){
		arg3 = removeFirst(arg3);
	}
	/*check for number and base validity for first number*/
	switch(arg2[0]){
		case 'b':
			for(i=1; i<strlen(arg2); i++){
				if(arg2[i] != '1' && arg2[i] != '0')
					help("INVALID BINARY NUMBER");
			}
			break;
		case 'd':
			for(i=1; i<strlen(arg2); i++){
				if((int)arg2[i] > (int)'9' || (int)arg2[i] < (int)'0'){
					help("INVALID DECIMAL NUMBER");
				}
			}
			break;
		case 'x':
			for(i=1; i<strlen(arg2); i++){
				if((int)arg2[i] > (int)'9' || (int)arg2[i] < (int)'0' ){
					if((int)arg2[i] < (int)'A' || (int)arg2[i] > (int)'F')
						help("INVALID HEXADECIMAL NUMBER");
				}
			}
			break;
		case 'o':
			for(i=1; i<strlen(arg2); i++){
				if((int)arg2[i] > (int)'7' || (int)arg2[i] < (int)'0'){
					help("INVALID OCTAL NUMBER");
				}
			}
			break;
		default:
			help("WRONG INPUT BASE");
	}
	/*check for number and base validity for second number*/
	switch(arg3[0]){
		case 'b':
			for(i=1; i<strlen(arg3); i++){
				if(arg3[i] != '1' && arg3[i] != '0')
					help("INVALID BINARY NUMBER");
			}
			break;
		case 'd':
			for(i=1; i<strlen(arg3); i++){
				if((int)arg3[i] > (int)'9' || (int)arg3[i] < (int)'0'){
					help("INVALID DECIMAL NUMBER");
				}
			}
			break;
		case 'x':
			for(i=1; i<strlen(arg3); i++){
				if((int)arg3[i] > (int)'9' || (int)arg3[i] < (int)'0' ){
					if((int)arg3[i] < (int)'A' || (int)arg3[i] > (int)'F')
						help("INVALID HEXADECIMAL NUMBER");
				}
			}
			break;
		case 'o':
			for(i=1; i<strlen(arg3); i++){
				if((int)arg3[i] > (int)'7' || (int)arg3[i] < (int)'0'){
					help("INVALID OCTAL NUMBER");
				}
			}
			break;
		default:
			help("WRONG INPUT BASE");
	}
	/*printf("ARG4: %s\n", arg4);*/

	/*check for correct output base*/
	if(arg4[0] != 'b' && arg4[0] != 'd' && arg4[0] != 'o' && arg4[0] != 'x'){
		help("INVALID OUTPUT BASE");
	}
	if(arg4[1] != '\0'){
		help("INVALID OUTPUT BASE");
	}
#ifdef DEBUG
	printf("OUT ARG CHECK\n");
#endif
	return;
}

//Arithmatic Functions

/*Add the numbers*/
void add(char* number1, char* number2, char* outbase){
	struct number * num1 = parseNum(number1);
	struct number * num2 = parseNum(number2);
	signed long int total=0, dec1, dec2;
	char * totalBin;
	char * totalHex;
	char * totalOct;
#ifdef DEBUG
	printf("IN ADD\n");
#endif
	dec1 = num1->negative == true ? num1->decimal*(-1): num1->decimal;
#ifdef DEBUG
	printf("DECIMAL 1: %ld\n", dec1);
#endif
	dec2 = num2->negative == true ? num2->decimal*(-1): num2->decimal;
#ifdef DEBUG
	printf("DECIMAL 2: %ld\n", dec2);
#endif
	total = dec1 + dec2;
	/*printf("%ld %ld \n", total, total*(-1));*/
	totalBin = total>0 ? conDecToBin(total): conDecToBin(total*(-1));
	/*total>0 ? printf("LEFT "): printf("RIGHT");*/
	/*
	   if(total>0)
	   totalHex = conDecToHex(total);
	   else
	   totalHex = conDecToHex(total*(-1));
	   */
	totalHex = total>0 ? conDecToHex(total): conDecToHex(total*(-1));
	totalOct = total>0 ? conDecToOct(total): conDecToOct(total*(-1));

	/*	totalHex = total>0 ? conDecToHex(total): conDecToHex(total*(-1));*/
	/*printf("%s\n", conDecToHex(total));*/
	printf("\n************************\nTHE SUM OF %s", num1->original);
	printf(" AND %s ", num2->original);
	total>0 ? printf("IS:\nBINARY: %s \n", totalBin): printf("IS:\nBINARY: (-)%s \n", totalBin);
	printf("DECIMAL: %li \n", total);
	total>0 ? printf("HEXADECIMAL: %s \n", totalHex): printf("HEXADECIMAL: (-)%s \n", totalHex);
	total>0 ? printf("OCTAL:%s \n************************\n", totalOct): printf("OCTAL: (-)%s \n************************\n", totalOct);
#ifdef DEBUG
	printf("OUT ADD\n");
#endif

}

/*Substract the numbers*/
void subs(char* number1, char* number2, char* outbase){
	struct number *num1 = parseNum(number1);
	struct number *num2 = parseNum(number2);
	signed long int total=0, dec1, dec2;
	char * totalBin;
	char * totalHex;
	char * totalOct;
#ifdef DEBUG
	printf("IN SUBTRACT\n");
#endif
	dec1 = num1->negative == true ? num1->decimal*(-1): num1->decimal;
#ifdef DEBUG
	printf("DECIMAL 1: %ld\n", dec1);
#endif
	dec2 = num2->negative == true ? num2->decimal*(-1): num2->decimal;
#ifdef DEBUG
	printf("DECIMAL 2: %ld\n", dec2);
#endif
	total = dec1 - dec2;
	/*printf("%ld %ld \n", total, total*(-1));*/
	totalBin = total>0 ? conDecToBin(total): conDecToBin(total*(-1));
	/*total>0 ? printf("LEFT "): printf("RIGHT");*/
	/*
	   if(total>0)
	   totalHex = conDecToHex(total);
	   else
	   totalHex = conDecToHex(total*(-1));
	   */
	totalHex = total>0 ? conDecToHex(total): conDecToHex(total*(-1));
	totalOct = total>0 ? conDecToOct(total): conDecToOct(total*(-1));

	/*	totalHex = total>0 ? conDecToHex(total): conDecToHex(total*(-1));*/
	/*printf("%s\n", conDecToHex(total));*/
	printf("\n************************\nTHE DIFFERENCE OF %s", num1->original);
	printf(" AND %s ", num2->original);
	total>0 ? printf("IS:\nBINARY: %s \n", totalBin): printf("IS:\nBINARY: (-)%s \n", totalBin);
	printf("DECIMAL: %li \n", total);
	total>0 ? printf("HEXADECIMAL: %s \n", totalHex): printf("HEXADECIMAL: (-)%s \n", totalHex);
	total>0 ? printf("OCTAL:%s \n************************\n", totalOct): printf("OCTAL: (-)%s \n************************\n", totalOct);
#ifdef DEBUG
	printf("OUT SUBTRACT\n");
#endif
}

//Multiply the numbers
void mult(char* number1, char* number2, char* outbase){
	struct number *num1 = parseNum(number1);
	struct number *num2 = parseNum(number2);
	signed long int total=0, dec1, dec2;
	char * totalBin;
	char * totalHex;
	char * totalOct;
#ifdef DEBUG
	printf("IN MULTIPLY\n");
#endif
	dec1 = num1->negative == true ? num1->decimal*(-1): num1->decimal;
#ifdef DEBUG
	printf("DECIMAL 1: %ld\n", dec1);
#endif
	dec2 = num2->negative == true ? num2->decimal*(-1): num2->decimal;
#ifdef DEBUG
	printf("DECIMAL 2: %ld\n", dec2);
#endif
	total = dec1 * dec2;
	/*printf("%ld %ld \n", total, total*(-1));*/
	totalBin = total>0 ? conDecToBin(total): conDecToBin(total*(-1));
	/*total>0 ? printf("LEFT "): printf("RIGHT");*/
	/*
	   if(total>0)
	   totalHex = conDecToHex(total);
	   else
	   totalHex = conDecToHex(total*(-1));
	   */
	totalHex = total>0 ? conDecToHex(total): conDecToHex(total*(-1));
	totalOct = total>0 ? conDecToOct(total): conDecToOct(total*(-1));

	/*	totalHex = total>0 ? conDecToHex(total): conDecToHex(total*(-1));*/
	/*printf("%s\n", conDecToHex(total));*/
	printf("\n************************\nTHE PRODUCT OF %s", num1->original);
	printf(" AND %s ", num2->original);
	total>0 ? printf("IS:\nBINARY: %s \n", totalBin): printf("IS:\nBINARY: (-)%s \n", totalBin);
	printf("DECIMAL: %li \n", total);
	total>0 ? printf("HEXADECIMAL: %s \n", totalHex): printf("HEXADECIMAL: (-)%s \n", totalHex);
	total>0 ? printf("OCTAL:%s \n************************\n", totalOct): printf("OCTAL: (-)%s \n************************\n", totalOct);
#ifdef DEBUG
	printf("OUT MULTIPLY\n");
#endif

}


//Pairing functions
struct number * parseNum(char* number){
	struct number *num;
	signed long dec;
	char type;
#ifdef DEBUG
	printf("IN PARSE NUM\n");
	printf("TYPE: %c", number[0]);
#endif
	num = (struct number *)malloc(sizeof(struct number));
	/*if number is negative*/
	if(number[0]== '-'){
		num->negative = true;
		type = number[1];
		number = removeFirst(number);
		number = removeFirst(number);
		if(type == 'b'){
			num->binary = number;
			dec = conBinToDec(number);
		}else if(type == 'o'){
			num->oct = number;
			dec = conOctToDec(number);
		}else if(type == 'x'){
			num->hex = number;
			dec = conHexToDec(number);
		}else{
			dec = atol(number);
		}
		/*printf("%s\n", number);*/
		num->decimal = dec;
	}else{
		num->negative = false;
		type = number[0];
		number = removeFirst(number);
		if(type == 'b'){
			num->binary = number;
			dec = conBinToDec(number);
		}else if(type == 'o'){
			num->oct = number;
			dec = conOctToDec(number);
		}else if(type == 'x'){
			num->hex = number;
			dec = conHexToDec(number);
		}else{
			dec = atol(number);
		}
		/*printf("%s\n", number);*/
		num->decimal = dec;
	}
	num->original = number;
#ifdef DEBUG
	printf("OUT PARSENUM\n");
#endif
	return num;
}

/*removes first character in string*/
char *removeFirst(char *charBuffer) {
	char *str;
#ifdef DEBUG
	printf("IN REMOVE FIRST\n");
#endif
	if (strlen(charBuffer) == 0)
		str = charBuffer;
	else
		str = charBuffer + 1;
#ifdef DEBUG
	printf("OUT REMOVE FIRST\n");
#endif
	return str;
}

//Reverses string
char* reverseString(char *str)
{
	char temp;
	size_t len = strlen(str) - 1;
	size_t i;
	size_t k = len;

	for(i = 0; i < len; i++)
	{
		temp = str[k];
		str[k] = str[i];
		str[i] = temp;
		k--;

		/* As 2 characters are changing place for each cycle of the loop
		   only traverse half the array of characters */
		if(k == (len / 2))
		{
			break;
		}
	}
	return str;
}

//Converting  functions
signed long conBinToDec(char* binary){
	struct node * binaryList = (struct node *)malloc(sizeof(struct node));
	struct node * ptr;
	long total=0, i=0;
#ifdef DEBUG
	printf("IN BIN2DEC\n");
#endif
	binaryList = binList(binary);
	ptr=binaryList;
	while(ptr!=NULL){
		/*/printf("TOTAL %ld\n", total);*/
		/*/printf("ptr->val %d\n", ptr->val);*/
		if(ptr->val == 1){
			total += 1<<i;
		}
		i++;
		ptr=ptr->next;

	}
	/*printf("\nTOTAL%d\n", total);*/
#ifdef DEBUG
	printf("OUT BIN2DEC\n");
#endif
	return total;
}

signed long conHexToDec(char* hex){
	int len = strlen (hex), i ;
	signed long total;
	char * string = (char *)malloc((len)*4+1), bin[5];
#ifdef DEBUG
	printf("IN HEX2DEC\n");
#endif
	for(i =0; i < len; i++) {
		switch (hex[i]){
			case '0':	strcpy(bin, "0000"); break;
			case '1':	strcpy(bin, "0001"); break;
			case '2':	strcpy(bin, "0010"); break;
			case '3':	strcpy(bin, "0011"); break;
			case '4':	strcpy(bin, "0100"); break;
			case '5':	strcpy(bin, "0101"); break;
			case '6':	strcpy(bin, "0110"); break;
			case '7':	strcpy(bin, "0111"); break;
			case '8':	strcpy(bin, "1000"); break;
			case '9':	strcpy(bin, "1001"); break;
			case 'A':	strcpy(bin, "1010"); break;
			case 'B':	strcpy(bin, "1011"); break;
			case 'C':	strcpy(bin, "1100"); break;
			case 'D':	strcpy(bin, "1101"); break;
			case 'E':	strcpy(bin, "1110"); break;
			case 'F':	strcpy(bin, "1111"); break;
			default: 	printf("INVALID CHARACTER"); exit(EXIT_FAILURE);
		}
		strcat(string, bin);
		/*string[strlen(string)] = '\0';*/
		/*printf("THE STRING : %s\n", string);*/

	}
	/*printf("\n%s in decimal is %ld\n",hex, conBinToDec(string));*/
	total =conBinToDec(string);
#ifdef DEBUG
	printf("OUT HEX2DEC\n");
#endif
	return total;
}

signed long conOctToDec(char* oct){
	int len = strlen (oct), i ;
	signed long total;
	char * string = (char *)malloc((len)*3+1), bin[4];
#ifdef DEBUG
	printf("IN OCT2DEC\n");
#endif
	for(i =0; i < len; i++) {
		switch (oct[i]){
			case '0':	strcpy(bin, "000"); break;
			case '1':	strcpy(bin, "001"); break;
			case '2':	strcpy(bin, "010"); break;
			case '3':	strcpy(bin, "011"); break;
			case '4':	strcpy(bin, "100"); break;
			case '5':	strcpy(bin, "101"); break;
			case '6':	strcpy(bin, "110"); break;
			case '7':	strcpy(bin, "111"); break;
			default: 	printf("INVALID CHARACTER"); exit(EXIT_FAILURE);
		}
		strcat(string, bin);
		string[strlen(string)] = '\0';
		/*printf("THE STRING : %s\n", string);*/

	}
	/*printf("\n%s in decimal is %ld\n",oct, conBinToDec(string));*/
	total =conBinToDec(string);
#ifdef DEBUG
	printf("OUT OCT2DEC\n");
#endif
	return total;

}


char * conDecToBin(signed long dec){
	signed long total;
	int i=0;
	char * bin;
#ifdef DEBUG
	printf("IN DEC2BIN\n");
#endif
	if(dec == 0){
		return "0";
	}
	total=1;
	while(total<=dec){
		total <<=1;
		i++;
	}
	i--;
	bin= (char *)malloc(i+2);
	bin[i+1]='\0';
	while(i>=0){
		if(dec%2 == 0)
			bin[i] = '0';
		else if(dec%2 == 1)
			bin[i] = '1';
		dec/=2;
		i--;
	}
#ifdef DEBUG
	printf("OUT DEC2BIN\n");
#endif
	return bin;

}

char * conDecToHex(signed long dec){
	int i=0;
	char * binary= conDecToBin(dec), bin[5];
	char * string = (char *)malloc((strlen(binary)+1)/4);
	struct node * binaryList = (struct node *)malloc(sizeof(struct node));
	struct node * ptr;
#ifdef DEBUG
	printf("IN DEC2HEX\n");
#endif
	binaryList = binList(binary);
	ptr=binaryList;
	while(ptr!=NULL){
		for(i=0;i<4;i++){
			bin[i] = '\0';
		}

		for(i=0;i<4;i++){
			if(ptr==NULL)
				break;
			bin[i] = ptr->val == 1 ? '1' : '0';
			ptr=ptr->next;
		}
		for(i=0;i<4;i++){
			if(bin[i] == '\0')
				bin[i] = '0';
		}

		bin[4] = '\0';
		if(!strcmp("0000", bin)){	strcat(string, "0");}
		if(!strcmp("0001", bin)){	strcat(string, "8");}
		if(!strcmp("0010", bin)){	strcat(string, "4");}
		if(!strcmp("0011", bin)){	strcat(string, "C");}
		if(!strcmp("0100", bin)){	strcat(string, "2");}
		if(!strcmp("0101", bin)){	strcat(string, "A");}
		if(!strcmp("0110", bin)){	strcat(string, "6");}
		if(!strcmp("0111", bin)){	strcat(string, "E");}
		if(!strcmp("1000", bin)){	strcat(string, "1");}
		if(!strcmp("1001", bin)){	strcat(string, "9");}
		if(!strcmp("1010", bin)){	strcat(string, "5");}
		if(!strcmp("1011", bin)){	strcat(string, "D");}
		if(!strcmp("1100", bin)){	strcat(string, "3");}
		if(!strcmp("1101", bin)){	strcat(string, "B");}
		if(!strcmp("1110", bin)){	strcat(string, "7");}
		if(!strcmp("1111", bin)){	strcat(string, "F");}

		/*printf("Decimal to Binary 4 Digits is:  %s and the whole is: %s\nand hex is : %s\n", bin, binary, string);*/
	}
#ifdef DEBUG
	printf("OUT DEC2HEX\n");
#endif
	reverseString(string);
	return string;

}

char * conDecToOct(signed long dec){
	int i=0;
	char * binary= conDecToBin(dec), bin[4];
	char * string = (char *)malloc((strlen(binary)+1)/3);
	struct node * binaryList = (struct node *)malloc(sizeof(struct node));
	struct node * ptr;
#ifdef DEBUG
	printf("IN DEC2OCT\n");
#endif
	binaryList = binList(binary);
	ptr=binaryList;
	while(ptr!=NULL){
		for(i=0;i<3;i++){
			bin[i] = '\0';
		}

		for(i=0;i<3;i++){
			if(ptr==NULL)
				break;
			bin[i] = ptr->val == 1 ? '1' : '0';
			ptr=ptr->next;
		}
		for(i=0;i<3;i++){
			if(bin[i] == '\0')
				bin[i] = '0';
		}

		bin[3] = '\0';
		if(!strcmp("000", bin)){	strcat(string, "0");}
		if(!strcmp("001", bin)){	strcat(string, "4");}
		if(!strcmp("010", bin)){	strcat(string, "2");}
		if(!strcmp("011", bin)){	strcat(string, "6");}
		if(!strcmp("100", bin)){	strcat(string, "1");}
		if(!strcmp("101", bin)){	strcat(string, "5");}
		if(!strcmp("110", bin)){	strcat(string, "3");}
		if(!strcmp("111", bin)){	strcat(string, "7");}

		/*printf("Decimal to Binary 4 Digits is:  %s and the whole is: %s\nand hex is : %s\n", bin, binary, string);*/
	}
#ifdef DEBUG
	printf("OUT DEC2OCT\n");
#endif

	return reverseString(string);

}

//Linked List functions for use in sorting, searching, and organizing
struct node * binList(char * binary){
	struct node * front = (struct node *)malloc(sizeof(struct node));
	int len, i;
	struct node * newNode;
	struct node * ptr;
#ifdef DEBUG
	printf("IN BINLIST\n");
#endif
	front->val=binary[0] - '0';
	/*printf("%d\n", front->val);*/
	len = strlen (binary);
	for(i =1; i < len; i++) {
		newNode = (struct node *)malloc(sizeof(struct node));
		newNode->val =binary[i] - '0';
		newNode->next = front;
		front = newNode;
		/*		printf("%d\n", newNode->val);*/
	}
	ptr=front;
	i=0;
	/*printf("BINARY REVERSE FOR %s\t is ", binary);*/
	/*while(ptr!=NULL){
	  printf("%d", ptr->val);
	  ptr=ptr->next;
	  }
	  printf("\n");*/
#ifdef DEBUG
	printf("OUT BINLIST\n");
#endif
	return front;

}

// THANKS FOR READING MY BLOOD, SWEAT, AND TEARS