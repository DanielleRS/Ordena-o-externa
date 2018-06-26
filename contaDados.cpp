#include "contaDados.hpp"

static long leituras;
static long escritas;
static long comparacoes;

void iniciaContadores(){
    leituras = 0;
    escritas = 0;
    comparacoes = 0;
}

void incrementaLeituras(){
    leituras++;
}

void incrementaEscritas(){
    escritas++;    
}

void incrementaComparacoes(){
    comparacoes++;   
}

long returnLeituras(){
    return leituras;
}

long returnEscritas(){
    return escritas;
}

long returnComparacoes(){
    return comparacoes;
}