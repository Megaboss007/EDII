#include <stdio.h>
#include <iostream>
#include <stack>


using namespace std;

#define TipoDaPilha pecaenc
#define TipoDaFila posicao

typedef struct{
  int lin, col;
  char **matriz, nome;  
} pentamino;

char** criarmatriz(int lin,int col){ 
  char** matriz;
  int i;
  matriz = (char**)malloc( lin * sizeof (char *));
  for (i = 0; i < lin; ++i)
   matriz[i] = (char*)malloc( col* sizeof (char));
  return matriz;
}

void limparmatriz(char** matriz,int linhas){ 
  for (int i=0;i<linhas;i++)
    free(matriz[i]);  
  free(matriz);
}

int inserirpentamino(char** matriz, int linha, int coluna, pentamino penta) {
  char** matrizaux;
  matrizaux = criarmatriz(penta.lin, penta.col);
  for(int i=0;i<p.lin;i++)
    for(int j=0;j<p.col;j++)
       matrizaux[i][j]=p.mat[i][j];
  

  return 0;
}


char** invertermatriz(char **matriz,int maxlin,int maxcol){
  char** matrizinversa;

  matrizinversa= criarmatriz(maxcol,maxlin);
  for(int i=0;i<maxcol;i++)
    for(int j=0;j<maxlin;j++)
     matrizinversa[i][j]=matriz[maxlin-j-1][i];

  limparmatriz(matriz,maxlin);
  return matrizinversa;
}


void solver(char** matriz,int maxlinha,int maxcoluna,int inverter){
    int aux;
    stack <string> pentaminos;

    if(inverter){ // Trocando linhas por colunas, para aumentar a velocidade do código.
    matriz=invertermatriz(matriz,maxlinha,maxcoluna);
    aux=maxlinha;
    maxlinha=maxcoluna;
    maxcoluna=maxlinha;
  }



    
}

int main() 
{ 
  string matriz;
  int linha = 0;
  int coluna = 0;
  int maxcoluna = 0;
  char** matriz2;
  char** a2d = new char*[60]; 
  for (int i = 0; i < 60; i++) 
     a2d[i] = new char[60]; 

//Recebendo Input e armazenando em uma matriz

while(getline(cin, matriz)) {
  for (int i = 0; i < matriz.length(); i++) {   
     if (matriz[i]=='0' || matriz[i] == '1')  {
     a2d[linha][coluna] = matriz[i];    
     coluna++;     

     }          
  }
  if(maxcoluna < coluna)
  maxcoluna = coluna;
  coluna = 0;
  linha++;
}

matriz2=criarmatriz(linha, maxcoluna);

  for(int i=0;i<linha;i++){
    for(int j=0;j<maxcoluna;j++){
      matriz2[i][j] = a2d[i][j];
    }
  }	

   for(int i=0;i<linha;i++){
    for(int j=0;j<maxcoluna;j++){
      cout << matriz2[i][j];
    }
    cout << '\n';

    solver(matriz2,linha,maxcoluna,linha<maxcoluna);
  }	


}
