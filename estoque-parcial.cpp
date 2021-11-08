#include <stdio.h>
#include <stdlib.h>

typedef struct dados{
        int    reg;
        char   produto[20];
        int    qtde;
        float  preco;
        } dados ;

void aloca(dados **p,int tam);
int verifica();
void cadastro(dados *p,int qtde);
void grava(dados *p);
void mostra(dados *p,int qtde);

main()
{
dados *pd=NULL;
char op;
int qtde;

aloca(&pd,1);
qtde=verifica();
do{
	cadastro(pd,qtde+1);
	qtde++;
	printf("\nDeseja continuar <S/N>: ");
	scanf("%c",&op);
	fflush(stdin);
  }while(op!='n' && op!= 'N');
mostra(pd,qtde);  
}//main

void aloca(dados **p,int tam)
{
if((*p=(dados*)realloc(*p,tam*sizeof(dados)))==NULL)
  exit(1);
}//aloca

int verifica()
{
FILE *fptr=NULL;
long int cont=0;
if((fptr=fopen("estoque.bin","rb"))==NULL)
  return cont;
else
  {
  	fseek(fptr,0,2);   //posiciona fptr no final do arquivo
  	cont=ftell(fptr)/sizeof(dados);
  	fclose(fptr);     //dentro do else - por conta rb
  	return cont;
  }//else
}//verifica

void cadastro(dados *p,int qtde)
{
p->reg=qtde;
printf("\nRegistro: %i",p->reg);
printf("\nProduto: ");
gets(p->produto);
fflush(stdin);
printf("Qtde: ");
scanf("%i",&(p->qtde));
fflush(stdin);
printf("Preco: ");
scanf("%f",&(p->preco));
fflush(stdin);
grava(p);
}//cadastro

void grava(dados *p)
{
FILE *fptr=NULL;
if((fptr=fopen("estoque.bin","ab"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(dados),1,fptr);
fclose(fptr);   //fora do else - por conta do ab  
}//grava

void mostra(dados *p,int qtde)
{
int i;
FILE *fptr=NULL;
system("cls");
if((fptr=fopen("estoque.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  	for(i=0;i<qtde;i++)
  	  {
	  	fseek(fptr,i*sizeof(dados),0);
	  	fread(p,sizeof(dados),1,fptr);
	  	printf("\nRegistro: %i\nProduto: %s\nQtde: %i\nPreco: %.2f\n",p->reg,p->produto,p->qtde,p->preco);
      }//for
    fclose(fptr);   //dentro do else - por conta rb
  }//else
printf("\n\n");
system("pause");
}//mostra
