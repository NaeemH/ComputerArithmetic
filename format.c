#include "format.h"

/* minimum required number of parameters */
#define MIN_REQUIRED 3

/* display usage */
void help(char* error) {
	printf("%s\n", error);
	printf("Usage: ./format <OPTIONS>\n\n<OPTIONS>\n [-h]\t\t help\n [argument]\t <input bit sequence> <type>\n");
	exit(EXIT_FAILURE);
	return;
}

int main  ( int argc, char **argv ) {
	double time_spent;
	clock_t tic=clock(), toc;
#ifdef DEBUG
	printf("IN MAIN\n");
#endif
	/*Displays Help Command*/

	if(argc!=MIN_REQUIRED) {	help("WRONG NUMBER OF ARGUMENTS");}
	if(!strcmp(argv[1], "-h")){	help("HELP: ");}

	if(argc== MIN_REQUIRED){	checkArgs(argv[1], argv[2] );}

	format(argv[1], argv[2]);
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

/*checks arguments for validity*/
void checkArgs(char* arg1, char* arg2){
	int i;
#ifdef DEBUG
	printf("IN ARG CHECK\n");
#endif
	if(strlen(arg1) != 32){
		help("THERE MUST BE 32 BITS");
	}
	for(i=0; i<strlen(arg1); i++){
		if(arg1[i] != '1' && arg1[i] != '0')
			help("INVALID BINARY NUMBER");
	}
	if(strcmp(arg2, "int")!=0){
		if(strcmp(arg2, "float")!=0){
			help("INVALID FORMAT");
		}
	}


#ifdef DEBUG
	printf("OUTARG CHECK\n");
#endif
	return;
}


// Functions to Parse data

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
// Basic formatting operations

void format(char* binary, char* type){
	struct number * ieee = (struct number *)malloc(sizeof(struct number));
	signed long decimal;
	char* sigDecimal;
	int i;
	bool infinity = true;
	bool nan = true;
	ieee->sign = binary[0] == '1'? 1: 0;
	ieee->negative = binary[0] == '1' ? true: false;
	for(i=1; i<9; i++){
		if(binary[i] == '0'){
			infinity = false;
			nan = false;
			break;
		}
	}
	for(i=9; i<33; i++){
		if(binary[i] == '1'){
			infinity = false;
			break;
		}
	}
	if(nan == true){
		for(i=9; i<33; i++){
			if(binary[i] == '1'){
				nan = true;
				break;
			}else{
				nan=false;
			}
		}

	}
	if(nan == true){
		printf("NaN");
		exit(EXIT_SUCCESS);
	}
	if(infinity == true){
		if(ieee->negative == false)
			printf("pinf");
		else
			printf("ninf");
		exit(EXIT_SUCCESS);
	}

	if(!strcmp(type, "int") && ieee->negative == false){
		decimal = conBinToDec(removeFirst(binary));
		printf("INTEGER: %ld \n", decimal);
	}
	if(!strcmp(type, "int") && ieee->negative == true){
		decimal = conBinToDec(twoComp(removeFirst(binary)));
		printf("INTEGER: %ld \n", (-1)*decimal);
	}
	if(!strcmp(type, "float") && ieee->negative == false){
		sigDecimal = floatParse(removeFirst(binary));
		printf("FLOAT: %s \n", sigDecimal);
	}
	if(!strcmp(type, "float") && ieee->negative == true){
		/*printf("TWOS COMPLEMENT: %s\n", twoComp(binary));*/
		sigDecimal = floatParse(removeFirst(twoComp(binary)));
		printf("FLOAT:-%s \n", sigDecimal);
	}
}

char* twoComp(char* str){
	char* temp = (char*)malloc(strlen(str)+1);
	int i, len=strlen(str);
	bool test=true;
	strcpy(temp, str);
	temp = reverseString(temp);
	/*printf("ORIGINAL STRING: %s REVERSED STRING: %s", str, temp);*/
	for(i = 0; i<len; i++){
		if(test == false){
			temp[i] = temp[i] =='1' ? '0': '1';
		}
		if(temp[i] == '1' && test==true){
			test = false;
		}


	}
	temp = reverseString(temp);
	/*printf("Flipped Bit %s\n", temp);*/
	return temp;
}

char* floatParse(char* number){
	char* tempNum = (char*) malloc(strlen(number)+1);
	char* exponent = (char*)malloc(sizeof(char)*9);
	char* mantissa = (char*)malloc(sizeof(char)*24);
	char* final;
	int i, j=0;
	signed long numExponent;
	float numMantissa, total, expo = 1;
	bool zero = true;
	/*printf("NUMBER T0 PARSE %s", number);*/
	for(i=0; i<strlen(number); i++){
		if(number[i] == '1'){
			zero = false;
		}
	}
	if(zero==true){
		return "0.0e0";
	}
	strcpy(tempNum, number);
	for(i=0; i<8; i++){
		exponent[i] = number[i];
	}
	for(i=8; i<32; i++){
		mantissa[j] = number[i];
		j++;
	}
	exponent[8] = '\0';
	numExponent =  conBinToDec(exponent)-127;
	numMantissa = conBinToDec0(mantissa);
	/*printf("EXPONENT: %ld\nMANTISSA %f\n",numExponent, numMantissa);*/
	if(numExponent <0){
		for(i=0; i<-1*numExponent; i++){
			expo /= 2;
			/*printf("%f\n",expo );*/

		}
	}
	if(numExponent>0)
		total = numMantissa * (1<<numExponent);
	else
		total = numMantissa * expo;


	final = sigFig(total);
	/*printf("TOTAL : %f\n", total);*/
	return final;
}

char* sigFig(float total){
	int exponent=0;
	char* output;
	/*printf("TOTAL %f\n", total);*/
	if(total == 0){
		exponent = 0;
		total = 0;
	}
	else if(total >= 1){
		while(total > 10){
			total /= 10;
			exponent++;
		}
	}
	else if(total < 1 && total >0){
		while(total <1){
			total *= 10;
			exponent--;
		}
	}
	output=(char*)malloc(sizeof(char)*33);
	sprintf(output, "%fe%d\n", total, exponent);
	return output;
}





// Converts
float conBinToDec0(char* binary){
	int i;
	float total=0;
	float temp = .5;
#ifdef DEBUG
	printf("IN BIN TO DEC <0\n");
#endif
	/*printf("TOTAL: %f \t TEMP: %f\n", total, temp);*/
	for(i=0; i<strlen(binary); i++){
		if(binary[i] == '1'){
			total +=temp;
		}
		temp /=2;
		/*printf("TOTAL: %.6f \t TEMP: %.6f\n", total, temp);*/
	}
	/*printf("TOTAL FLOAT: %f\n", total);*/
#ifdef DEBUG
	printf("OUT BIN TO DEC <0\n");
#endif
	return (total+1);
}




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
#ifdef DEBUG
	printf("%lu %lu %d %s\n", dec, total, i, bin);
#endif
	while(i>=0){
		if(dec%2 == 0)
			bin[i] = '0';
		else if(dec%2 == 1)
			bin[i] = '1';
		dec/=2;
		i--;
	}
#ifdef DEBUG
	printf("%ld %ld %d %s\n", dec, total, i, bin);
#endif
#ifdef DEBUG
	printf("OUT DEC2BIN\n");
#endif
	return bin;

}


// Linked List functions

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
	while(ptr!=NULL){
		/*printf("%d", ptr->val);*/
		ptr=ptr->next;
	}
	printf("\n");
#ifdef DEBUG
	printf("OUT BINLIST\n");
#endif
	return front;
}
