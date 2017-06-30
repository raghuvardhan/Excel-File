#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char sheet[26][26][100];

void intialize(){
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < 26; j++){
			strcpy(sheet[i][j],"0");
		}
	}
}

int pow(int x, unsigned int y)
{
	if (y == 0)
		return 1;
	else if (y % 2 == 0)
		return pow(x, y / 2)*pow(x, y / 2);
	else
		return x*pow(x, y / 2)*pow(x, y / 2);
}

int isValue(char* str){
	for (int i = 0; str[i] != '\0'; i++){
		if (!isdigit(str[i])){
			return 0;
		}
	}
	return 1;
}

int toNum(char *str){
	int num = 0;
	for (int i = 0; str[i] != '\0'; i++){
		num = num * 10 + (str[i] - '0');
	}
	return num;
}

int PerformOperation(char operation, int operand1, int operand2)
{
	if (operation == '+')
		return operand1 + operand2;
	else if (operation == '-')
		return operand1 - operand2;
	else if (operation == '*')
		return operand1 * operand2;
	else if (operation == '^')
		return pow(operand1, operand2);
	return -1;
}

int eval(int row, int col){
	if (isValue(sheet[row][col]) == 1){
		return toNum(sheet[row][col]);
	}
	char op[2] = "\0";
	op[0] = sheet[row][col][2];
	char oper1[3], oper2[3];
	oper1[0] = sheet[row][col][0];
	oper1[1] = sheet[row][col][1];
	oper1[2] = '\0';
	int op1, op2;
	if (isValue(oper1) != 1){
		op1 = eval(sheet[row][col][0] - 97, sheet[row][col][1] - '0' - 1);
	}
	else{
		op1 = toNum(oper1);
	}
	oper2[0] = sheet[row][col][3];
	oper2[1] = sheet[row][col][4];
	oper2[2] = '\0';
	if (isValue(oper2) != 1){
		op2 = eval(sheet[row][col][3] - 97, sheet[row][col][4] - '0' - 1);
	}
	else{
		op2 = toNum(oper2);
	}
	return PerformOperation(op[0], op1, op2);
}

void print(){
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < 26; j++){
			printf("%d ", eval(i, j));
		}
		printf("\n");
	}
}

char* strtok(char * str, char *comp)
{
	static int pos;
	static char *s;
	int i = 0, start = pos;

	if (str != NULL)
		s = str;

	i = 0;
	int j = 0;
	while (s[pos] != '\0')
	{
		j = 0;
		while (comp[j] != '\0')
		{
			if (s[pos] == comp[j])
			{
				s[pos] = '\0';
				pos = pos + 1;
				if (s[start] != '\0')
					return (&s[start]);
				else
				{
					start = pos;
					pos--;
					break;
				}
			}
			j++;
		}
		pos++;
	}
	s[pos] = '\0';
	if (s[start] == '\0')
		return NULL;
	else
		return &s[start];
}


int main(void){
	intialize();
	printf("Enter the values in the cells:\n");
	printf("Enter N to exit\n");
	char str[100];
	int ch = 1;
	while (ch == 1){
			char *tokens[2];
			char temp[100];
			printf(">");
			scanf("%s", str);
			char *token = strtok(str, "=");
			int row = token[0] - 97;
			int col = token[1] - '0' - 1;
			token = strtok(NULL, "=");
			strcpy(sheet[row][col],token);
			printf("enter 1 to continue\n");
			scanf("%d", &ch);
			print();
	}
	getchar();
	system("pause");
}