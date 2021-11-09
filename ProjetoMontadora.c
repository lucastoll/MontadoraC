// João Mendes
// Lucas Fernandes Tolotto
// Pedro Henrique Todineyb Santos
// Rafael Ramos do Rosário

// ponteiro -> membro da estrutura
// estrutura (membro) . dados da estrutura

// duvidas
// na tabela de visualização como fica o endereço
// como fica a venda dos carros
// deletar uma montadora


#include <stdio.h> //Biblioteca padrão de entrada/saída, printf scanf.
#include <stdlib.h> //emula o prompt de comando, cls pause.
#include <locale.h> //acentuação / linguagem
#include <math.h>  //funções matématicas
#include <ctype.h> //Ascii e manipulação de caracteres to upper to lower
#include <string.h> //Funções string
#include <windows.h> //Cores


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
 union  dadoscarro  tabela;
}loja;


// loja - endereço // loja - union dadoscarro - struct infocarro

// Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main.

void aloca(loja **p,int tam);
int verifica(); //verifica se existe e retorna o registro (qtde)
void cadastro(loja *p,int qtde); //cadastro struct loja
void cadastroend(loja *p);
void grava(loja *p); //grava os dados no ponteiro
void mostra(loja *p, int qtde);
void buscacnpj(loja *p, int qtde);

// Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main.

main()
{
setlocale(LC_ALL, "portuguese");
loja *ploja=NULL;
char op;
int qtde, opmenu, controlemenu=1;
aloca(&ploja,1);

do
{
    system("cls");
    qtde=verifica(); // Função que retorna o número do registro

    printf("REGISTRO MONTADORAS\n");
    printf("\nBem vindo, digite uma das opções abaixo.");
    printf("\n[1] Consulta geral\n[2] Consulta de vendas\n[3] Registrar montadora\n[4] Fechar programa\n\n");
    scanf("%i", &opmenu);
    fflush(stdin);

    switch(opmenu)
    {
        case 1: mostra(ploja,qtde);
        break;

        case 2: buscacnpj(ploja, qtde);

        system("pause");
        break;

        case 3: do{
        cadastro(ploja,qtde+1);
        qtde++;
        if(qtde>=5)
        {
            break;
        }
        printf("\nDeseja continuar <S/N>: ");
        scanf("%c",&op);
        fflush(stdin);
        }while(op!='n' && op!= 'N');
        mostra(ploja,qtde);
        break;

        case 4: controlemenu = 0;
        break;

        default: printf("Opção inválida\a\n");
        system("pause");
        break;
    }
    printf("\nfim");
}while(controlemenu==1);



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
  	fseek(fptr,0,2);   // posiciona fptr no final do arquivo
  	cont=ftell(fptr)/sizeof(loja); //n de bytes do começo do arquivo até a posição atual (fim), dividido pela quantidade de bytes que a estrutura tem, isso da um número inteiro certinho que é o nosso cont, usado nas outras funções como tamanho/qtde
  	fclose(fptr);    // dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
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

cadastroend(p);
fflush(stdin);

p->sold = 0;
p->reserved = 0;
p->tabela.sigla = 'x';

grava(p);
}


void cadastroend(loja *p)
{
printf("Logradouro: ");
gets(p->end.logradouro);
fflush(stdin);

printf("Bairro: ");
gets(p->end.bairro);
fflush(stdin);

printf("CEP: ");
gets(p->end.CEP);
fflush(stdin);

printf("Cidade: ");
gets(p->end.cidade);
fflush(stdin);

printf("Estado: ");
gets(p->end.estado);
fflush(stdin);

printf("Telefone: ");
gets(p->end.fone);
fflush(stdin);

printf("E-mail: ");
gets(p->end.email);
fflush(stdin);
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


struct endereco {
 char logradouro[80];
 char bairro[15];
 char CEP[10];
 char cidade[15];
 char estado[3];
 char fone[12];
 char email[40];
};
*/


void grava(loja *p) //grava os dados depois dos inputs na void cadastro
{
FILE *fptr=NULL;
if((fptr=fopen("concessionaria.bin","ab"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(loja),1,fptr);
fclose(fptr);   //fora do else - por conta do ab (ab sempre cria, então a ação de fechar tem que estar fora do else pra acontecer sempre)
}

void mostra(loja *p,int qtde)
{
int i, j;
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
        if(i==0)
            printf("------------------------------------------------------------------------------------------------------------------\n");
	  	printf("\t\t\t\t\t\t%s", (p->nome)); //toupper
	  	printf("\nRegistro: %i\nCNPJ: %s\nLogradouro: %s\nBairro: %s\nCEP: %s\nCidade: %s\nEstado: %s\nTelefone: %s\nEmail: %s\nSold: %i\nReserved: %i\n",p->regloja,p->CNPJ,p->end.logradouro,p->end.bairro,p->end.CEP,p->end.cidade,p->end.estado,p->end.fone,p->end.email, p->sold, p->reserved);
        for(j=0;j<3;j++)
            printf("Tabela %i = %c\n", j, (p->tabela.sigla));
        printf("------------------------------------------------------------------------------------------------------------------\n");
      }
    fclose(fptr);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
  }
printf("\n\n");
system("pause");
}

void buscacnpj(loja *p, int qtde)
{

int i, j, achou=0;
FILE *fptr=NULL;
char pcnpj[30];
system("cls");
printf("Digite o CNPJ que deseja buscar: ");
gets(pcnpj);
fflush(stdin);

if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  	for(i=0;i<qtde;i++)
  	  {
	  	fseek(fptr,i*sizeof(loja),0);
	  	fread(p,sizeof(loja),1,fptr);
	  	if(strcmp(pcnpj, p->CNPJ)==0)
            {
            system("cls");
            printf("\nCNPJ Encontrado.");
            printf("\nNome: %s\nSold: %i\nReserved: %i\n", p->nome, p->sold, p->reserved);
            for(j=0;j<3;j++)
                printf("Tabela %i = %c\n", j, (p->tabela.sigla));
            achou=1;
            }
      }
    fclose(fptr);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
  }

if(achou==0)
{
    printf("CNPJ não encontrado! verifique na consulta e tente novamente.");
}
printf("\n\n");
}

