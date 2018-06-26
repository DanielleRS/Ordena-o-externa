#include "stdio.h"
#include "Aluno.hpp"
#include "LISTA.hpp"

#ifndef FITA_HPP_
#define FITA_HPP_

#define N_FITAS 20 //quantidadade total de fitas

/*
    Estrutua da fita que usa uma lista por array 
    guardar os tamanhos de cada bloco
*/
typedef struct{
    FILE* arq;
    char nome_arq[20];
    TLista tam_blocos;
    bool dir;
    bool ativa;
    int n_blocos;
    long pos_leitura;
}Fita;

void inicializaFitas(Fita*,int);
void deleta_arqs(Fita*);
void geraBlocosOrdenados(Fita*, Aluno*);
int intercalaBlocos(Fita*,int);

#endif
