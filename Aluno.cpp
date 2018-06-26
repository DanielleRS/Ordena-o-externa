#include "Aluno.hpp"
#include <iostream>
using namespace std;

void insertion (Aluno* V, int n ){ //função para inserir ordenado
    int i,j;
    Aluno aux;
    for (i = 1; i < n; i++) {
        aux = V[i];
        j = i - 1;
        while (j >= 0 && aux.nota > V[j].nota) {
            V[j + 1] = V[j];
            j--;
        }
        V[j + 1] = aux;
    }
}