#include "QuickExterno.hpp"
#include "QuickSort.hpp"
#include "contaDados.hpp"
#include <iostream>
using namespace std;

// Função que coordena a as chamadas recursivas para os subarquivos
void QuicksortExterno(FILE** ArqLi, FILE** ArqEi, FILE** ArqLEs, int Esq, int Dir){
    int i,j;
    TipoArea Area;
    if(Dir - Esq < 1)return;

    FAVazia(&Area);
    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);
    
    if(i - Esq < Dir - j){
        
        incrementaComparacoes();
        
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
    }
    else{
        
        incrementaComparacoes();
        
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
    }
}

// Função que realiza uma leitura no subarquivo superior
void LeSup(FILE** ArqLEs, TipoRegistro* UltLido, int* Ls, short* OndeLer){
    
    incrementaLeituras();
    
    fseek(*ArqLEs, (*Ls - 1) * sizeof(TipoRegistro), SEEK_SET);
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = 0;
}

// Função que realiza uma leitura no subarquivo inferior
void LeInf(FILE** ArqLi, TipoRegistro* UltLido, int* Li, short* OndeLer){
    
    incrementaLeituras();
    
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLi);
    (*Li)++;
    *OndeLer = 1;
}

// Função que insere um registro em memoria principal
void InserirArea(TipoArea* Area, TipoRegistro* UltLido, int* NRArea){
    InsereItem(*UltLido, Area);
    *NRArea = ObterNumCelOcupadas(Area);
}

// Função escreve no sub arquivo superior  
void EscreveMax(FILE** ArqLEs, TipoRegistro R, int* Es){
    
    incrementaEscritas();
    
    fseek(*ArqLEs, (*Es - 1) * sizeof(TipoRegistro), SEEK_SET);
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs);
    (*Es)--;
}

// Função escreve no sub arquivo inferior 
void EscreveMin(FILE** ArqEi, TipoRegistro R, int* Ei){
    
    incrementaEscritas();
    
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqEi);
    (*Ei)++;
}

// Função que retira o maior registro da memoria
void RetiraMax(TipoArea* Area, TipoRegistro* R, int* NRArea){
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

// Função que retira o menor registro da memoria
void RetiraMin(TipoArea* Area, TipoRegistro* R, int* NRArea){
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

// Função que realiza a ordenação em si
void Particao(FILE** ArqLi, FILE** ArqEi, FILE** ArqLEs, TipoArea Area, int Esq, int Dir, int* i, int* j){
    int Ls = Dir;
    int Es = Dir;
    int Li = Esq;
    int Ei = Esq;
    int NRArea = 0;
    int Linf = INT_MAX, Lsup = INT_MIN; //Limites foram trocados
    short OndeLer = 1;
    TipoRegistro UltLido, R;
    // Bloco que fecha e reabre todos os apontadores de arquivo para evitar os erros que estavamos tendo nas chamdas recursivas, 
    fclose(*ArqLi);
    fclose(*ArqEi);
    fclose(*ArqLEs);
    *ArqLi = fopen("PROVAO.bin", "r+b");
    *ArqLEs = fopen("PROVAO.bin", "r+b");
    *ArqEi = fopen("PROVAO.bin", "r+b");
    //Para testar sem isso, basta comentar esse bloco
    
    fseek (*ArqLi, (Li - 1)*sizeof(TipoRegistro), SEEK_SET);
    fseek (*ArqEi, (Ei - 1)*sizeof(TipoRegistro), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;

    while(Ls >= Li){
        if (NRArea < TAMAREA-1){
            incrementaComparacoes();        
            if(OndeLer){
                incrementaComparacoes();
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            }
            else{
                incrementaComparacoes();                               
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);        
            }
            InserirArea(&Area, &UltLido, &NRArea);
            continue;
        }
        if(Ls == Es){
            incrementaComparacoes();                               
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        }
        else if (Li == Ei){
            incrementaComparacoes();                               
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        }
        else if (OndeLer){
            incrementaComparacoes();                               
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        }
        else{
            incrementaComparacoes();                               
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        }
        if (UltLido.nota < Lsup){ //Para ordenar de forma escendente, trocamos o sinal da comparação
            incrementaComparacoes();                               
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }
        if(UltLido.nota > Linf){   //Para ordenar de forma escendente, trocamos o sinal da comparação
            incrementaComparacoes();                               
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }
        InserirArea(&Area, &UltLido, &NRArea);
        if(Ei - Esq < Dir - Es){
            incrementaComparacoes();                               
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
            Linf = R.nota;
        }
        else{
            incrementaComparacoes();                               
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.nota;
        }
    }
    while(Ei <= Es){
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }

}

// Função utilizada por RetiraMax
void RetiraUltimo(TipoArea* Area,TipoRegistro* R){
    *R = Area->itens[(Area->num_celOcupadas) -1]; // retorna o registro a ser atualizado no limite
    (Area->num_celOcupadas) --; // retira o registro da Area (através da lista por array)


}

// Função utilizada por RetiraMin
void RetiraPrimeiro(TipoArea* Area,TipoRegistro* R){
    *R = Area->itens[0]; //funciona de forma análoga ao RetiraUltimo, porém, retira o primeiro
    //Arrasta os elementos do array (lista por array)
    TipoRegistro aux;
    for (int i=1; i<Area->num_celOcupadas; i++){
        aux = Area->itens[i];
        Area->itens[i-1] = aux;
    }
    (Area->num_celOcupadas) --;

}

// Retorna quantos registros estão em memoria
int ObterNumCelOcupadas(TipoArea* Area){
    return Area->num_celOcupadas;
}

// Inicializa o numero de celulas ocupadas
void FAVazia(TipoArea* Area){
    Area->num_celOcupadas = -1;
}

// Função utilizada pro InserenaArea
void InsereItem(TipoRegistro R, TipoArea* Area){
    if (Area->num_celOcupadas == -1){ //caso inicial (array vazio)
        incrementaComparacoes();
        Area->itens[0] = R; // basta adicionar o novo item e atualizar a variavel de controle num_celOcupadas
        Area->num_celOcupadas = 1;
    }
    else { // Chama o insertionsort, e incrementa a variavel de controle
       incrementaComparacoes();
       Area->itens[Area->num_celOcupadas] = R;
       (Area->num_celOcupadas) ++;
       insertion (Area->itens, Area->num_celOcupadas);
    }


}
