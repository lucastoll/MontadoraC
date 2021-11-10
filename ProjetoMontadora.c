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
// função unica ou uma pra cada
// printar em tabela
// typedef duas estruturas
// só ponteiro pra estrutura ou usar em mais coisas.

#include <stdio.h> //Biblioteca padrão de entrada/saída, printf scanf.
#include <stdlib.h> //emula o prompt de comando, cls pause.
#include <locale.h> //acentuação / linguagem
#include <math.h>  //funções matématicas
#include <ctype.h> //Ascii e manipulação de caracteres to upper to lower
#include <string.h> //Funções string
#include <windows.h> //Cores

//Estruturas - Estruturas - Estruturas - Estruturas - Estruturas - Estruturas - Estruturas - Estruturas - Estruturas - Estruturas - Estruturas.

//concessionária.bin

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


typedef struct loja{ //estrutura principal de cadastro
 int regloja; //gerar automático - long int
 char nome[30];
 char CNPJ[19];
 struct endereco end;
 int sold;
 int reserved;
 union  dadoscarro  tabela;
}loja;

//carro.bin

struct infoloja {
char sigla;
char CNPJ[19];
};

union dadosloja {
char sigla;
struct infoloja reserva;
};

typedef struct montadora { //estrutura principal de cadastro
int regcarro; //gerar automático - long int
char modelo[20];
char cor[10];
float valor;
union dadosloja status;
}montadora;

// Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main.
//portal

//concessionária.bin

void alocaloja(loja **p, int tam);
int verificaconc(); //verifica se existe e retorna o registro (qtde)
void cadastroconc(loja *p, int qtde); //cadastro struct loja
void cadastroend(loja *p);
void gravaconc(loja *p); //grava os dados no ponteiro
void mostraconc(loja *p, int qtde);
void buscacnpj(loja *p, int qtde);

//carros.bin

void alocacarro(montadora **p, int tam);
int verificacarro();
void cadastrocarro(montadora *p, int qtde);
void gravacarro(montadora *p, int qtde);
void mostracarro(montadora *p, int qtde);
void buscastatus(montadora *p, int qtde);

// Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main.

int main()
{
setlocale(LC_ALL, "portuguese");
loja *ploja=NULL;
montadora *pcarros=NULL;
char op;
int qtde, qtdecarro, opmenu=1, controlemenu=1, opconc, mconc=1, opcarro, mcarro=1;
alocaloja(&ploja,1);
alocacarro(&pcarros, 1);

do // menu principal - montadora ou carros
{
system("cls");
printf("SISTEMA ESTOQUE MONTADORA\n\nBem vindo, digite uma das opções abaixo.\n[1] Registro concessionária\n[2] Registro de carros\n[3] Encerrar programa\n\n");
scanf("%i", &opmenu);
switch(opmenu)
{
        case 1: mconc=1; //controle dowhile concessionaria
        do //concessionaria
        {
        system("cls");
        qtde=verificaconc(); // Função que retorna o número do registro

        printf("REGISTRO CONCESSIONÁRIA\n\nBem vindo, digite uma das opções abaixo.\n[1] Consulta geral\n[2] Consulta de vendas\n[3] Registrar concessionária\n[4] Menu principal\n\n");
        scanf("%i", &opconc);
        fflush(stdin);
        switch(opconc)
        {
            case 1: mostraconc(ploja,qtde);
            break;

            case 2: buscacnpj(ploja, qtde);
            system("pause");
            break;

            case 3: do{
            if(qtde>=5)
            {
                printf("Quantidade máxima de montadoras já foi atingida.");
                system("pause");
                break;
            }
            cadastroconc(ploja,(qtde++)+1);
            printf("\nDeseja continuar <S/N>: ");
            scanf("%c",&op);
            fflush(stdin);
            }while(op!='n' && op!= 'N');
            mostraconc(ploja,qtde);
            break;

            case 4: mconc = 0;
            break;

            default: printf("Opção inválida\a\n");
            system("pause");
            break;
        }//switch
        }while(mconc==1);
        break; //fim menu concessionaria

        case 2: mcarro = 1; //controle carro
        do{
        system("cls");
        qtdecarro = verificacarro();
        printf("REGISTRO DE CARROS - MONTADORA\n\n[1] Consulta geral\n[2] Consulta parcial\n[3] Registrar carros\n[4] Menu principal\n\n");
        scanf("%i", &opcarro);
        fflush(stdin);
        switch(opcarro)
        {
            case 1: system("cls");
            mostracarro(pcarros, qtdecarro);
            break;

            case 2: system("cls");
            buscastatus(pcarros, qtdecarro);
            break;

            case 3: system("cls");
            cadastrocarro(pcarros, (qtdecarro++)+1);
            mostracarro(pcarros, qtdecarro);
            break;

            case 4: mcarro = 0;
            break;

            default: printf("Opção inválida\a\n");
            system("pause");
            break;
        }

        }while(mcarro==1);
        system("pause");
        break;

        case 3: controlemenu = 0; //encerrar programa
        break;

        default: printf("Opção inválida\a\n");
        system("pause");
        break;
}
}while(controlemenu==1);
printf("creditos");
}//main fim

// Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main.

// concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin

void alocaloja(loja **p,int tam)
{
if((*p=(loja*)realloc(*p,tam*sizeof(loja)))==NULL)
  exit(1);
}

int verificaconc()
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

void cadastroconc(loja *p,int qtde)
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
p->tabela.sigla = 'L';

gravaconc(p);
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

void gravaconc(loja *p) //grava os dados depois dos inputs na void cadastro
{
FILE *fptr=NULL;
if((fptr=fopen("concessionaria.bin","ab"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(loja),1,fptr);
fclose(fptr);   //fora do else - por conta do ab (ab sempre cria, então a ação de fechar tem que estar fora do else pra acontecer sempre)
}

void mostraconc(loja *p,int qtde)
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

// carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin
//portal

void alocacarro(montadora **p,int tam)
{
if((*p=(montadora*)realloc(*p,tam*sizeof(montadora)))==NULL)
  exit(1);
}

int verificacarro()
{
FILE *fptr=NULL;
long int cont=0;
if((fptr=fopen("carro.bin","rb"))==NULL)
  return cont;
else
  {
  	fseek(fptr,0,2);   // posiciona fptr no final do arquivo
  	cont=ftell(fptr)/sizeof(montadora); //n de bytes do começo do arquivo até a posição atual (fim), dividido pela quantidade de bytes que a estrutura tem, isso da um número inteiro certinho que é o nosso cont, usado nas outras funções como tamanho/qtde
  	fclose(fptr);    // dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
  	return cont;
  }
}

void cadastrocarro(montadora *p, int qtde)
{
float price=0;

p->regcarro = qtde;
printf("Digite o modelo do carro: ");
gets(p->modelo);
fflush(stdin);

printf("Digite a cor do carro: ");
gets(p->cor);
fflush(stdin);

printf("Digite o valor do carro: ");
scanf("%f", &price);
p->valor = price;

p->status.sigla = 'L';
gravacarro(p, qtde);
}

void gravacarro(montadora *p, int qtde)
{
FILE *fptr=NULL;
if((fptr=fopen("carro.bin","ab"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(montadora),1,fptr);
fclose(fptr);   //fora do else - por conta do ab (ab sempre cria, então a ação de fechar tem que estar fora do else pra acontecer sempre)
}

void mostracarro(montadora *p, int qtde)
{
int i, j;
FILE *fptr=NULL;
system("cls");
if((fptr=fopen("carro.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  	for(i=0;i<qtde;i++)
  	  {
	  	fseek(fptr,i*sizeof(montadora),0);
	  	fread(p,sizeof(montadora),1,fptr);
        if(i==0)
            printf("------------------------------------------------------------------------------------------------------------------\n");
        printf("\nID: %i\nModelo: %s\nCor: %s\nValor: R$%.2f\nStatus: %c\n",p->regcarro, p->modelo, p->cor, p->valor, p->status.sigla);
        printf("\n------------------------------------------------------------------------------------------------------------------\n");
      }
    fclose(fptr);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
  }
printf("\n\n");
system("pause");
}

void buscastatus(montadora *p, int qtde)
{
int i, j, achou=0;
FILE *fptr=NULL;
char cstatus;
system("cls");
printf("Consulta parcial\n\nL - Carros com status livre\nR - Carros com status reservado\n\nDigite a sigla: ");
scanf("%c", &cstatus);
fflush(stdin);

if((fptr=fopen("carro.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  	for(i=0;i<qtde;i++)
  	  {
	  	fseek(fptr,i*sizeof(montadora),0);
	  	fread(p,sizeof(montadora),1,fptr);
	  	if(p->status.sigla == cstatus)
            {
            if(achou==0)
                printf("\n------------------------------------------------------------------------------------------------------------------\n");
            printf("\nID: %i\nModelo: %s\nCor: %s\nValor: R$%.2f\nStatus: %c\n",p->regcarro, p->modelo, p->cor, p->valor, p->status.sigla);
            printf("\n------------------------------------------------------------------------------------------------------------------\n");
            achou=1;
            }
      }
    fclose(fptr);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
  }

if(achou==0)
{
    printf("Nenhum carro com o status indicado foi encontrado.");
}
printf("\n\n");
system("pause");
}
