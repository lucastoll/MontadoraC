// João Mendes
// Lucas Fernandes Tolotto
// Pedro Henrique Todineyb Santos
// Rafael Ramos do Rosário

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Estruturas

struct endereco {
 char logradouro[80];
 char bairro[15];
 char CEP[10];
 char cidade[15];
 char estado[3];
 char fone[12];
 char email[40];
};

struct infocarro {
 char sigla;
 int regcarro;
};


union dadoscarro {
 char sigla;
 struct infocarro reservado;
};


typedef struct loja{
 int regloja; //gerar automático -long int
 char nome[30];
 char CNPJ[19];
 struct endereco end;
 int sold;
 int reserved;
 union  dadoscarro  tabela[3];
}loja;

// Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main.

void aloca(loja **p,int tam);
int verifica(); //verifica se existe e retorna o registro (qtde)
void cadastro(loja *p,int qtde); //cadastro struct loja
void grava(loja *p); //grava os dados no ponteiro
void mostra(loja *p,int qtde);

// Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main.

main()
{
setlocale(LC_ALL, "portuguese");
loja *ploja=NULL;
char op;
int qtde;

aloca(&ploja,1);
qtde=verifica(); // Função que retorna o número do registro
do{
	cadastro(ploja,qtde+1);
	qtde++;
	printf("\nDeseja continuar <S/N>: ");
	scanf("%c",&op);
	fflush(stdin);
  }while(op!='n' && op!= 'N');
mostra(ploja,qtde);
}//main

// Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main.

void aloca(loja **p,int tam)
{
if((*p=(loja*)realloc(*p,tam*sizeof(loja)))==NULL)
  exit(1);
}

int verifica()
{
FILE *fptr=NULL;
long int cont=0;
if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  return cont;
else
  {
  	fseek(fptr,0,2);   //posiciona fptr no final do arquivo
  	cont=ftell(fptr)/sizeof(loja);
  	fclose(fptr);     //dentro do else - por conta rb
  	return cont;
  }
}

void cadastro(loja *p,int qtde)
{
p->regloja=qtde;
printf("\nID Registro: %i",p->regloja);
printf("\nNome: ");
gets(p->nome);
fflush(stdin);
printf("CNPJ (Ex: 11.444.777/0001-61): ");
gets(p->CNPJ);
fflush(stdin);


grava(p);
}

/*
typedef struct loja{
 int regloja; //gerar automático
 char nome[30];
 char CNPJ[19];
 struct endereco end;
 int sold;
 int reserved;
 union  lojacarro  tabela[3];
}loja;
*/


void grava(loja *p) //grava os dados depois dos inputs na void cadastro
{
FILE *fptr=NULL;
if((fptr=fopen("concessionaria.bin","ab"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(loja),1,fptr);
fclose(fptr);   //fora do else - por conta do ab
}

void mostra(loja *p,int qtde)
{
int i;
FILE *fptr=NULL;
system("cls");
if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  	for(i=0;i<qtde;i++)
  	  {
	  	fseek(fptr,i*sizeof(loja),0);
	  	fread(p,sizeof(loja),1,fptr);
	  	printf("\nRegistro: %i\nNome: %s\nCNPJ: %s\n",p->regloja,p->nome,p->CNPJ);
      }
    fclose(fptr);   //dentro do else - por conta rb
  }
printf("\n\n");
system("pause");
}
