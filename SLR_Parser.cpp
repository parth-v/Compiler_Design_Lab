#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define MAX 100
using namespace std;

struct gramr
{
    int prod_count;
    char prod[100][100]={{}};
};

void augg(struct gramr *G,struct gramr *H){
    if(H->prod[0][0]=='S')
        strcpy(G->prod[0],"Z->.S");
    else{
        strcpy(G->prod[0],"S->.");
        G->prod[0][4]=H->prod[0][0];}
    G->prod_count++;
}

void dots(struct gramr *H)
{
    for(int i=0;i<H->prod_count;i++){
        for (int j=99;j>3;j--)
            H->prod[i][j] = H->prod[i][j-1];
        H->prod[i][3]='.';
    }
}

bool ifnont(char a)
{
   if (a >= 'A' && a <= 'Z')
        return true;
    else
        return false;
}

bool ifstt(struct gramr *H,char *a)
{
    for(int i=0;i<H->prod_count;i++)
        if(!strcmp(H->prod[i],a))
            return true;
    return false;
}

int nterm,nnont;
char term[MAX]={},nonterm[MAX]={};
void getdata(struct gramr *H)
{
    cout<<"Enter the no. of productions:";
    cin>>H->prod_count;
    cout<<"Enter the no. of non-terminals:";
    cin>>nnont;
    cout<<"Enter the non-terminals:";
    for(int i=0;i<nnont;i++)
        cin>>nonterm[i];
    cout<<"Enter the no. of terminals:";
    cin>>nterm;
    cout<<"Enter the terminals:";
    for(int i=0;i<nterm;i++)
        cin>>term[i];
    cout<<"Enter the productions(form:E->T+E):\n";
    for(int i=0;i<H->prod_count;i++){
        cin>>H->prod[i];
    }
}

char chgdot(char a[100])
{
    char b;
    for(int i=0;i<strlen(a);i++)
    {
	    if(a[i]=='.')
		{
            b=a[i+1];
            return b;
		}
	}
}

char* locdot(char b[100],int len)
{
    char a[100]={};
    strcpy(a,b);
    for(int i=0;i<len;i++)
	{
        if(a[i]=='.')
		{
            swap(a[i],a[i+1]);
            break;
        }
    }
    return &a[0];
}

bool prevst(struct gramr *G,struct gramr *H)
{
    if (G->prod_count != H->prod_count)
        return false;

    for (int i=0; i<G->prod_count; i++)
    {
        int flag = 0;
        for (int j=0; j<H->prod_count; j++)
            if (strcmp(G->prod[i], H->prod[j]) == 0)
                flag = 1;
        if (flag == 0)
            return false;
    }
    return true;
}
char table[MAX][MAX],reduce[MAX][MAX],follow[MAX][MAX],fo_co[MAX][MAX],first[MAX][MAX];
void closure(struct gramr *H,struct gramr *G)
{
    char a={};
    for(int i=0;i<G->prod_count;i++)
	{
        a=chgdot(G->prod[i]);
        if(ifnont(a))
		{
            for(int j=0;j<H->prod_count;j++)
			{
                if(H->prod[j][0]==a)
				{
                    if(!ifstt(G,H->prod[j]))
					{
                        strcpy(G->prod[G->prod_count],H->prod[j]);
                        G->prod_count++;
                    }
                }
            }
        }
    }
}

void gotof(struct gramr *H,struct gramr *S,char a){
    int time=1;
    for(int i=0;i<H->prod_count;i++)
	{
        if(chgdot(H->prod[i])==a)
		{
                if(time==1)
                    time++;
                strcpy(S->prod[S->prod_count],locdot(H->prod[i],strlen(H->prod[i])));
                S->prod_count++;
        }
    }
}

void outprod(struct gramr *H)
{
    for(int i=0;i<H->prod_count;i++)
        printf("%s\n",H->prod[i]);
    cout<<endl;
}

bool in_array(char a[20],char b)
{
    for(int i=0;i<strlen(a);i++)
        if(a[i]==b)
            return true;
    return false;
}

char* chars_after_dots(struct gramr *H)
{
    char a[20]={};
    for(int i=0;i<H->prod_count;i++)
        if(!in_array(a,chgdot(H->prod[i])))
                a[strlen(a)]=chgdot(H->prod[i]);
    return &a[0];
}

void cleanup_prods(struct gramr * G)
{
    char a[100]={};
    for(int i=0;i<G->prod_count;i++)
        strcpy(G->prod[i],a);
    G->prod_count=0;
}

int return_index(char a)
{
    for(int i=0;i<nterm;i++)
        if(term[i]==a)
            return i;
    for(int i=0;i<nnont;i++)
        if(nonterm[i]==a)
            return nterm+i;
}

int retid(char c,char *a)
{
for(int i=0;i<strlen(a);i++)
    if(a[i]==c)
    return i;
}

void fdot(struct gramr* G){
    for(int i=0;i<G->prod_count;i++){
        strcat(G->prod[i],".");
    }
}

void addf(int n,char b){
   for(int i=0;i<strlen(first[n]);i++)
        if(first[n][i]==b)
            return;
    first[n][strlen(first[n])]=b;
}

void addf(int m,int n)
{
    for(int i=0;i<strlen(first[n]);i++){
            int flag=0;
        for(int j=0;j<strlen(first[m]);j++){
            if(first[n][i]==first[m][j])
                flag=1;
        }
        if(flag==0)
            addf(m,first[n][i]);
    }
}

void addfo(int n,char b)
{
   for(int i=0;i<strlen(follow[n]);i++)
        if(follow[n][i]==b)
            return;
    follow[n][strlen(follow[n])]=b;
}

void addfo(int m,int n)
{
    for(int i=0;i<strlen(follow[n]);i++){
            int flag=0;
        for(int j=0;j<strlen(follow[m]);j++){
            if(follow[n][i]==follow[m][j])
                flag=1;
        }
        if(flag==0)
            addfo(m,follow[n][i]);
    }
}

void addff(int m,int n)
{
    for(int i=0;i<strlen(first[n]);i++){
            int flag=0;
        for(int j=0;j<strlen(follow[m]);j++){
            if(first[n][i]==follow[m][j])
                flag=1;
        }
        if(flag==0)
            addfo(m,first[n][i]);
    }
}

void isfit(struct gramr *G)
{
    for(int i=0;i<nnont;i++){
        for(int j=0;j<G->prod_count;j++){
            if(G->prod[j][0]==nonterm[i]){
                if(!ifnont(G->prod[j][3])){
                    addf(i,G->prod[j][3]);
                    }

            }
        }
    }
}

void iffollow(struct gramr *G)
{
    for(int i=0;i<nnont;i++)
	{
        for(int j=0;j<G->prod_count;j++){
            for(int k=3;k<strlen(G->prod[j]);k++){
                if(G->prod[j][k]==nonterm[i]){
                    if(G->prod[j][k+1]!='\0'){
                        if(!ifnont(G->prod[j][k+1])){
                            addfo(i,G->prod[j][k+1]);
                        }
                    }
                }
            }
        }
    }
}

int retid(int *arr,int n)
{
    for(int i=0;i<nterm;i++){
        if(arr[i]==n)
            return i;
    }
    return -1;
}
void outshf(int nost)
{
    cout<<endl<<"\tSHIFT ACTION\t\tGOTO"<<endl;
	cout<<"-----------------------------------------------------"<<endl;
    cout<<"\t";
    for(int i=0;i<nterm;i++)
        cout<<term[i]<<"\t";
    for(int i=0;i<nnont;i++)
        cout<<nonterm[i]<<"\t";
    cout<<endl;
    for(int i=0;i<nost;i++)
	{
        int arr[nnont+nterm]={-1};
        for(int j=0;j<nost;j++){
            if(table[i][j]!='~'){
                    arr[return_index(table[i][j])]= j;
            }
        }
        cout<<"I"<<i<<"\t";
        for(int j=0;j<nnont+nterm;j++){
            if(i==1&&j==nterm-1)
                cout<<"ACC"<<"\t";
            if(arr[j]==-1||arr[j]==0)
                cout<<"\t";
            else{
            if(j<nterm)
                cout<<"S"<<arr[j]<<"\t";
            else
                cout<<arr[j]<<"\t";

            }
        }
        cout<<"\n";
    }
}


void outred(int nost,int *no_re,struct gramr *temp1)
{
    cout<<"\tREDUCE ACTION"<<endl<<"--------------------------------------"<<endl;
    cout<<"\t";
    int arr[temp1->prod_count][nterm]={-1};
    for(int i=0;i<nterm;i++){
        cout<<term[i]<<"\t";
    }
    cout<<endl;
    for(int i=0;i<temp1->prod_count;i++)
	{
	    int n=no_re[i];
	    for(int j=0;j<strlen(follow[return_index(temp1->prod[i][0])-nterm]);j++){
	        for(int k=0;k<nterm;k++){
	            if(follow[return_index(temp1->prod[i][0])-nterm][j]==term[k])
	                arr[i][k]=i+1;
	        }
	    }
	    cout<<"I"<<n<<"\t";
	    for(int j=0;j<nterm;j++){
	        if(arr[i][j]!=-1&&arr[i][j]!=0&&arr[i][j]<nost)
	            cout<<"R"<<arr[i][j]<<"\t";
	        else
	            cout<<"\t";
	    }
	    cout<<endl;
	}
}

int main()
{
    struct gramr gram;
    int nost=1;
    getdata(&gram);
    struct gramr temp,temp1;
    temp=gram;
    temp1=temp;
    dots(&gram);

    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            table[i][j]='~';


	cout<<"\nCanonical LR(0) Collection is:\n";
    struct gramr G[50];
    augg(&G[0],&gram);
    closure(&gram,&G[0]);
    cout<<"\nI0:\n";
    outprod(&G[0]);

    char chs[20]={};
    for(int i=0;i<nost;i++)
	{
        char chs[20]={};
        for(int z=0;z<G[i].prod_count;z++)
                if(!in_array(chs,chgdot(G[i].prod[z])))
                chs[strlen(chs)]=chgdot(G[i].prod[z]);


        for(int j=0;j<strlen(chs);j++)
		{
            gotof(&G[i],&G[nost],chs[j]);
            closure(&gram,&G[nost]);
            int flag=0;
            for(int k=0;k<nost-1;k++){
                if(prevst(&G[k],&G[nost])){
                    cleanup_prods(&G[nost]);flag=1;
                    cout<<"GOTO(I"<<i<<","<<chs[j]<<") = I"<<k<<".\n";
                    table[i][k]=chs[j];;
                    break;
                }
            }
            if(flag==0){
                nost++;
                cout<<"GOTO(I"<<i<<","<<chs[j]<<") = I"<<nost-1<<":\n";
                table[i][nost-1]=chs[j];
                outprod(&G[nost-1]);
            }
        }
    }

    int no_re[temp.prod_count]={-1};
    term[nterm]='$';nterm++;

    fdot(&temp1);
    for(int i=0;i<nost;i++)
	{
        for(int j=0;j<G[i].prod_count;j++)
            for(int k=0;k<temp1.prod_count;k++)
                 if(ifstt(&G[i],temp1.prod[k]))
                        no_re[k]=i;
    }

    isfit(&temp);
    for(int l=0;l<nnont;l++)
	{
	    for(int i=0;i<temp.prod_count;i++){
	        if(ifnont(temp.prod[i][3])){
	            addf(return_index(temp.prod[i][0])-nterm,return_index(temp.prod[i][3])-nterm);
	        }
	    }
	}

    iffollow(&temp);
    addfo(0,'$');
    for(int l=0;l<nnont;l++)
	{
        for(int i=0;i<temp.prod_count;i++){
            for(int k=3;k<strlen(temp.prod[i]);k++){
                if(temp.prod[i][k]==nonterm[l]){
                        if(ifnont(temp.prod[i][k+1])){
                            addff(l,return_index(temp.prod[i][k+1])-nterm);}
                        if(temp.prod[i][k+1]=='\0')
                            addfo(l,return_index(temp.prod[i][0])-nterm);
                            }
                    }
            }
    }
    
    cout<<"\nSLR(1) Parsing Table:\n";
    outshf(nost);
    cout<<endl<<endl;
    outred(nost,&no_re[0],&temp1);
}
