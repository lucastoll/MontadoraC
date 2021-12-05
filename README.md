# MontadoraC

https://user-images.githubusercontent.com/86172649/144734206-32901f77-7366-463a-b866-e7cd70bbc938.mp4

## 🚗 O que é 

Projeto desenvolvido para a avaliação final da disciplina de programação estruturada, consiste em um executável programado em C que faz o papel de um sistema de montadora de carros, onde o intuito é **registrar concessionárias**, que seriam os _clientes_ e **registrar carros**, que seriam os _produtos_ da montadora, dessa maneira é possível vender os carros registrados para as concessionárias registradas, quando a venda acontece ela é registrada em um histórico de vendas. 

## 📁 Arquivos

A principal curva de aprendizado do projeto é manipular __arquivos em binário__ para guardar as informações registradas, o projeto gera 3 arquivos:

- __concessionaria.bin__ - Guarda as informações das concessionárias registradas.
- __carro.bin__ - Guarda as informações dos carros registrados.
- __historico.bin__ - Guarda as informações do histórico de vendas.

#### Executáveis

1. FoxtrotMontadora.exe, executável da versão final do projeto, que tem sua build feita com um efeitos sonoros e um ícone personalizado
2. a pasta "codigo" tem o código fonte do arquivo __sem as customizações de som e ícone__, esse arquivo pode ser alterado e buildado sem instalar nada.
3. a pasta "codigofinal" tem o código fonte do arquivo com as customizações, para alterar e buildar esse arquivo é necessário criar um projeto no DEV e instalar a biblioteca __mmsystem__ nos paramêtros do projeto

## 📈 Funções desenvolvidas

O programa contém diversas funções para facilitar a manipulação dos dados, sendo elas:

- __Registro de concessionária/carro:__ recebe e grava os dados nos arquivos respectivos arquivos binários. 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Reserva:__ realiza a reserva de um carro para uma concessionária, é necessário reservar antes de realizar a venda: 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Venda:__ realiza a venda de um carro previamente __reservado__, também é possível cancelar a reserva ao invés de concluir a venda. 

![4](https://user-images.githubusercontent.com/86172649/144735509-93441901-8f0c-4a79-868d-f957827a380b.PNG)
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Histórico por concessionária:__ exibe o histórico de vendas realizadas para uma determinada concessionária.
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Histórico por modelo:__ exibe o histórico de vendas realizadas de um determinado modelo de carro.
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Alterar registro:__ permite a alteração dos dados já registrados de uma concessionária ou carro, desde que o dado ao ser alterado não esteja envolvido em uma reserva.
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Consulta geral das concessionárias/carros:__ mostra todos os items registrados nos arquivos e suas características.

![1](https://user-images.githubusercontent.com/86172649/144735215-3ceb443e-7e3d-4c5f-ac11-c87457705af5.PNG)

- __Consulta de vendas da concessionárias:__ exibe apenas as informações relacionadas as vendas de uma das concessionárias.
 ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Consulta parcial de carros:__ exibe apenas os carros com status livre ou reservado.
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
- __Consulta individual de carro:__ exibe um carro e suas características com uma arte em caractere, que tem a cor registrada no arquivo ilustrada na arte. 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
![3](https://user-images.githubusercontent.com/86172649/144735261-190b19e7-07f2-4e4c-8ebe-542dbf4ab625.PNG)

## 🙍‍♂️ Contribuidores
João Matheus de Jesus Mendes

Lucas Fernandes Tolotto

Pedro Henrique Todineyb Santos

Rafael Ramos do Rosário
