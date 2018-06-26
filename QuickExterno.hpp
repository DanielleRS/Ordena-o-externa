#ifndef QUICKEXTERNO_HPP_
#define QUICKEXTERNO_HPP_

#include "stdio.h"
#include <limits.h>
#include "Aluno.hpp"

typedef Aluno TipoRegistro ;

//Area de mememo riainterna usada como pivo (enxergada como um vetor)
typedef struct{
  TipoRegistro itens[TAMAREA];
  int num_celOcupadas;
}TipoArea;

void QuicksortExterno(FILE**, FILE**, FILE**, int, int);                
void LeSup(FILE**, TipoRegistro*, int*, short*);                        
void LeInf(FILE**, TipoRegistro*, int*, short*);                        
void InserirArea(TipoArea*, TipoRegistro*, int*);                       
void EscreveMax(FILE**, TipoRegistro, int*);                            
void EscreveMin(FILE**, TipoRegistro, int*);                            
void RetiraMax(TipoArea*, TipoRegistro*, int*);                         
void RetiraMin(TipoArea*, TipoRegistro*, int*);                         
void Particao(FILE**, FILE**, FILE**, TipoArea, int, int, int*, int*);  
void RetiraUltimo(TipoArea*,TipoRegistro*);                             
void RetiraPrimeiro(TipoArea*,TipoRegistro*);                           
int ObterNumCelOcupadas(TipoArea*);                                     
void FAVazia(TipoArea*);                                                
void InsereItem(TipoRegistro, TipoArea*);                               

#endif