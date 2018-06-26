#include "QuickSort.hpp"
#include <iostream>

using namespace std;
    /*  Quicksort interno adaptado para ordenar os registros do tipo Aluno de for descendente. Usado pra gerar o arquivo binario de entrada e 
        para ordenar internamente no metodo de intercalação balanceada 2f caminhos com ordenação interna na etapa de geração de blocos ordenados     */
void QuickSort_particao (Aluno* v, int esq, int dir, int* i, int* j) {
	Aluno pivo , aux ;
	*i = esq ;
	*j = dir ;
	pivo = v [(*i + *j ) /2];
	do {
		while (!( pivo.nota >= v[*i].nota)){
			(*i)++;
			
		}
		while (pivo.nota > v[*j].nota){
			(*j)--;
			
		}
		if (*i <= *j) {
		aux = v [*i];
		v [*i] = v[*j];
		v [*j] = aux ;
		(*i)++;
		(*j)--;
		
		}
	} while (*i <= *j) ;
}
void quicksort_ordena(Aluno* v, int esq, int dir) {
	int i , j ;
		QuickSort_particao (v, esq, dir, &i, &j);
	if (esq < j)
		quicksort_ordena(v, esq, j);
	if (i < dir)
		quicksort_ordena(v, i, dir);
}
void quicksort (Aluno* v, int n) {
	quicksort_ordena(v, 0 ,n-1);
}
