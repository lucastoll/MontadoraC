// Grupo 5 TIM2 - Manh�
// Jo�o Matheus de Jesus Mendes     RA 210166
// Lucas Fernandes Tolotto          RA 211046
// Pedro Henrique Todineyb Santos   RA 210131
// Rafael Ramos do Ros�rio          RA 210814

// duvidas
// acentua��o nao funciona quando cadastra dados no arquivo, so funciona nos prints normais do menu.

// coisas pra fazer chique
// 1 - tratamento inputs (receber s� informa��es validas)
// 2 - tratamento valor (no print R$120.000,00)
// 3 - intro anima��o
// 4 - fun��o printar carro colorido
// 5 - printar hor�rio no menu

// ponteiro -> membro da estrutura
// estrutura (membro) . dados da estrutura

#include <stdio.h>   // Biblioteca padr�o de entrada/sa�da, printf scanf.
#include <stdlib.h>  // Emula o prompt de comando, cls pause.
#include <locale.h>  // Acentua��o e linguagem
#include <string.h>  // Fun��es string
#include <windows.h> // Cores
#include <time.h>    // Data automatica


//Estruturas.
//concession�ria.bin
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
 int regloja;
 char nome[30];
 char CNPJ[19];
 struct endereco end;
 int sold;
 int reserved;
 union  dadoscarro  tabela[3];
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

typedef struct montadora {
int regcarro;
char modelo[20];
char cor[10];
float valor;
union dadosloja status;
}montadora;

//historico.bin
struct data {
int dia;
int mes;
int ano;
};

typedef struct historicoVendas {
int reghist;
int regcarro;
char modelo[20];
char cor[10];
float valor;
int regloja;
char nome[30];
char cnpj[19];
struct data dataVenda;
}historicoVendas;

// Fun��es antes da main.
// fun��es universais.
void aloca(loja **ploja, montadora **pmontadora,  historicoVendas **phistorico, int tam, int seletor);
int verifica(loja **ploja, montadora **pmontadora,  historicoVendas **phistorico, int seletor);
void reserva(loja *ploja, montadora *pmontadora, int qtdeconc, int qtdecarro);
void venda(loja *ploja, montadora *pmontadora, historicoVendas *phistorico, int qtdeconc, int qtdecarro, int qtdehistorico);
void creditos();

// fun��es concession�ria.bin
void cadastroconc(loja *p, int qtde);
void cadastroend(loja *p);
void gravaconc(loja *p);
void mostraconc(loja *p, int qtde);
void buscacnpj(loja *p, int qtde);
void alteraconc(loja *p, int qtde);

// fun��es carros.bin
void cadastrocarro(montadora *p, int qtde);
void gravacarro(montadora *p, int qtde);
void mostracarro(montadora *p, int qtde);
void buscastatus(montadora *p, int qtde);
void alteracarro(montadora *p, int qtde);

// fun��es historico.bin
void historicoeasteregg(historicoVendas *p, int qtde);
void histconc(historicoVendas *phistorico, loja *ploja, int qtdehistorico, int qtdeloja);
void histcarro(historicoVendas *phistorico, montadora *pmontadora, int qtdehistorico, int qtdecarro);

// Main.
int main()
{
setlocale(LC_ALL, "portuguese");
time_t t = time(NULL); //data automatica
struct tm tm = *localtime(&t);

loja *ploja=NULL;
montadora *pcarros=NULL;
historicoVendas *phistorico=NULL;

char op, op2;
int qtde, qtdecarro, qtdehistorico, opmenu=1, controlemenu=1, opconc, mconc=1, opcarro, mcarro=1, opreserva, mreserva=1;
aloca(&ploja, &pcarros, &phistorico, 1, 1);
aloca(&ploja, &pcarros, &phistorico, 1, 2);
aloca(&ploja, &pcarros, &phistorico, 1, 3);

do // menu principal
{
qtde = verifica(&ploja, &pcarros,  &phistorico, 1);
qtdecarro = verifica(&ploja, &pcarros, &phistorico, 2);
qtdehistorico = verifica(&ploja, &pcarros, &phistorico, 3);
system("cls");
printf("=====================================================");
printf("\nSISTEMA ESTOQUE MONTADORA     |      Data: %i/%i/%i",  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
printf("\nCONCESSION�RIAS NO SISTEMA: %i |\tCARROS NO SISTEMA: %i\n\nBem-vindo(a)!, digite uma das op��es abaixo.\n[1] Registro concession�ria\n[2] Registro de carros\n[3] Registros e vendas\n[4] Encerrar programa\n\n", qtde, qtdecarro);

scanf("%i", &opmenu);
fflush(stdin);
switch(opmenu)
    {
        case 1: mconc=1; //controle menu concessionaria.
        do // Menu concession�ria.
        {
        system("cls");
        printf("REGISTRO CONCESSION�RIA\n\n[1] Consulta geral\n[2] Consulta de vendas\n[3] Registrar concession�ria\n[4] Alterar registro\n[5] Hist�rico de compras por concession�ria\n[6] Menu principal\n\n");
        scanf("%i", &opconc);
        fflush(stdin);
        qtde = verifica(&ploja, &pcarros, &phistorico, 1);
        switch(opconc)
            {
                case 1: mostraconc(ploja,qtde); break;
                case 2: buscacnpj(ploja, qtde); break;

                case 3: do{
                if(qtde>=5) // cadastro de no m�ximo 5 montadoras.
                {
                    printf("Quantidade m�xima de montadoras j� foi atingida.\n");
                    system("pause");
                    break;
                }
                cadastroconc(ploja,(qtde++)+1);
                printf("\nDeseja continuar <S/N>: ");
                scanf("%c", &op);
                fflush(stdin);
                }while(op!='n' && op!= 'N');
                mostraconc(ploja,qtde); break;

                case 4: alteraconc(ploja, qtde); break;
                case 5: histconc(phistorico, ploja, qtdehistorico, qtde); break;
                case 6: mconc = 0; break;

                default: printf("Op��o inv�lida\a\n");
                system("pause"); break;
            }//switch
        }while(mconc==1);
        break; //fim menu concessionaria

        case 2: mcarro = 1; //controle dowhile menu carro
        do{ // Menu carro
        system("cls");
        printf("REGISTRO DE CARROS - MONTADORA\n\n[1] Consulta geral\n[2] Consulta parcial\n[3] Registrar carros\n[4] Alterar registro\n[5] Hist�rico de vendas por modelo\n[6] Menu principal\n\n");
        scanf("%i", &opcarro);
        fflush(stdin);
        qtdecarro = verifica(&ploja, &pcarros, &phistorico, 2);
        switch(opcarro)
            {
                case 1: mostracarro(pcarros, qtdecarro); break;
                case 2: buscastatus(pcarros, qtdecarro); break;

                case 3: do
                    {
                    if(qtdecarro >= 50) // Quantidade m�xima de 50 carros registrados
                    {
                        printf("Quantidade m�xima de carros j� foi atingida.\n");
                        system("pause");
                        break;
                    }
                    cadastrocarro(pcarros, (qtdecarro++)+1);
                    printf("\nDeseja continuar <S/N>: ");
                    scanf("%c", &op2);
                    fflush(stdin);
                    }while(op2!='n' && op2!= 'N');
                    mostracarro(pcarros, qtdecarro);
                    break;

                case 4: alteracarro(pcarros, qtdecarro); break;
                case 5: histcarro(phistorico, pcarros, qtdehistorico, qtdecarro); break;
                case 6: mcarro = 0; break;

                default: printf("Op��o inv�lida\a\n");
                system("pause");
                break;
            }
        }while(mcarro==1);
        break;

        case 3: mreserva=1;
        if(qtde==0)
        {
            printf("\nN�o � possivel realizar reservas ou vendas sem nenhuma concession�ria registrada no sistema!\a\n\n");
            system("pause");
            break;
        }
        else if(qtdecarro==0)
        {
            printf("\nN�o � possivel realizar reservas ou vendas sem nenhum carro registrado no sistema!\a\n\n");
            system("pause");
            break;
        }
        do
        {
            system("cls");
            printf("RESERVAS E VENDAS\n\n[1] Reservas\n[2] Vendas e libera��o\n[3] Menu principal\n\n");
            scanf("%i", &opmenu);
            fflush(stdin);

            switch(opmenu)
            {
            case 1: reserva(ploja, pcarros, qtde, qtdecarro); break;
            case 2: venda(ploja, pcarros, phistorico, qtde, qtdecarro, ((qtdehistorico)+1)); break;
            case 3: mreserva = 0; break;

            default: printf("Op��o inv�lida\a\n");
            system("pause");
            break;
            }
        }while(mreserva==1);
        break;

        case 4: controlemenu = 0; break;
        case 77: historicoeasteregg(phistorico, qtdehistorico); break;

        default: printf("Op��o inv�lida\a\n");
        system("pause");
        break;
    }// Switch menu principal
}while(controlemenu==1); // Menu geral
creditos();
}//main

// Fun��es depois da main.
// fun��es genericas.
void aloca(loja **ploja, montadora **pmontadora, historicoVendas **phistorico, int tam, int seletor)
{
if(seletor==1)      // ploja
    {
    if((*ploja=(loja*)realloc(*ploja,tam*sizeof(loja)))==NULL)
      exit(1);
    }
else if(seletor==2) // pmontadora
    {
    if((*pmontadora=(montadora*)realloc(*pmontadora,tam*sizeof(montadora)))==NULL)
      exit(1);
    }
else                // phistorico
    {
    if((*phistorico=(historicoVendas*)realloc(*phistorico,tam*sizeof(historicoVendas)))==NULL)
      exit(1);
    }
}//aloca

int verifica(loja **ploja, montadora **pmontadora, historicoVendas **phistorico, int seletor)
{
FILE *fptr=NULL;
long int cont=0;

if(seletor==1)      //ploja
    {
        if((fptr=fopen("concessionaria.bin","rb"))==NULL)
          return cont;
        else
          {
            fseek(fptr,0,2);   // posiciona fptr no final do arquivo
            cont=ftell(fptr)/sizeof(loja); //n de bytes do come�o do arquivo at� a posi��o atual (fim), dividido pela quantidade de bytes que a estrutura tem, isso da um n�mero inteiro certinho que � o nosso cont, usado nas outras fun��es como tamanho/qtde
            fclose(fptr);    // dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
            return cont;
          }
    }
else if(seletor==2) //pmontadora
    {
        if((fptr=fopen("carro.bin","rb"))==NULL)
          return cont;
        else
          {
            fseek(fptr,0,2);
            cont=ftell(fptr)/sizeof(montadora);
            fclose(fptr);
            return cont;
          }
    }
else
    {
        if((fptr=fopen("historico.bin","rb"))==NULL)
          return cont;
        else
          {
            fseek(fptr,0,2);
            cont=ftell(fptr)/sizeof(historicoVendas);
            fclose(fptr);
            return cont;
          }
    }
}// verifica

void reserva(loja *ploja, montadora *pmontadora, int qtdeconc, int qtdecarro)
{
    int i, j, l=0, achou=0, idcarro, pos, poscarro, erro=0;
    char pcnpj[30], auxnomeconc[30], auxnomecarro[20], auxcorcarro[10], auxcarrosigla, op;
    FILE *fptrconc=NULL; // ponteiro concession�ria
    FILE *fptrcarro=NULL; // ponteiro carros
    do // dowhile input cnpj
    {
        system("cls");
        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL) //arquivo aberto para mostrar todos os cnpjs disponiveis
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtdeconc;i++)
            {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(ploja,sizeof(loja),1,fptrconc);
                printf("ID - %i | CNPJ - %s\n", ploja->regloja, ploja->CNPJ);
            }
            fclose(fptrconc);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }
        printf("----------------------------------------------------------------------------------------------\n\nDigite o CNPJ da concession�ria que vai efetuar a reserva: ");
        gets(pcnpj);
        fflush(stdin);
        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL) //arquivo aberto para comparar o cnpj recebido com os cnpj do arquivo.
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdeconc;i++)
              {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(ploja,sizeof(loja),1,fptrconc);
                if(strcmp(pcnpj, ploja->CNPJ)==0)
                    {
                    printf("\n----------------------------------------------------------------------------------------------\nCNPJ Encontrado.");
                    printf("\nNome: %s\nSold: %i\nReserved: %i\n", ploja->nome, ploja->sold, ploja->reserved);
                    for(j=0;j<3;j++)
                    {
                        if(ploja->tabela[j].reservado.sigla == 'L')
                            printf("Tabela %i = %c\n", j, (ploja->tabela[j].sigla));
                        else
                            printf("Tabela %i = %c - %i\n", j, ploja->tabela[j].reservado.sigla, ploja->tabela[j].reservado.regcarro);
                    }
                    achou=1;
                    strcpy(auxnomeconc, ploja->nome);
                    }
              }
            fclose(fptrconc);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }

        if(achou==0)
        {
            printf("\nCNPJ n�o encontrado! verifique a digita��o e tente novamente.\n");
            system("pause");
        }
    }while(achou==0);

    achou=0; // variavel resetada para usar do mesmo jeito com o input do carro
    do // dowhile input - ID carro
    {
        printf("----------------------------------------------------------------------------------------------\n\nDigite o ID do carro � ser reservado: ");
        scanf("%i", &idcarro);
        fflush(stdin);

        if((fptrcarro=fopen("carro.bin","rb"))==NULL) // arquivo aberto para comparar o ID recebido com os ID's do arquivo.
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdecarro;i++)
              {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(pmontadora,sizeof(montadora),1,fptrcarro);
                if(pmontadora->regcarro == idcarro)
                    {
                    printf("\n----------------------------------------------------------------------------------------------");
                    printf("\nCarro encontrado\nModelo: %s | Cor: %s | Valor: R$%.2f | Status: %c\n----------------------------------------------------------------------------------------------\n\n",pmontadora->modelo, pmontadora->cor, pmontadora->valor, pmontadora->status.sigla);
                    achou=1;
                    strcpy(auxnomecarro, pmontadora->modelo); // vari�veis auxiliares usadas posteriormente para printar uma confirma��o.
                    strcpy(auxcorcarro, pmontadora->cor);
                    auxcarrosigla = pmontadora->status.sigla;
                    }
              }
            fclose(fptrcarro); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
          }

        if(achou==0)
        {
            printf("\n----------------------------------------------------------------------------------------------");
            printf("\nNenhum carro com o ID indicado foi encontrado.\n");
        }
        else
        {
            printf("Confirmar reserva do carro %s %s na concession�ria %s? <S|N>\n", auxnomecarro, auxcorcarro, auxnomeconc);
            scanf("%c", &op);
            fflush(stdin);
            switch(op)
            {
                case 'n': //tratamento minusculo e maiusculo
                case 'N': printf("Cancelando reserva.");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".\n");
                break;

                case 's':
                case 'S':
                if((fptrconc=fopen("concessionaria.bin","rb"))==NULL) // arquivo aberto para verifica��o e altera��o dos dados concessionaria.bin
                  printf("\nErro ao abrir o arquivo");
                else
                    {
                    for(i=0;i<qtdeconc;i++)
                        {
                        fseek(fptrconc,i*sizeof(loja),0);
                        fread(ploja,sizeof(loja),1,fptrconc);
                        if(strcmp(pcnpj, ploja->CNPJ)==0)
                            {
                            //Verifica��o carro vago (j� vendido)
                            if(strcmp(auxcorcarro,"vago")==0)
                            {
                                printf("\nEsse carro j� foi vendido.\n");
                                fclose(fptrconc);
                                erro=1;
                                break;
                            }
                            //Verifica��o carro 'L'
                            if(auxcarrosigla=='R')
                            {
                                printf("\nEsse carro j� foi reservado\n");
                                fclose(fptrconc);
                                erro=1;
                                break;
                            }
                            //Verifica��o reserved >= 3
                            else if(ploja->reserved >= 3)
                            {
                                printf("Quantidade m�xima de reservas nessa concession�ria j� foi atingida.\n");
                                fclose(fptrconc);
                                erro=1;
                                break;
                            }
                            ploja->reserved += 1;
                            pos = i;
                            i=qtdeconc;
                            // Implementa��o sigla status concession�ria.
                            for(l=0;l<3;l++)
                                {
                                if(ploja->tabela[l].sigla=='L')
                                    {
                                    ploja->tabela[l].reservado.sigla = 'R';
                                    ploja->tabela[l].reservado.regcarro = idcarro;
                                    l=3; //interromper for
                                    }
                                }
                            printf("\n----------------------------------------------------------------------------------------------\nReserva efetuada com sucesso.");
                            // Printar concession�ria novamente, agora que a reserva foi efetuada.
                            printf("\nNome: %s\nSold: %i\nReserved: %i\n", ploja->nome, ploja->sold, ploja->reserved);
                            for(j=0;j<3;j++)
                            {
                                if(ploja->tabela[j].reservado.sigla == 'L')
                                    printf("Tabela %i = %c\n", j, (ploja->tabela[j].sigla));
                                else
                                    printf("Tabela %i = %c - %i\n", j, ploja->tabela[j].reservado.sigla, ploja->tabela[j].reservado.regcarro);
                            }
                            }//if
                        }//for
                    fclose(fptrconc);
                    }//else

                if(erro==0)
                //gravar informa��es na concessionaria.bin
                {
                    if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL)
                      printf("\nErro ao abrir o arquivo");
                    else
                      {
                        fseek(fptrconc, pos*sizeof(loja),0);
                        fwrite(ploja,sizeof(loja),1,fptrconc);
                      }//else
                    fclose(fptrconc);   //fora do else - por conta do ab ou rb+

                    //verifica��o e altera��o na carro.bin
                    if((fptrcarro=fopen("carro.bin","rb"))==NULL)
                      printf("\nErro ao abrir o arquivo");
                    else
                      {
                        for(i=0;i<qtdecarro;i++)
                          {
                            fseek(fptrcarro,i*sizeof(montadora),0);
                            fread(pmontadora,sizeof(montadora),1,fptrcarro);
                            if(pmontadora->regcarro == idcarro)
                                {
                                    pmontadora->status.reserva.sigla='R';
                                    strcpy(pmontadora->status.reserva.CNPJ, pcnpj);
                                    poscarro = i;
                                    i=qtdecarro;
                                }
                          }
                        fclose(fptrcarro); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
                      }

                    //gravar informa��es no carro.bin
                    if((fptrcarro=fopen("carro.bin", "rb+"))==NULL) //acabamento
                      printf("\nErro ao abrir o arquivo");
                    else
                      {
                        fseek(fptrcarro, poscarro*sizeof(montadora),0);
                        fwrite(pmontadora,sizeof(montadora),1,fptrcarro);
                      }
                    fclose(fptrcarro);   //fora do else - por conta do ab ou rb+
                }
                break;

                default: printf("Op��o inv�lida\a\n");
                break;
        }//switch
       }//else
    }while(achou==0);
system("pause");
} // reserva

void venda(loja *ploja, montadora *pmontadora, historicoVendas *phistorico, int qtdeconc, int qtdecarro, int qtdehistorico)
{
    int i, j, l, auxidcarro, auxidloja, achou=0, achoureserva=0, escolhaswitch, posconc, poscarro, controle=0;
    float auxvalorcarro;
    char auxmodelo[20], auxcor[10], auxcnpj[20], auxnomeconc[30];

    time_t t = time(NULL); //data automatica
    struct tm tm = *localtime(&t);

    FILE *fptrcarro=NULL;
    FILE *fptrconc=NULL;
    FILE *fptrhistorico=NULL;
    system("cls");

    printf("Vendas");
    if((fptrcarro=fopen("carro.bin","rb"))==NULL)
      printf("\nErro ao abrir o arquivo");
    else
      {
        for(i=0;i<qtdecarro;i++)
          {
            fseek(fptrcarro,i*sizeof(montadora),0);
            fread(pmontadora,sizeof(montadora),1,fptrcarro);
            if(pmontadora->status.sigla=='R')
                {
                    printf("\nID: %i\t | Status: %c - %s\t | %s %s R$%.2f", pmontadora->regcarro, pmontadora->status.reserva.sigla, pmontadora->status.reserva.CNPJ, pmontadora->modelo, pmontadora->cor, pmontadora->valor);
                    controle+=1;
                }
          }
        fclose(fptrcarro);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
      }

    if(controle==0)
    {
        printf("\nN�o h� carros reservados para realizar a venda ou a libera��o.\n\n");
        system("pause");
    }
    else
    {
        do
    {
        printf("\n-----------------------------------------------------------------------------------------------------\n\nDigite o ID do carro que voc� deseja vender ou liberar: ");
        scanf("%i", &auxidcarro);
        fflush(stdin);
        if((fptrcarro=fopen("carro.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdecarro;i++)
              {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(pmontadora,sizeof(montadora),1,fptrcarro);
                if(pmontadora->regcarro==auxidcarro)
                {
                    if(pmontadora->status.reserva.sigla=='R')
                    {

                    strcpy(auxmodelo, pmontadora->modelo);
                    strcpy(auxcor, pmontadora->cor);
                    strcpy(auxcnpj, pmontadora->status.reserva.CNPJ);
                    auxvalorcarro = pmontadora->valor;
                    achoureserva=1;
                    }
                    achou=1;
                }
              }
            fclose(fptrcarro);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
          }

        if(achou==0)
        {
           printf("ID n�o encontrado, tente novamente.\n");
        }
        else if(achoureserva==0)
        {
            printf("O carro com este ID n�o foi reservado, favor reservar antes de realizar alguma a��o.\n");
        }
    }while(achou==0 || achoureserva==0);
    printf("\n-----------------------------------------------------------------------------------------------------\n\nO que voc� deseja fazer com o carro ID %i - %s %s?.\n\n[1] Vender\n[2] Liberar reserva\n\n", auxidcarro, auxmodelo, auxcor);
    scanf("%i", &escolhaswitch);
    switch(escolhaswitch)
    {
        case 1: // caso vender
        // altera��es concessionaria.bin
        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
            {
            for(i=0;i<qtdeconc;i++)
                {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(ploja,sizeof(loja),1,fptrconc);
                if(strcmp(auxcnpj, ploja->CNPJ)==0)
                    {
                    ploja->reserved -= 1;
                    ploja->sold += 1;
                    posconc = i;
                    i=qtdeconc;
                    strcpy(auxnomeconc, ploja->nome);
                    auxidloja = ploja->regloja;
                    for(l=0;l<3;l++)
                        {
                        if(ploja->tabela[l].sigla=='R' && ploja->tabela[l].reservado.regcarro==auxidcarro)
                            {
                            ploja->tabela[l].reservado.sigla = 'L';
                            l=3; //interromper for
                            }
                        }
                    }//if
                }//for
            fclose(fptrconc);
            }//else


        // altera��es historico.bin
        if((fptrhistorico=fopen("historico.bin","ab"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdehistorico;i++)
              {
                fseek(fptrhistorico,i*sizeof(historicoVendas),0);
                fread(fptrhistorico,sizeof(historicoVendas),1,fptrhistorico);
                if(i==(qtdehistorico-1))
                {
                    phistorico->reghist = qtdehistorico;
                    phistorico->regcarro = auxidcarro;
                    strcpy(phistorico->modelo, auxmodelo);
                    strcpy(phistorico->cor, auxcor);
                    phistorico->valor = auxvalorcarro;
                    phistorico->regloja = auxidloja;
                    strcpy(phistorico->nome, auxnomeconc);
                    strcpy(phistorico->cnpj, auxcnpj);
                    phistorico->dataVenda.dia = tm.tm_mday;
                    phistorico->dataVenda.mes = tm.tm_mon + 1;
                    phistorico->dataVenda.ano = tm.tm_year + 1900;
                } // if
              } // for
          } // else
        fclose(fptrhistorico); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)

        // altera��es carro.bin
        if((fptrcarro=fopen("carro.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdecarro;i++)
              {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(pmontadora,sizeof(montadora),1,fptrcarro);
                if(pmontadora->regcarro == auxidcarro)
                    {
                        pmontadora->status.reserva.sigla='L';
                        pmontadora->valor = 0;
                        strcpy(pmontadora->modelo, "vago");
                        strcpy(pmontadora->cor, "vago");
                        poscarro = i;
                        i=qtdecarro;
                    }
              }
            fclose(fptrcarro); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
          }

        //grava��o historico.bin
        if(qtdehistorico==1)
        {
            if((fptrhistorico=fopen("historico.bin","ab"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
              qtdehistorico++;
              fwrite(phistorico,sizeof(historicoVendas),1,fptrhistorico);
              }
            fclose(fptrhistorico);   //fora do else - por conta do ab (ab sempre cria, ent�o a a��o de fechar tem que estar fora do else pra acontecer sempre)
        }

        else
        {
            if((fptrhistorico=fopen("historico.bin", "rb+"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
                fseek(fptrhistorico, (qtdehistorico-1)*sizeof(historicoVendas),0);
                fwrite(phistorico,sizeof(historicoVendas),1,fptrhistorico);
              }//else
            fclose(fptrhistorico);   //fora do else - por conta do ab ou rb+
        }

        //grava��o carro.bin
        if((fptrcarro=fopen("carro.bin", "rb+"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrcarro, poscarro*sizeof(montadora),0);
            fwrite(pmontadora,sizeof(montadora),1,fptrcarro);
          }//else
        fclose(fptrcarro);   //fora do else - por conta do ab ou rb+

        printf("\n-----------------------------------------------------------------------------------------------------\nVenda do carro ID - %i, %s %s na %s foi confirmada.\n", auxidcarro, auxmodelo, auxcor, auxnomeconc);
        printf("Data da compra: %i/%i/%i\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        // grava��o concessionaria.bin
        if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrconc, posconc*sizeof(loja),0);
            fwrite(ploja,sizeof(loja),1,fptrconc);
          }
        fclose(fptrconc);   //fora do else - por conta do ab ou rb+
        break;

        case 2: // caso liberar reserva
        // altera��es concessionaria.bin
        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
            {
            for(i=0;i<qtdeconc;i++)
                {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(ploja,sizeof(loja),1,fptrconc);
                if(strcmp(auxcnpj, ploja->CNPJ)==0)
                    {
                    ploja->reserved -= 1;
                    posconc = i;
                    i=qtdeconc;
                    strcpy(auxnomeconc, ploja->nome);
                    for(l=0;l<3;l++)
                        {
                        if(ploja->tabela[l].sigla=='R' && ploja->tabela[l].reservado.regcarro==auxidcarro)
                            {
                            ploja->tabela[l].reservado.sigla = 'L';
                            l=3; //interromper for
                            }
                        }
                    }//if
                }//for
            fclose(fptrconc);
            }//else

        // grava��o concessionaria.bin
        if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrconc, posconc*sizeof(loja),0);
            fwrite(ploja,sizeof(loja),1,fptrconc);
          }//else
        fclose(fptrconc);   //fora do else - por conta do ab ou rb+

        // altera��o sigla do carro.bin
        if((fptrcarro=fopen("carro.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdecarro;i++)
              {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(pmontadora,sizeof(montadora),1,fptrcarro);
                if(pmontadora->regcarro == auxidcarro)
                    {
                        pmontadora->status.reserva.sigla='L';
                        poscarro = i;
                        i=qtdecarro;
                    }
              }
            fclose(fptrcarro); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
          }

        // gravar informa��es no carro.bin
        if((fptrcarro=fopen("carro.bin", "rb+"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrcarro, poscarro*sizeof(montadora),0);
            fwrite(pmontadora,sizeof(montadora),1,fptrcarro);
          }
        fclose(fptrcarro);   //fora do else - por conta do ab ou rb+
        printf("Reserva do carro ID - %i, %s %s na %s foi liberada.", auxidcarro, auxmodelo, auxcor, auxnomeconc);
        printf("\n\n");
        break;

        default: printf("Op��o inv�lida\a\n");
        break;
    }

    system("pause");
    }
} // venda

void creditos()
{
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;
GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
saved_attributes = consoleInfo.wAttributes;

printf("\nFeito por: ");
Sleep(1000);
SetConsoleTextAttribute(hConsole, 1);
printf("Lucas Tolotto");
SetConsoleTextAttribute(hConsole, saved_attributes);
printf(", ");
Sleep(1000);
SetConsoleTextAttribute(hConsole, 4);
printf("Pedro Todineyb");
SetConsoleTextAttribute(hConsole, saved_attributes);
printf(", ");
Sleep(1000);
SetConsoleTextAttribute(hConsole, 3);
printf("Jo�o Mendes");
SetConsoleTextAttribute(hConsole, saved_attributes);
printf(", ");
Sleep(1000);
SetConsoleTextAttribute(hConsole, 10);
printf("Rafael Ros�rio");
SetConsoleTextAttribute(hConsole, saved_attributes);
printf(".\n\n");
}

// Fun��es concessionaria.bin - Fun��es concessionaria.bin - Fun��es concessionaria.bin - Fun��es concessionaria.bin - Fun��es concessionaria.bin - Fun��es concessionaria.bin.

void cadastroconc(loja *p,int qtde)
{
int i;
p->regloja=qtde;
fflush(stdin);
printf("\nID Registro: %i",p->regloja);
printf("\nNome [30]: ");
gets(p->nome);
fflush(stdin);

printf("CNPJ (Ex: 11.444.777/0001-61) [19]: ");
gets(p->CNPJ);
fflush(stdin);

cadastroend(p);
fflush(stdin);

p->sold = 0;
p->reserved = 0;
for(i=0;i<3;i++)
    p->tabela[i].sigla = 'L';

gravaconc(p);
}

void cadastroend(loja *p)
{
printf("Logradouro [80]: ");
gets(p->end.logradouro);
fflush(stdin);

printf("Bairro [15]: ");
gets(p->end.bairro);
fflush(stdin);

printf("CEP [10]: ");
gets(p->end.CEP);
fflush(stdin);

printf("Cidade [15]: ");
gets(p->end.cidade);
fflush(stdin);

printf("Estado [3]: ");
gets(p->end.estado);
fflush(stdin);

printf("Telefone [12]: ");
gets(p->end.fone);
fflush(stdin);

printf("E-mail [40]: ");
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
fclose(fptr);   //fora do else - por conta do ab (ab sempre cria, ent�o a a��o de fechar tem que estar fora do else pra acontecer sempre)
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
	  	printf("\t\t\t\t\t\t%s", (p->nome));
	  	printf("\nRegistro: %i\nCNPJ: %s\nLogradouro: %s\nBairro: %s\nCEP: %s\nCidade: %s\nEstado: %s\nTelefone: %s\nEmail: %s\nSold: %i\nReserved: %i\n",p->regloja,p->CNPJ,p->end.logradouro,p->end.bairro,p->end.CEP,p->end.cidade,p->end.estado,p->end.fone,p->end.email, p->sold, p->reserved);
        for(j=0;j<3;j++)
            {
            if(p->tabela[j].reservado.sigla == 'L')
                printf("Tabela %i = %c\n", j, (p->tabela[j].sigla));
            else
                printf("Tabela %i = %c - %i\n", j, p->tabela[j].reservado.sigla, p->tabela[j].reservado.regcarro);
            }
        printf("------------------------------------------------------------------------------------------------------------------\n");
      }
    fclose(fptr);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
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

if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
{
    for(i=0;i<qtde;i++)
    {
        fseek(fptr,i*sizeof(loja),0);
        fread(p,sizeof(loja),1,fptr);
        printf("ID - %i | CNPJ - %s\n", p->regloja, p->CNPJ);
    }
    fclose(fptr); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
}

printf("\nDigite o CNPJ que deseja buscar: ");
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
            printf("\n-------------------------------------------------\nCNPJ Encontrado.");
            printf("\nNome: %s\nSold: %i\nReserved: %i\n", p->nome, p->sold, p->reserved);
            for(j=0;j<3;j++)
                {
                 if(p->tabela[j].reservado.sigla == 'L')
                    printf("Tabela %i = %c\n", j, (p->tabela[j].sigla));
                else
                    printf("Tabela %i = %c - %i\n", j, p->tabela[j].reservado.sigla, p->tabela[j].reservado.regcarro);
                }
            achou=1;
            }
      }
    fclose(fptr); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
  }

if(achou==0)
{
    printf("\nCNPJ n�o encontrado! verifique na consulta e tente novamente.");
}
printf("\n\n");
system("pause");
}//buscacnpj

void alteraconc(loja *p, int qtde)
{
    int i=0, achou=0, op, posconc, erro=0;
    char cnpj[19], cnpjnovo[19], nomenovo[30], auxnomevelho[30];
    FILE *fptrconc=NULL;

    do
    {
        system("cls");
        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtde;i++)
            {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(p,sizeof(loja),1,fptrconc);
                printf("ID - %i | CNPJ - %s\n", p->regloja, p->CNPJ);
            }
            fclose(fptrconc);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }
        printf("----------------------------------------------------------------------------------------------\n\nDigite o CNPJ da concession�ria para alterar os dados: ");
        gets(cnpj);
        fflush(stdin);

        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtde;i++)
            {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(p,sizeof(loja),1,fptrconc);
                if(strcmp(cnpj, p->CNPJ)==0)
                {
                    achou = 1;
                }
            }
            fclose(fptrconc);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }

        if(achou==0)
        {
            printf("Concession�ria n�o encontrada, verifique a digita��o e tente novamente.\n");
            system("pause");
        }
    }while(achou==0);

    printf("\n----------------------------------------------------------------------------------------------\n\n[1] Nome\n[2] CNPJ\nQual dado voc� deseja alterar: ");
    scanf("%i", &op);
    fflush(stdin);
    printf("\n");
    switch(op)
    {
        case 1: printf("----------------------------------------------------------------------------------------------\n\nDigite o novo nome da concession�ria: ");
        gets(nomenovo);
        fflush(stdin);
        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
            {
            for(i=0;i<qtde;i++)
                {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(p,sizeof(loja),1,fptrconc);
                if(strcmp(cnpj, p->CNPJ)==0)
                    {
                        strcpy(auxnomevelho, p->nome);
                        if(p->reserved >= 1)
                        {
                            printf("\n----------------------------------------------------------------------------------------------\nN�o � possivel trocar o nome com reservas em andamento!.\a\n");
                            erro = 1;
                            break;
                        }
                        else
                        {
                            strcpy(p->nome, nomenovo);
                            posconc = i;
                            i=qtde;
                        }
                    }//if
                }//for
            fclose(fptrconc);
            }//else
        if(erro==0)
        {
            //grava��o concession�ria.bin
            if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
                fseek(fptrconc, posconc*sizeof(loja),0);
                fwrite(p,sizeof(loja),1,fptrconc);
              }//else
            fclose(fptrconc);   //fora do else - por conta do ab ou rb+
            printf("\n----------------------------------------------------------------------------------------------\nTroca do nome %s para o nome %s foi efetuada com sucesso!.\n", auxnomevelho, nomenovo);
        }
        break;

        case 2: printf("----------------------------------------------------------------------------------------------\n\nDigite o novo CNPJ (Ex: 11.444.777/0001-61): ");
        gets(cnpjnovo);
        fflush(stdin);

        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
            {
            for(i=0;i<qtde;i++)
                {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(p,sizeof(loja),1,fptrconc);
                if(strcmp(cnpj, p->CNPJ)==0)
                    {
                        strcpy(auxnomevelho, p->nome);
                        if(p->reserved >= 1)
                        {
                            printf("\n----------------------------------------------------------------------------------------------\nN�o � possivel trocar o CNPJ com reservas em andamento!.\a\n");
                            erro = 1;
                            break;
                        }
                        else
                        {
                            strcpy(p->CNPJ, cnpjnovo);
                            posconc = i;
                            i=qtde;
                        }
                    }//if
                }//for
            fclose(fptrconc);
            }//else
        if(erro==0)
        {
            //grava��o concession�ria.bin
            if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
                fseek(fptrconc, posconc*sizeof(loja),0);
                fwrite(p,sizeof(loja),1,fptrconc);
              }
            fclose(fptrconc);   //fora do else - por conta do ab ou rb+
        printf("\n----------------------------------------------------------------------------------------------\nTroca do CNPJ %s na %s para %s foi efetuada com sucesso!.\n", cnpj, auxnomevelho, cnpjnovo);
        }
        break;

        default: printf("Op��o inv�lida\a\n");
        break;
    }
    system("pause");
} //alteraconc

// Fun��es carro.bin - Fun��es carro.bin - Fun��es carro.bin - Fun��es carro.bin - Fun��es carro.bin - Fun��es carro.bin - Fun��es carro.bin - Fun��es carro.bin - Fun��es carro.bin.
void cadastrocarro(montadora *p, int qtde)
{
float price=0;
p->regcarro = qtde;
printf("ID Registro: %i\n",p->regcarro);

printf("Digite o modelo do carro [20]: ");
gets(p->modelo);
fflush(stdin);

printf("Digite a cor do carro [10]: ");
gets(p->cor);
fflush(stdin);

printf("Digite o valor do carro: ");
scanf("%f", &price);
fflush(stdin);

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
fclose(fptr);   //fora do else - por conta do ab (ab sempre cria, ent�o a a��o de fechar tem que estar fora do else pra acontecer sempre)
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
        if(p->status.sigla=='L')
            printf("\nID: %i\nModelo: %s\nCor: %s\nValor: R$%.2f\nStatus: %c\n",p->regcarro, p->modelo, p->cor, p->valor, p->status.sigla);
        else
            printf("\nID: %i\nModelo: %s\nCor: %s\nValor: R$%.2f\nStatus: %c - %s\n",p->regcarro, p->modelo, p->cor, p->valor, p->status.reserva.sigla, p->status.reserva.CNPJ);
        printf("\n------------------------------------------------------------------------------------------------------------------\n");
      }
    fclose(fptr);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
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
    fclose(fptr); //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
  }

if(achou==0)
    {
        printf("Nenhum carro com o status indicado foi encontrado.");
    }
printf("\n\n");
system("pause");
}

void alteracarro(montadora *p, int qtde)
{
    int i, id, achou=0, op, pos, erro=0;
    char novomodelo[20], novacor[10], auxmodelovelho[20], auxcorvelha[10];
    float novovalor, valorvelho;
    FILE *fptrcarro=NULL;
    do
    {
        system("cls");
        if((fptrcarro=fopen("carro.bin", "rb"))==NULL)
            printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtde;i++)
            {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(p,sizeof(montadora),1,fptrcarro);
                if(p->status.sigla=='L')
                {
                    printf("\nID: %i\t | Status: %c\t | %s %s R$%.2f", p->regcarro, p->status.reserva.sigla, p->modelo, p->cor, p->valor);
                }//if
            }//for
            fclose(fptrcarro);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }//else

        printf("\n----------------------------------------------------------------------------------------------\n\nDigite o ID do carro para alterar os dados: ");
        scanf("%i", &id);
        fflush(stdin);

        if((fptrcarro=fopen("carro.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtde;i++)
            {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(p,sizeof(montadora),1,fptrcarro);
                if(id == p->regcarro)
                {
                    if(p->status.sigla=='L')
                        achou = 1;
                }
            }
            fclose(fptrcarro);  //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }

        if(achou==0)
        {
            printf("Carro n�o encontrado na classifica��o livre, verifique a digita��o e tente novamente.\n");
            system("pause");
        }
    }while(achou==0);

    printf("\n----------------------------------------------------------------------------------------------\n\n[1] Modelo\n[2] Cor\n[3] Valor\nQual dado voc� deseja alterar: ");
    scanf("%i", &op);
    fflush(stdin);

    switch(op)
    {
        case 1: printf("----------------------------------------------------------------------------------------------\n\nDigite o novo nome do modelo: ");
        gets(novomodelo);
        fflush(stdin);
        if((fptrcarro=fopen("carro.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
            {
            for(i=0;i<qtde;i++)
                {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(p,sizeof(montadora),1,fptrcarro);
                if(id==p->regcarro)
                    {
                        strcpy(auxmodelovelho, p->modelo);
                        if(p->status.reserva.sigla == 'R')
                        {
                            printf("\n----------------------------------------------------------------------------------------------\nN�o � possivel trocar os dados com reservas em andamento!.\a\n");
                            erro = 1;
                            break;
                        }
                        else
                        {
                            strcpy(p->modelo, novomodelo);
                            pos = i;
                            i=qtde;
                        }
                    }//if
                }//for
            fclose(fptrcarro);
            }//else


        if(erro==0)
        {
            //grava��o carro.bin
            if((fptrcarro=fopen("carro.bin", "rb+"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
                fseek(fptrcarro, pos*sizeof(montadora),0);
                fwrite(p,sizeof(montadora),1,fptrcarro);
              }
            fclose(fptrcarro);   //fora do else - por conta do ab ou rb+
            printf("\n----------------------------------------------------------------------------------------------\nTroca do nome do modelo %s para %s foi efetuada com sucesso!.\n", auxmodelovelho, novomodelo);
        }
        break;

        case 2:  printf("----------------------------------------------------------------------------------------------\n\nDigite o nova cor: ");
        gets(novacor);
        fflush(stdin);
        if((fptrcarro=fopen("carro.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
            {
            for(i=0;i<qtde;i++)
                {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(p,sizeof(montadora),1,fptrcarro);
                if(id==p->regcarro)
                    {
                        strcpy(auxcorvelha, p->cor);
                        if(p->status.reserva.sigla == 'R')
                        {
                            printf("\n----------------------------------------------------------------------------------------------\nN�o � possivel trocar os dados com reservas em andamento!.\a\n");
                            erro = 1;
                            break;
                        }
                        else
                        {
                            strcpy(p->cor, novacor);
                            pos = i;
                            i=qtde;
                        }
                    }//if
                }//for
            fclose(fptrcarro);
            }//else


        if(erro==0)
        {
            //grava��o carro.bin
            if((fptrcarro=fopen("carro.bin", "rb+"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
                fseek(fptrcarro, pos*sizeof(montadora),0);
                fwrite(p,sizeof(montadora),1,fptrcarro);
              }
            fclose(fptrcarro); //fora do else - por conta do ab ou rb+
            printf("\n----------------------------------------------------------------------------------------------\nTroca da cor %s para %s foi efetuada com sucesso!.\n", auxcorvelha, novacor);
        }
        break;

        case 3: printf("----------------------------------------------------------------------------------------------\n\nDigite o novo valor: ");
        scanf("%f", &novovalor);
        fflush(stdin);
        if((fptrcarro=fopen("carro.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
            {
            for(i=0;i<qtde;i++)
                {
                fseek(fptrcarro,i*sizeof(montadora),0);
                fread(p,sizeof(montadora),1,fptrcarro);
                if(id==p->regcarro)
                    {
                        valorvelho = p->valor;
                        if(p->status.reserva.sigla == 'R')
                        {
                            printf("\n----------------------------------------------------------------------------------------------\nN�o � possivel trocar os dados com reservas em andamento!.\a\n");
                            erro = 1;
                            break;
                        }
                        else
                        {
                            p->valor = novovalor;
                            pos = i;
                            i=qtde;
                        }
                    }//if
                }//for
            fclose(fptrcarro);
            }//else


        if(erro==0)
        {
            //grava��o carro.bin
            if((fptrcarro=fopen("carro.bin", "rb+"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
                fseek(fptrcarro, pos*sizeof(montadora),0);
                fwrite(p,sizeof(montadora),1,fptrcarro);
              }
            fclose(fptrcarro); //fora do else - por conta do ab ou rb+
            printf("\n----------------------------------------------------------------------------------------------\nTroca do valor %.2f para %.2f foi efetuada com sucesso!.\n", valorvelho, novovalor);
        }
        break;

        default: printf("Op��o inv�lida\a\n");
        break;
    }
    printf("\n");
    system("pause");
}

void historicoeasteregg(historicoVendas *p, int qtde)
{
    /*
    if(user==talita)
        printf("oi talita");
    else if(user==andrea)
        printf("oi andrea");
    */
    int i, j;
    FILE *fptr=NULL;
    system("cls");
    if((fptr=fopen("historico.bin","rb"))==NULL)
      printf("\nErro ao abrir o arquivo");
    else
      {
        for(i=0;i<qtde;i++)
          {
            fseek(fptr,i*sizeof(historicoVendas),0);
            fread(p,sizeof(historicoVendas),1,fptr);
            if(i==0)
                printf("regHist: %i", p->reghist);
            else
                printf("\n----------------------------------------------------------------------------------------------\nregHist: %i", p->reghist);
            printf("\nregCarro: %i", p->regcarro);
            printf("\nModelo: %s", p->modelo);
            printf("\nCor: %s", p->cor);
            printf("\nValor: %f", p->valor);
            printf("\nregLoja: %i", p->regloja);
            printf("\nNome: %s", p->nome);
            printf("\nCNPJ: %s", p->cnpj);
            printf("\nDia: %i", p->dataVenda.dia);
            printf("\nMes: %i", p->dataVenda.mes);
            printf("\nAno: %i", p->dataVenda.ano);
          }
        fclose(fptr);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
      }
    printf("\n\n");
    system("pause");
}

void histcarro(historicoVendas *phistorico, montadora *pmontadora, int qtdehistorico, int qtdecarro)
{
    int achou=0, i=0, controle=0;
    char modelo[20], arraymodelos[50][20];
    FILE *fptrhistorico=NULL; // ponteiro concession�ria
    FILE *fptrcarro=NULL; // ponteiro carros

    do
    {
        system("cls");
        printf("\t\t\t\t Registros no hist�rico de vendas\n\nModelos: ");
        if((fptrhistorico=fopen("historico.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtdehistorico;i++)
            {
                fseek(fptrhistorico,i*sizeof(historicoVendas),0);
                fread(phistorico,sizeof(historicoVendas),1,fptrhistorico);
                if(i==qtdehistorico-1)
                    printf("%s.", phistorico->modelo);
                else
                    printf("%s, ", phistorico->modelo);
            }
            fclose(fptrcarro);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }
        printf("\n----------------------------------------------------------------------------------------------\n\nDigite o modelo do carro para visualizar seu hist�rico de vendas: ");
        gets(modelo);
        fflush(stdin);

        if((fptrhistorico=fopen("historico.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtdehistorico;i++)
            {
                fseek(fptrhistorico,i*sizeof(historicoVendas),0);
                fread(phistorico,sizeof(historicoVendas),1,fptrhistorico);
                if(strcmp(modelo, phistorico->modelo)==0)
                {
                    achou = 1;
                }
            }
            fclose(fptrhistorico);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }

        if(achou==0)
        {
            printf("Modelo n�o encontrado, verifique a digita��o e tente novamente.\n");
            system("pause");
        }
    }while(achou==0);

     if((fptrhistorico=fopen("historico.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdehistorico;i++)
              {
                fseek(fptrhistorico,i*sizeof(historicoVendas),0);
                fread(phistorico,sizeof(historicoVendas),1,fptrhistorico);
                if(strcmp(modelo, phistorico->modelo)==0)
                    {
                        if(controle==0)
                        {
                            printf("\n----------------------------------------------------------------------------------------------\n\t\t\t\tHist�rico de vendas %s\n", phistorico->modelo);
                            controle=1;
                        }
                        printf("\nRegistro do hist�rico: %i\t\t\t\t\t\t       Data", phistorico->reghist);

                        if(phistorico->dataVenda.dia < 10)
                            printf(" 0%i/", phistorico->dataVenda.dia);
                        else
                            printf(" %i/", phistorico->dataVenda.dia);

                        if(phistorico->dataVenda.mes < 10)
                            printf("0%i/", phistorico->dataVenda.mes);
                        else
                            printf("%i/", phistorico->dataVenda.mes);

                        if(phistorico->dataVenda.ano < 10)
                            printf("0%i", phistorico->dataVenda.ano);
                        else
                            printf("%i", phistorico->dataVenda.ano);

                        printf("\nRegistro da concession�ria: %i", phistorico->regloja);
                        printf("\nNome da concession�ria: %s", phistorico->nome);
                        printf("\nCNPJ da concession�ria: %s", phistorico->cnpj);
                        printf("\nRegistro do carro: %i", phistorico->regcarro);
                        printf("\nCor: %s", phistorico->cor);
                        printf("\nValor: R$%.2f\n----------------------------------------------------------------------------------------------", phistorico->valor);
                    }
              }
            fclose(fptrhistorico);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
          }
    if(controle==0)
        printf("Essa concession�ria n�o vendeu nenhum carro\n");
    printf("\n");
    system("pause");
}


void histconc(historicoVendas *phistorico, loja *ploja, int qtdehistorico, int qtdeloja)
{
    int achou=0, i=0, controle=0;
    char cnpj[20];
    FILE *fptrconc=NULL;
    FILE *fptrhistorico=NULL;

    do
    {
        system("cls");
        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtdeloja;i++)
            {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(ploja,sizeof(loja),1,fptrconc);
                printf("ID - %i | CNPJ - %s\n", ploja->regloja, ploja->CNPJ);
            }
            fclose(fptrconc);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }
        printf("----------------------------------------------------------------------------------------------\n\nDigite o CNPJ da concession�ria para visualizar o hist�rico: ");
        gets(cnpj);
        fflush(stdin);

        if((fptrconc=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
        {
            for(i=0;i<qtdeloja;i++)
            {
                fseek(fptrconc,i*sizeof(loja),0);
                fread(ploja,sizeof(loja),1,fptrconc);
                if(strcmp(cnpj, ploja->CNPJ)==0)
                {
                    achou = 1;
                }
            }
            fclose(fptrconc);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
        }
    }while(achou==0);


        if((fptrhistorico=fopen("historico.bin","rb"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdehistorico;i++)
              {
                fseek(fptrhistorico,i*sizeof(historicoVendas),0);
                fread(phistorico,sizeof(historicoVendas),1,fptrhistorico);
                if(strcmp(cnpj, phistorico->cnpj)==0)
                    {
                        if(controle==0)
                        {
                            printf("\n----------------------------------------------------------------------------------------------\n\t\t\t\tHist�rico de vendas %s\n", phistorico->nome);
                            controle=1;
                        }
                        printf("\nRegistro do hist�rico: %i\t\t\t\t\t\t       Data", phistorico->reghist);

                        if(phistorico->dataVenda.dia < 10)
                            printf(" 0%i/", phistorico->dataVenda.dia);
                        else
                            printf(" %i/", phistorico->dataVenda.dia);

                        if(phistorico->dataVenda.mes < 10)
                            printf("0%i/", phistorico->dataVenda.mes);
                        else
                            printf("%i/", phistorico->dataVenda.mes);

                        if(phistorico->dataVenda.ano < 10)
                            printf("0%i", phistorico->dataVenda.ano);
                        else
                            printf("%i", phistorico->dataVenda.ano);
                        printf("\nRegistro do carro: %i", phistorico->regcarro);
                        printf("\nModelo: %s", phistorico->modelo);
                        printf("\nCor: %s", phistorico->cor);
                        printf("\nValor: R$%.2f\n----------------------------------------------------------------------------------------------", phistorico->valor);
                    }
              }
            fclose(fptrhistorico);   //dentro do else - por conta rb (rb n�o tem for�a pra criar, ent�o a a��o de fechar s� deve acontecer dentro do else, caso o arquivo exista)
          }
    if(controle==0)
        printf("Essa concession�ria n�o vendeu nenhum carro\n");
    printf("\n");
    system("pause");
}

