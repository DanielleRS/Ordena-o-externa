#include "LISTA.hpp"
#include <iostream>

using namespace std;


void TLista_Inicia(TLista* lista){
	lista->pFim=0;
}

int getSize(TLista* lista){
	return lista->pFim;
}

void decrementaPrimeiro(TLista* lista){
	lista->vetor[0]--;
}

void decrementaPos(TLista* lista, int pos){
	lista->vetor[pos]--;
}

int getPrimeiro(TLista* lista){
	return lista->vetor[0];
}

int getPosicao(TLista* lista, int pos){
	return lista->vetor[pos];
}
void incrementaPos(TLista * lista, int pos){
	lista->vetor[pos]++;
}

void insereFim(TLista* lista, int dado){ 
	lista->vetor[lista->pFim]= dado;
	lista->pFim++;
}
void removeInicio(TLista* lista){
	int aux;
	for (int i=1; i<lista->pFim; i++){
        aux = lista->vetor[i];
        lista->vetor[i-1] = aux;
    }
    lista->pFim--;
}
