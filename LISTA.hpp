#ifndef LISTA_HPP_
#define LISTA_HPP_


typedef struct {
	
	int vetor[6000];
    int pFim;
}TLista;

void TLista_Inicia(TLista*);
int getSize(TLista*);
void decrementaPrimeiro(TLista*);
void decrementaPos(TLista* ,int );
int getPrimeiro(TLista* );
int getPosicao(TLista* , int );
void incrementaPos(TLista * , int );
void insereFim(TLista* , int );
void removeInicio(TLista* );
#endif