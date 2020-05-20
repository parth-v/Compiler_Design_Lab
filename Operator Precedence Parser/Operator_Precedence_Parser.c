#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int i=0,tp=0,l=0;
char op[9]={'+','-','*','/','^','i','(',')','$'};
char matrix[9][9]={
'>','>','<','<','<','<','<','>','>',
'>','>','<','<','<','<','<','>','>',
'>','>','>','>','<','<','<','>','>',
'>','>','>','>','<','<','<','>','>',
'>','>','>','>','<','<','<','>','>',
'>','>','>','>','>','e','e','>','>',
'<','<','<','<','<','<','<','>','e',
'>','>','>','>','>','e','e','>','>',
'<','<','<','<','<','<','<','<','>',
};

int func_op(char c)
{
	switch(c)
	{
		case '+':return 0;
		case '-':return 1;
		case '*':return 2;
		case '/':return 3;
		case '^':return 4;
		case 'i':return 5;
		case '(':return 6;
		case ')':return 7;
		case '$':return 8;
	}
}
char stk[6],stack[50],*arr;
int shift()
{
	stack[++tp]=*(arr+i++);
	stack[tp+1]='\0';
}
char stkk[][5]={")E(","E*E","E+E","i","E^E"};
int reduce()
{
	int i,len,found,t;
	for(i=0;i<5;i++)
	{
		len=strlen(stkk[i]);
		if(stack[tp]==stkk[i][0]&&tp+1>=len)
		{
			found=1;
			for(t=0;t<len;t++)
			{
				if(stack[tp-t]!=stkk[i][t])
				{
					found=0;
					break;
				}
			}
			if(found==1)
			{
				stack[tp-t+1]='E';
				tp=tp-t+1;
				strcpy(stk,stkk[i]);
				stack[tp+1]='\0';
				return 1;
			}
		}
	}
	return 0;
}
void outstk()
{
	int j;
	for(j=0;j<=tp;j++)
	printf("%c",stack[j]);
}
void outip()
{
	int j;
	for(j=i;j<l;j++)
	printf("%c",*(arr+j));
}
int main()
{
	arr=(char*)malloc(50*sizeof(char));
	printf("Operator Precedence Parser\n");
	printf("\nOperator precedence table:\n\n\t");
	int a,b;
	for(a=0;a<9;a++)
		printf("%c\t",op[a]);
	printf("\n");
	for(a=0;a<9;a++)
	{
		printf("\n%c\t",op[a]);
		for(b=0;b<9;b++)
		{
			printf("%c\t",matrix[a][b]);
		}
	}
	printf("\n\nEnter the input string(ending with $):");
	scanf("%s",arr);
	l=strlen(arr);
	strcpy(stack,"$");
	printf("\nSTACK\tINPUT\tACTION");
	while(i<l)
	{
		shift();
		printf("\n");
		outstk();
		printf("\t");
		outip();
		printf("\tShift");
		if(matrix[func_op(stack[tp])][func_op(arr[i])]=='>')
		{
			while(reduce())
			{
				printf("\n");
				outstk();
				printf("\t");
				outip();
				printf("\tReduced: E->%s",stk);
			}
		}
	}
	if(strcmp(stack,"$E$")==0)
		printf("\n\nInput String Accepted!");
	else
		printf("\n\nInput String Rejected!");
}
