#ifndef CONTADADOS_HPP_
#define CONTADADOS_HPP_

//Conjunto de funções usado para contrar as estatísticas para análise

void iniciaContadores();

void incrementaLeituras();
void incrementaEscritas();
void incrementaComparacoes();

long returnLeituras();
long returnEscritas();
long returnComparacoes();

#endif