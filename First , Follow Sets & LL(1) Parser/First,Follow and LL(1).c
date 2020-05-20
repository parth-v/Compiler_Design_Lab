#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

char prod[MAX][MAX],first[MAX],str[MAX],first_arr[MAX][MAX],follow_arr[MAX][MAX],flag;
int prod_n=0,num=0,k=0,e=0,m=0;

void follow(char c)
{
	int i ,j;
	if(prod[0][0]==c){
 		str[m++]='$';
 	}
 	for(i=0;i<10;i++)
 	{
  		for(j=2;j<10;j++)
  		{
   			if(prod[i][j]==c)
   			{
    			if(prod[i][j+1]!='\0'){
					first_fo(prod[i][j+1],i,(j+2));
 				}
    			if(prod[i][j+1]=='\0'&&c!=prod[i][0]){
     				follow(prod[i][0]);
				}
   			}   
  		}
 	}
}
void first_fo(char c,int x ,int y)
{
    int k;
    if(!(isupper(c)))
		str[m++]=c;
	else{
		int i=0,j=1;
		for(i=0;i<prod_n;i++)
		{
			if(first_arr[i][0] == c)
				break;
		}
		while(first_arr[i][j] != '!')
		{
			if(first_arr[i][j] != '#'){
				str[m++] = first_arr[i][j];
			}
			else{
				if(prod[x][y] == '\0'){
					follow(prod[x][0]);
				}
				else{
					first_fo(prod[x][y],x,y+1);
				}
			}
			j++;
		}
	}
}
void first_f(char c,int x,int y)
{
	int j;
	if(!(isupper(c))){
		first[num++]=c;
	}
	for(j=0;j<prod_n;j++)
	{
		if(prod[j][0]==c)
		{
			if(prod[j][2]=='#'){
				if(prod[x][y] == '\0')
					first[num++]='#';
				else if(prod[x][y] != '\0' && (x != 0 || y != 0))
				{
					first_f(prod[x][y], x, (y+1));
				}
				else
					first[num++]='#';
			}
			else if(!isupper(prod[j][2])){
				first[num++]=prod[j][2];
			}
			else {
				first_f(prod[j][2], j, 3);
			}
		}
	}	
}


int main()
{
	int i=0,choice=0,set=0,ptr=-1,jm=0,km=0,ptr1=0,ptr2=0,check=0;
	char c,ch,final[prod_n];
	printf("Enter the no of productions(each rule separate):");
	scanf("%d",&prod_n);
	printf("\nEnter the productions(form:S=X)(use # for epsilon):\n",prod_n);
	for(i=0;i<prod_n;i++)
		scanf("%s%c",prod[i],&ch);
	for(i=0;i<prod_n;i++)
	{
		if(prod[i][0]==prod[i][2])
		{
			printf("\nThe given grammar is not LL(1)!");
			exit(0);
		}
	}
	for(k=0;k<prod_n;k++){
		for(set=0;set<100;set++){
			first_arr[k][set] = '!';
		}
	}
	printf("\nFirst Sets:\n");
	for(k=0;k<prod_n;k++)
	{
		c=prod[k][0];
		ptr2 = 0;
		check = 0;
		for(set = 0; set <= ptr; set++)
			if(c == final[set])
				check = 1;
		if (check == 1)
			continue;
		first_f(c,0,0);
		ptr+=1;
		final[ptr] = c;
		printf("\nFirst(%c)={",c);
		first_arr[ptr1][ptr2++] = c;
		for(i=0+jm;i<num;i++){
			int lark = 0,chk = 0;
  			for(lark=0;lark<ptr2;lark++){
  				if (first[i] == first_arr[ptr1][lark]){
  					chk = 1;
  					break;
				}
			}
			if(chk == 0){
  		 		printf("%c,",first[i]);
  				first_arr[ptr1][ptr2++] = first[i];
			}
		}
		printf("}");
		jm=num;
		ptr1++;
	}
	printf("\n");
	char res[prod_n];
	ptr = -1;
	for(k=0;k<prod_n;k++){
		for(set=0;set<100;set++){
			follow_arr[k][set] = '!';
		}
	}
	ptr1 = 0;
	int flag1 = 0;
	printf("\nFollow Sets:\n");
	for(e=0;e<prod_n;e++)
  	{
		flag=prod[e][0];
		ptr2 = 0;
		check = 0;
		for(set = 0; set <= ptr; set++)
			if(flag == res[set])
				check = 1;
		if (check == 1)
			continue;
  		flag1 += 1;
		follow(flag);
  		ptr+=1;
		res[ptr] = flag;
  		printf("\nFollow(%c)={",flag);
  		follow_arr[ptr1][ptr2++] = flag;
  		for(i=0+km;i<m;i++){
  			int lark = 0,chk = 0;
  			for(lark=0;lark<ptr2;lark++){
  				if (str[i] == follow_arr[ptr1][lark]){
  					chk = 1;
  					break;
				}
			}
			if(chk == 0){
  		 		printf("%c,",str[i]);
  				follow_arr[ptr1][ptr2++] = str[i];
  			}
  		}
  		printf("}");
		km=m;
		ptr1++; 
	}
	char ter[10];
	for(k=0;k<10;k++){
		ter[k] = '!';
	}
	int ap,vp,prod_k = 0;
	for(k=0;k<prod_n;k++){
		for(set=0;set<prod_n;set++){
			if(!isupper(prod[k][set]) && prod[k][set]!= '#' && prod[k][set] != '=' && prod[k][set] != '\0'){
				vp = 0;
				for(ap = 0;ap < prod_k; ap++){
					if(prod[k][set] == ter[ap]){
						vp = 1;
						break;
					}
				}
				if(vp == 0){
					ter[prod_k] = prod[k][set];
					prod_k ++;
				}
			}
		}
	}
	ter[prod_k] = '$';
	prod_k++;
	printf("\n\nLL(1) Parsing Table:\n");
	printf("\n---------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t|\t");
	for(ap = 0;ap < prod_k; ap++){
		printf("%c\t\t",ter[ap]);
	}
	printf("\n---------------------------------------------------------------------------------------------------------------------\n");
	char first_prod[prod_n][prod_k];
	for(ap=0;ap<prod_n;ap++){
		int destiny = 0;
		k = 2;
		int ct = 0;
		char temp[100];
		while(prod[ap][k] != '\0'){
			if(!isupper(prod[ap][k])){
				temp[ct++] = prod[ap][k];
				temp[ct++] = '_';
				temp[ct++] = '\0';
				k++;
				break;
			}
			else{
				int zap=0;
				int tuna = 0;
				for(zap=0;zap<prod_n;zap++){
					if(first_arr[zap][0] == prod[ap][k]){
						for(tuna=1;tuna<100;tuna++){
							if(first_arr[zap][tuna] != '!'){
								temp[ct++] = first_arr[zap][tuna];
							}
							else
								break;
						}
					break;
					}
				}
				temp[ct++] = '_';
			}
			k++;
		}
		int z = 0,temp1=0;		
		for(temp1 = 0;temp1<ct;temp1++){
			if(temp[temp1] == '#'){
				z = 1;
			}
			else if(temp[temp1] == '_'){
				if(z == 1){
					z = 0;
				}
				else
					break;
			}
			else{
				first_prod[ap][destiny++] = temp[temp1];
			}
		}
	}
	char table[flag1][prod_k+1];
	ptr = -1;
	for(ap = 0; ap < flag1 ; ap++){
		for(set = 0; set < (prod_k + 1) ; set++){
			table[ap][set] = '!';
		}
	}
	for(ap = 0; ap < prod_n ; ap++){
		flag = prod[ap][0];
		check = 0;
		for(set = 0; set <= ptr; set++)
			if(flag == table[set][0])
				check = 1;
		if (check == 1)
			continue;
		else{
			ptr = ptr + 1;
			table[ptr][0] = flag;
		}
	}
	for(ap = 0; ap < prod_n ; ap++){
		int temp1 = 0;
		while(first_prod[ap][temp1] != '\0'){
			int to,ni=0;
			for(to=0;to<prod_k;to++){
				if(first_prod[ap][temp1] == ter[to]){
					ni = 1;
				}
			}
			if(ni == 1){
				char xz = prod[ap][0];
				int cz=0;
				while(table[cz][0] != xz){
					cz = cz + 1;
				}
				int vz=0;
				while(ter[vz] != first_prod[ap][temp1]){
					vz = vz + 1;
				}
				table[cz][vz+1] = (char)(ap + 65);
			}
			temp1++;
		}
	}
	for(k=0;k<prod_k;k++){
		for(set=0;set<100;set++){
			if(first_arr[k][set] == '!'){
				break;
			}
			else if(first_arr[k][set] == '#'){
				int fz = 1;
				while(follow_arr[k][fz] != '!'){
					char xz = prod[k][0];
					int cz=0;
					while(table[cz][0] != xz){
						cz = cz + 1;
					}
					int vz=0;
					while(ter[vz] != follow_arr[k][fz]){
						vz = vz + 1;
					}
					table[k][vz+1] = '#';
					fz++;	
				}
				break;
			}
		}
	}
	for(ap = 0; ap < flag1 ; ap++){
		printf("\t%c\t|\t",table[ap][0]);
		for(set = 1; set < (prod_k + 1) ; set++){
			if(table[ap][set] == '!')
				printf("\t\t");
			else if(table[ap][set] == '#')
				printf("%c=#\t\t",table[ap][0]);
			else{
				int num1 = (int)(table[ap][set]);
				num1 -= 65;
				printf("%s\t\t",prod[num1]);
			}
		}
		printf("\n");
	}
	int j;
	printf("\n\nEnter the result1 string(followed by $):");
	char result1[100];
	scanf("%s%c",result1,&ch);
	printf("\n\n---------------------------------------------------------------------------\n");
	printf("\n\tStack\t\t\tInput\t\t\tAction");
	printf("\n---------------------------------------------------------------------------\n");
	int val = 0,val1 = 1;
	char stack[100];
	stack[0] = '$';
	stack[1] = table[0][0];
	while(val1 != -1){
		int val2 = 0;
		printf("\t");
		for(val2=0;val2<=val1;val2++){
			printf("%c",stack[val2]);
		}
		printf("\t\t\t");
		val2 = val;
		while(result1[val2] != '\0'){
			printf("%c",result1[val2]);
			val2++;
		}
		printf("\t\t\t");
		char arrx = result1[val],arry = stack[val1];
		val1--;
		if(!isupper(arry)){
			if(arrx == arry){
				val++;
				printf("POP\n");
			}
			else{
				printf("\n\nInput String Rejected!\n");
				exit(0);
			}
		}
		else{
			for(i=0;i<prod_k;i++){
				if(ter[i] == arrx)
					break;
			}
			char resf[100];
			for(j=0;j<flag1;j++){
				if(arry == table[j][0]){
					if (table[j][i+1] == '#'){
						printf("%c=#\n",table[j][0]);
						resf[0] = '#';
						resf[1] = '\0';
					}
					else if(table[j][i+1] != '!'){
						int num1 = (int)(table[j][i+1]);
						num1 -= 65;
						strcpy(resf,prod[num1]);
						printf("%s\n",resf);
					}
					else{
						printf("\n\nInput String Rejected!\n");
						exit(0);
					}
				}
			}
			int len = strlen(resf);
			len = len - 1;
			if(len == 0){
				continue;
			}
			for(j=len;j>=2;j--){
				val1++;
				stack[val1] = resf[j];
			}
		}
	}
	if (result1[val] == '\0')
		printf("\n\nInput String Accepted!\n");
	else
		printf("\n\nInput String Rejected!\n");
}



