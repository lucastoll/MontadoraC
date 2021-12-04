// Grupo 5 TIM2 - Manhã
// João Matheus de Jesus Mendes     RA 210166
// Lucas Fernandes Tolotto          RA 211046
// Pedro Henrique Todineyb Santos   RA 210131
// Rafael Ramos do Rosário          RA 210814

// duvidas
// acentuação nao funciona quando cadastra dados no arquivo, so funciona nos prints normais do menu.

// coisas pra fazer chique
// 1 - tratamento inputs (receber só informações validas)
// 2 - tratamento valor (no print R$120.000,00)
// 3 - intro animação
// 4 - função printar carro colorido
// 5 - printar horário no menu

// ponteiro -> membro da estrutura
// estrutura (membro) . dados da estrutura

#include <stdio.h> //Biblioteca padrão de entrada/saída, printf scanf.
#include <stdlib.h> //emula o prompt de comando, cls pause.
#include <locale.h> //acentuação / linguagem
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

typedef struct montadora { //estrutura principal de cadastro
int regcarro; //gerar automático - long int
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



//portal (ctrl f)
// Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main - Funções antes da main.

// funções universal

void aloca(loja **ploja, montadora **pmontadora,  historicoVendas **phistorico, int tam, int seletor);
int verifica(loja **ploja, montadora **pmontadora,  historicoVendas **phistorico, int seletor);
void creditos();
void reserva(loja *ploja, montadora *pmontadora, int qtdeconc, int qtdecarro);
void venda(loja *ploja, montadora *pmontadora, historicoVendas *phistorico, int qtdeconc, int qtdecarro, int qtdehistorico);

// funções concessionária.bin
void cadastroconc(loja *p, int qtde); //cadastro struct loja
void cadastroend(loja *p);
void gravaconc(loja *p); //grava os dados no ponteiro
void mostraconc(loja *p, int qtde);
void buscacnpj(loja *p, int qtde);

// funções carros.bin
void cadastrocarro(montadora *p, int qtde);
void gravacarro(montadora *p, int qtde);
void mostracarro(montadora *p, int qtde);
void buscastatus(montadora *p, int qtde);

// funções historico.bin
void historicoeasteregg(historicoVendas *p, int qtde);


// Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main - Main.
//portalmain
int main()
{
setlocale(LC_ALL, "portuguese");
loja *ploja=NULL;
montadora *pcarros=NULL;
historicoVendas *phistorico=NULL;


char op, op2;
int qtde, qtdecarro, qtdehistorico, opmenu=1, controlemenu=1, opconc, mconc=1, opcarro, mcarro=1, opreserva, mreserva=1;
aloca(&ploja, &pcarros, &phistorico, 1, 1);
aloca(&ploja, &pcarros, &phistorico, 1, 2);
aloca(&ploja, &pcarros, &phistorico, 1, 3);


do // menu principal - montadora ou carros
{
qtde = verifica(&ploja, &pcarros,  &phistorico, 1); // Função que retorna o número do registro
qtdecarro = verifica(&ploja, &pcarros, &phistorico, 2);
qtdehistorico = verifica(&ploja, &pcarros, &phistorico, 3);
system("cls");
printf("\n\nqtdehistorico ana maria braga = %i\n\n", qtdehistorico);
printf("SISTEMA ESTOQUE MONTADORA\nCONCESSIONÁRIAS NO SISTEMA: %i |\tCARROS NO SISTEMA: %i\n\nBem-vindo(a)!, digite uma das opções abaixo.\n[1] Registro concessionária\n[2] Registro de carros\n[3] Registros e vendas\n[4] Encerrar programa\n\n", qtde, qtdecarro);
scanf("%i", &opmenu);
fflush(stdin);
switch(opmenu)
{
        case 1: mconc=1; //controle dowhile concessionaria
        do //concessionaria
        {
        system("cls");
        printf("REGISTRO CONCESSIONÁRIA\n\n[1] Consulta geral\n[2] Consulta de vendas\n[3] Registrar concessionária\n[4] Alterar registro\n[5] Histórico de compras por concessionária\n[6] Menu principal\n\n");
        scanf("%i", &opconc);
        fflush(stdin);
        qtde = verifica(&ploja, &pcarros, &phistorico, 1); // Função que retorna o número do registro
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
                printf("Quantidade máxima de montadoras já foi atingida.\n");
                system("pause");
                break;
            }
            cadastroconc(ploja,(qtde++)+1);
            printf("\nDeseja continuar <S/N>: ");
            scanf("%c", &op);
            fflush(stdin);
            }while(op!='n' && op!= 'N');
            mostraconc(ploja,qtde);
            break;

            case 4: printf("altera");
            system("pause");
            break;

            case 5: printf("talitacpaconcessionaria");
            system("pause");
            break;

            case 6: mconc = 0;
            break;

            default: printf("Opção inválida\a\n");
            system("pause");
            break;
        }//switch
        }while(mconc==1);
        break; //fim menu concessionaria

        case 2: mcarro = 1; //controle dowhile menu carro
        do{
        system("cls");
        printf("REGISTRO DE CARROS - MONTADORA\n\n[1] Consulta geral\n[2] Consulta parcial\n[3] Registrar carros\n[4] Alterar registro\n[5] Histórico de vendas por modelo\n[6] Menu principal\n\n");
        scanf("%i", &opcarro);
        fflush(stdin);
        qtdecarro = verifica(&ploja, &pcarros, &phistorico, 2);
        switch(opcarro)
        {
            case 1: mostracarro(pcarros, qtdecarro);
            break;

            case 2: buscastatus(pcarros, qtdecarro);
            break;

            case 3: do
                {
                if(qtdecarro >= 50)
                {
                    printf("Quantidade máxima de carros já foi atingida.\n");
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

            case 4: printf("altera carro");
            system("pause");
            break;

            case 5: printf("historico de vendas por modelo");
            system("pause");
            break;

            case 6: mcarro = 0;
            break;

            default: printf("Opção inválida\a\n");
            system("pause");
            break;
        }
        }while(mcarro==1);
        break;

        case 3: mreserva=1;
        if(qtde==0)
        {
            printf("\nNão é possivel realizar reservas ou vendas sem nenhuma concessionária registrada no sistema!\a\n\n");
            system("pause");
            break;
        }
        else if(qtdecarro==0)
        {
            printf("\nNão é possivel realizar reservas ou vendas sem nenhum carro registrado no sistema!\a\n\n");
            system("pause");
            break;
        }
        do
        {
            system("cls");
            printf("RESERVAS E VENDAS\n\n[1] Reservas\n[2] Vendas e liberação\n[3] Menu principal\n\n");
            scanf("%i", &opmenu);
            fflush(stdin);

            switch(opmenu)
            {
            case 1: reserva(ploja, pcarros, qtde, qtdecarro);
            break;

            case 2: venda(ploja, pcarros, phistorico, qtde, qtdecarro, ((qtdehistorico)+1));
            break;

            case 3: mreserva = 0;
            break;

            default: printf("Opção inválida\a\n");
            system("pause");
            break;
            }
        }while(mreserva==1);
        break;

        case 4: controlemenu = 0; //encerrar programa
        break;

        case 5: historicoeasteregg(phistorico, qtdehistorico);
        break;

        default: printf("Opção inválida\a\n");
        system("pause");
        break;
}//switch menu principal
}while(controlemenu==1);
creditos();
}//main


//portaleaster
void historicoeasteregg(historicoVendas *p, int qtde)
{
    int i, j;
    FILE *fptr=NULL;
    system("cls");
    printf("\n\n");
    if((fptr=fopen("historico.bin","rb"))==NULL)
      printf("\nErro ao abrir o arquivo");
    else
      {
        for(i=0;i<qtde;i++)
          {
            fseek(fptr,i*sizeof(historicoVendas),0);
            fread(p,sizeof(historicoVendas),1,fptr);
            printf("\nregHist: %i", p->reghist);
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
        fclose(fptr);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
      }
    printf("\n\n");
    system("pause");
}







// Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main - Funções depois da main.
//portalreserva
void reserva(loja *ploja, montadora *pmontadora, int qtdeconc, int qtdecarro)
{
    int i, j, l=0, achou=0, idcarro, pos, poscarro, erro=0;
    char pcnpj[30], auxnomeconc[30], auxnomecarro[20], auxcorcarro[10], auxcarrosigla, op;
    FILE *fptrconc=NULL; // ponteiro concessionária
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
            fclose(fptrconc);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
        }
        printf("----------------------------------------------------------------------------------------------\n\nDigite o CNPJ da concessionária que vai efetuar a reserva: ");
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
            fclose(fptrconc);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
        }

        if(achou==0)
        {
            printf("\nCNPJ não encontrado! verifique a digitação e tente novamente.\n");
            system("pause");
        }
    }while(achou==0);

    achou=0; // variavel resetada para usar do mesmo jeito com o input do carro
    do // dowhile input - ID carro
    {
        printf("----------------------------------------------------------------------------------------------\n\nDigite o ID do carro à ser reservado: ");
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
                    strcpy(auxnomecarro, pmontadora->modelo); // variáveis auxiliares usadas posteriormente para printar uma confirmação.
                    strcpy(auxcorcarro, pmontadora->cor);
                    auxcarrosigla = pmontadora->status.sigla;
                    }
              }
            fclose(fptrcarro); //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
          }

        if(achou==0)
        {
            printf("\n----------------------------------------------------------------------------------------------");
            printf("\nNenhum carro com o ID indicado foi encontrado.\n");
        }
        else
        {
            printf("Confirmar reserva do carro %s %s na concessionária %s? <S|N>\n", auxnomecarro, auxcorcarro, auxnomeconc);
            scanf("%c", &op);
            fflush(stdin);
            switch(op)
            {
                case 'n':

                case 'N': printf("Cancelando reserva.");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".\n");
                break;

                case 's':

                case 'S':
                if((fptrconc=fopen("concessionaria.bin","rb"))==NULL) // arquivo aberto para verificação e alteração dos dados concessionaria.bin
                  printf("\nErro ao abrir o arquivo");
                else
                    {
                    for(i=0;i<qtdeconc;i++)
                        {
                        fseek(fptrconc,i*sizeof(loja),0);
                        fread(ploja,sizeof(loja),1,fptrconc);
                        if(strcmp(pcnpj, ploja->CNPJ)==0)
                            {
                            //Verificação carro vago (já vendido)
                            if(auxcorcarro=="vago");
                            {
                                printf("\nEsse carro já foi vendido.\n");
                                fclose(fptrconc);
                                erro=1;
                                break;
                            }
                            //Verificação carro 'L'
                            if(auxcarrosigla=='R')
                            {
                                printf("\nEsse carro já foi reservado\n");
                                fclose(fptrconc);
                                erro=1;
                                break;
                            }
                            //Verificação reserved >= 3
                            else if(ploja->reserved >= 3)
                            {
                                printf("Quantidade máxima de reservas nessa concessionária já foi atingida.\n");
                                fclose(fptrconc);
                                erro=1;
                                break;
                            }
                            ploja->reserved += 1;
                            pos = i;
                            i=qtdeconc;
                            // Implementação sigla status concessionária.
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
                            // Printar concessionária novamente, agora que a reserva foi efetuada.
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
                //gravar informações na concessionaria.bin
                {
                    if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL) //acabamento
                      printf("\nErro ao abrir o arquivo");
                    else
                      {
                        fseek(fptrconc, pos*sizeof(loja),0);
                        fwrite(ploja,sizeof(loja),1,fptrconc);
                      }//else
                    fclose(fptrconc);   //fora do else - por conta do ab ou rb+

                    //verificação e alteração na carro.bin

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
                        fclose(fptrcarro); //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
                      }

                    //gravar informações no carro.bin
                    if((fptrcarro=fopen("carro.bin", "rb+"))==NULL) //acabamento
                      printf("\nErro ao abrir o arquivo");
                    else
                      {
                        fseek(fptrcarro, poscarro*sizeof(montadora),0);
                        fwrite(pmontadora,sizeof(montadora),1,fptrcarro);
                      }//else
                    fclose(fptrcarro);   //fora do else - por conta do ab ou rb+
                }
                break;

                default: printf("Opção inválida\a\n");
                break;

        }//switch
       }//else
    }while(achou==0);
system("pause");
}

//portalvenda
void venda(loja *ploja, montadora *pmontadora, historicoVendas *phistorico, int qtdeconc, int qtdecarro, int qtdehistorico)
{
    int i, j, l, auxidcarro, auxidloja, achou=0, achoureserva=0, escolhaswitch, posconc, poscarro, controle=0;
    float auxvalorcarro;
    char auxmodelo[20], auxcor[10], auxcnpj[20], auxnomeconc[30];
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
        fclose(fptrcarro);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
      }

    if(controle==0)
    {
        printf("\nNão há carros reservados para realizar a venda ou a liberação.\n\n");
        system("pause");
    }
    else
    {
        do
    {
        printf("\n-----------------------------------------------------------------------------------------------------\n\nDigite o ID do carro que você deseja vender ou liberar: ");
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
            fclose(fptrcarro);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
          }

        if(achou==0)
        {
           printf("ID não encontrado, tente novamente.\n");
        }
        else if(achoureserva==0)
        {
            printf("O carro com este ID não foi reservado, favor reservar antes de realizar alguma ação.\n");
        }
    }while(achou==0 || achoureserva==0);
    printf("\n-----------------------------------------------------------------------------------------------------\n\nO que você deseja fazer com o carro ID %i - %s %s?.\n\n[1] Vender\n[2] Liberar reserva\n\n", auxidcarro, auxmodelo, auxcor);
    scanf("%i", &escolhaswitch);
    switch(escolhaswitch)
    {
        case 1: // caso vender
        // alterações concessionaria.bin
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


        // alterações historico.bin
        if((fptrhistorico=fopen("historico.bin","ab"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            for(i=0;i<qtdehistorico;i++)
              {
                fseek(fptrhistorico,i*sizeof(historicoVendas),0);
                fread(fptrhistorico,sizeof(historicoVendas),1,fptrhistorico);
                //printf("i = %i | qtdehistorico = %i", i, qtdehistorico);
                if(i==(qtdehistorico-1))
                {
                    //phistorico->reghist = qtdehistorico;
                    phistorico->reghist = 250;
                    //phistorico->regcarro = auxidcarro;
                    phistorico->regcarro = 222;
                    //strcpy(phistorico->modelo, auxmodelo)
                    strcpy(phistorico->modelo, "Nilsinho");
                    //strcpy(phistorico->cor, auxcor);
                    strcpy(phistorico->cor, "cornao");
                    //phistorico->valor = auxvalorcarro;
                    phistorico->valor = 12.44;
                    //phistorico->regloja = auxidloja;
                    phistorico->regloja = 23223223232;
                    //strcpy(phistorico->nome, auxnomeconc);
                    strcpy(phistorico->nome, "auxnomeconc");
                    //strcpy(phistorico->cnpj, auxcnpj);
                    strcpy(phistorico->cnpj, "auxcnpj");

                    printf("\n-----------------------------------------------------------------------------------------------------\nData da venda\n");
                    printf("\n\nqtdehistorico = %i\n\n", qtdehistorico);
                    //printf("\nDia da venda: ");
                    phistorico->dataVenda.dia = 12;
                    phistorico->dataVenda.mes = 13;
                    phistorico->dataVenda.ano = 14;
                    /*
                    scanf("%i", &phistorico->dataVenda.dia);
                    printf("Mês da venda: ");
                    scanf("%i", &phistorico->dataVenda.mes);
                    printf("Ano da venda: ");
                    scanf("%i", &phistorico->dataVenda.ano);
                    */
                }
                //PINO
                //int i, j, l, auxidcarro, achou=0, achoureserva=0, escolhaswitch, posconc, poscarro, controle=0;
                //char auxmodelo[20], auxcor[10], auxcnpj[20], auxnomeconc[30];
              }
          }
        fclose(fptrhistorico); //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)


        // alterações carro.bin
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
            fclose(fptrcarro); //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
          }


        //gravação historico.bin
        if(qtdehistorico==1)
        {
            if((fptrhistorico=fopen("historico.bin","ab"))==NULL)
              printf("\nErro ao abrir o arquivo");
            else
              {
              //qtdehistorico++;
              //fseek(fptrhistorico, qtdehistorico*sizeof(historicoVendas),0);
              fwrite(phistorico,sizeof(historicoVendas),1,fptrhistorico);
              }
            fclose(fptrhistorico);   //fora do else - por conta do ab (ab sempre cria, então a ação de fechar tem que estar fora do else pra acontecer sempre)
        }
        else
        {
            if((fptrhistorico=fopen("historico.bin", "rb+"))==NULL) //acabamento
              printf("\nErro ao abrir o arquivo");
            else
              {
                printf("\n\nqtdehistorico ana maria braga = %i\n\n", qtdehistorico);
                fseek(fptrhistorico, qtdehistorico*sizeof(historicoVendas),0);
                fwrite(phistorico,sizeof(historicoVendas),1,fptrhistorico);
              }//else
            fclose(fptrhistorico);   //fora do else - por conta do ab ou rb+
        }


        //gravação carro.bin

        if((fptrcarro=fopen("carro.bin", "rb+"))==NULL) //acabamento
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrcarro, poscarro*sizeof(montadora),0);
            fwrite(pmontadora,sizeof(montadora),1,fptrcarro);
          }//else
        fclose(fptrcarro);   //fora do else - por conta do ab ou rb+

        printf("\n-----------------------------------------------------------------------------------------------------\nVenda do carro ID - %i, %s %s na %s foi confirmada.\n", auxidcarro, auxmodelo, auxcor, auxnomeconc);

        // gravação concessionaria.bin

        if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrconc, posconc*sizeof(loja),0);
            fwrite(ploja,sizeof(loja),1,fptrconc);
          }//else
        fclose(fptrconc);   //fora do else - por conta do ab ou rb+
        break;

        case 2: // caso liberar reserva
        // alterações concessionaria.bin
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


        // gravação concessionaria.bin
        if((fptrconc=fopen("concessionaria.bin", "rb+"))==NULL)
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrconc, posconc*sizeof(loja),0);
            fwrite(ploja,sizeof(loja),1,fptrconc);
          }//else
        fclose(fptrconc);   //fora do else - por conta do ab ou rb+


        // alteração sigla do carro.bin
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
            fclose(fptrcarro); //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
          }


        // gravar informações no carro.bin
        if((fptrcarro=fopen("carro.bin", "rb+"))==NULL) //acabamento
          printf("\nErro ao abrir o arquivo");
        else
          {
            fseek(fptrcarro, poscarro*sizeof(montadora),0);
            fwrite(pmontadora,sizeof(montadora),1,fptrcarro);
          }//else
        fclose(fptrcarro);   //fora do else - por conta do ab ou rb+
        printf("Reserva do carro ID - %i, %s %s na %s foi liberada.", auxidcarro, auxmodelo, auxcor, auxnomeconc);
        printf("\n\n");
        break;

        default: printf("Opção inválida\a\n");
        break;
    }

    system("pause");
    }
}//venda

void aloca(loja **ploja, montadora **pmontadora, historicoVendas **phistorico, int tam, int seletor)
{
if(seletor==1) //ploja
    {
    if((*ploja=(loja*)realloc(*ploja,tam*sizeof(loja)))==NULL)
      exit(1);
    }
else if(seletor==2) // pmontadora
    {
    if((*pmontadora=(montadora*)realloc(*pmontadora,tam*sizeof(montadora)))==NULL)
      exit(1);
    }
else
    {
    if((*phistorico=(historicoVendas*)realloc(*phistorico,tam*sizeof(historicoVendas)))==NULL)
      exit(1);
    }
}


int verifica(loja **ploja, montadora **pmontadora, historicoVendas **phistorico, int seletor)
{
FILE *fptr=NULL;
long int cont=0;

if(seletor==1) //ploja
{
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
else if(seletor==2) //pmontadora
{
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
else
{
    if((fptr=fopen("historico.bin","rb"))==NULL)
      return cont;
    else
      {
        fseek(fptr,0,2);   // posiciona fptr no final do arquivo
        cont=ftell(fptr)/sizeof(historicoVendas); //n de bytes do começo do arquivo até a posição atual (fim), dividido pela quantidade de bytes que a estrutura tem, isso da um número inteiro certinho que é o nosso cont, usado nas outras funções como tamanho/qtde
        fclose(fptr);    // dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
        return cont;
      }
}

}

void creditos()
{
//esquema de cores
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
printf("João Mendes");
SetConsoleTextAttribute(hConsole, saved_attributes);
printf(", ");
Sleep(1000);
SetConsoleTextAttribute(hConsole, 10);
printf("Rafael Rosário");
SetConsoleTextAttribute(hConsole, saved_attributes);
printf(".\n\n");
}

// concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin concessionaria.bin

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
	  	printf("\t\t\t\t\t\t%s", (p->nome)); //fazer toupper
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
    fclose(fptr);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
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
    fclose(fptr);   //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
  }

if(achou==0)
{
    printf("\nCNPJ não encontrado! verifique na consulta e tente novamente.");
}
printf("\n\n");
}

// carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin carro.bin
// portal (ctrl f)

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
        if(p->status.sigla=='L')
            printf("\nID: %i\nModelo: %s\nCor: %s\nValor: R$%.2f\nStatus: %c\n",p->regcarro, p->modelo, p->cor, p->valor, p->status.sigla);
        else
            printf("\nID: %i\nModelo: %s\nCor: %s\nValor: R$%.2f\nStatus: %c - %s\n",p->regcarro, p->modelo, p->cor, p->valor, p->status.reserva.sigla, p->status.reserva.CNPJ);
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
    fclose(fptr); //dentro do else - por conta rb (rb não tem força pra criar, então a ação de fechar só deve acontecer dentro do else, caso o arquivo exista)
  }

if(achou==0)
{
    printf("Nenhum carro com o status indicado foi encontrado.");
}
printf("\n\n");
system("pause");
}
