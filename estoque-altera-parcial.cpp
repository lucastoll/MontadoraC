#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados{
        int    reg;
        char   produto[20];
        int    qtde;
        float  preco;
        } dados ;

void aloca(dados **p,int tam);
int verifica();
void cadastro(dados *p);
void altera(dados *p);
int busca(dados *p,int num_reg);
void grava(dados *p,char *str,int pos);
void mostra(dados *p);

main()
{
dados *pd=NULL;
int op;

aloca(&pd,1);
do{
	system("cls");
	printf("\n[1]Cadastro\n[2]Altera\n[3]Mostra\n[4]Fim\nOpcao: ");
	scanf("%i",&op);
	fflush(stdin);
	switch(op)
	  {
	  	case 1: cadastro(pd);
	  			break;
	  	case 2: altera(pd);
	  			break;
	  	case 3: mostra(pd);
	  	        break;
	  }//switch
  }while(op!=4);
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

void cadastro(dados *p)
{
int qtde;
qtde=verifica();   //qtos registros tem no arquivo
p->reg=qtde+1;
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
grava(p,"ab",1);
}//cadastro

void altera(dados *p)
{
int num_reg,pos;

mostra(p);
printf("\nDigite o registro a ser alterado: ");
scanf("%i",&num_reg);
fflush(stdin);
pos=busca(p,num_reg);
if(pos==-1)   //nao achou
  printf("\nRegistro inexistente\n\n");
else
  {
  	printf("\nRegistro: %i\nProduto: %s\nQtde: %i\nPreco: %.2f\n\n",p->reg,p->produto,p->qtde,p->preco);
  	printf("\nNOVO preco: ");
  	scanf("%f",&(p->preco));
  	fflush(stdin);
  	grava(p,"rb+",pos);
  	printf("\nPreco alterado com sucesso\n\n");
  }//else
}//altera

void grava(dados *p,char *str,int pos)
{
FILE *fptr=NULL;
if((fptr=fopen("estoque.bin",str))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  	if(strcmp(str,"rb+")==0)
  	  fseek(fptr,pos*sizeof(dados),0);
  	fwrite(p,sizeof(dados),1,fptr);
  }//else
fclose(fptr);   //fora do else - por conta do ab ou rb+
}//grava

int busca(dados *p,int num_reg)
{
FILE *fptr=NULL;
int i,achou=-1,qtde;
qtde=verifica();
system("cls");
if((fptr=fopen("estoque.bin","rb"))==NULL)
  printf("\nErro");
else
  {
  	for(i=0;i<qtde;i++)
  	  {
  	  	fseek(fptr,i*sizeof(dados),0);  //caminho com fptr dentro do arquivo
  	  	fread(p,sizeof(dados),1,fptr);
  	  	if(p->reg==num_reg)
  	  	 {
  	  	 	achou=i;   //posicao do registro
  	  	 	i=qtde;    //garantir a saida do for
		 }//if
	  }//for
	 fclose(fptr);    //DENTRO do else - pois abriu com rb
  }//else
return achou;
}//busca

void mostra(dados *p)
{
int i,qtde;
FILE *fptr=NULL;
qtde=verifica();
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
