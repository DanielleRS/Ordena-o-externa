#include <iostream>
#include <iomanip>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "Aluno.hpp"
#include "geraArqs.hpp"
#include "Fita.hpp"
#include "QuickExterno.hpp"
#include "contaDados.hpp"

using namespace std;

int main(int argc, char* argv[]){
   	short metodo;
	int quantidade;
	char situacao;
	
	clock_t c1, c2;
	double tempo = 0;

	if(argc == 4 || argc == 5){
		metodo = atoi(argv[1]);
		quantidade = atoi(argv[2]);
		situacao = argv[3][0];
	}
	else{
		cout <<"FORMATO DE EXECUÇÃO: pesquisa <método> <quantidade> <situação> [-P]\n";
		exit(1);
	}
    
    geraArq_bin(situacao, quantidade); //a partir da quantidade e situação esclhidas gera um binario para ser trabalhado pelo método de escolha
 	
    if(argc == 5 && argv[4][1] =='P'){
        FILE* arq_entrada;
        if((arq_entrada=fopen("PROVAO.bin","r+b"))==NULL){
            puts ("Arquivo nao pode ser aberto...");
            exit (1);
        }
        fseek(arq_entrada,0,2);
        long tam = ftell(arq_entrada)/sizeof(Aluno);
        rewind(arq_entrada);
        cout << "Imprimindo chaves" <<endl;
        Aluno a;
        for (int i = 0; i < tam; ++i){
            fread(&a, sizeof(Aluno), 1,arq_entrada);
            cout<<a.inscricao << " " << a.nota<< " " << a.estado<< " " << a.cidade << " " << a.curso<<endl;
        }
        rewind(arq_entrada);
        fclose (arq_entrada);
    } 
    
    //METODOS : (DE 1 A 4)
	if (metodo == 1) {
        
        iniciaContadores(); //inicializa os contadores de leituras, comparações e leituras com 0
        
        Fita fitas[N_FITAS];
        Aluno area[TAMAREA]; 
        
        c1 = clock();
        inicializaFitas(fitas,N_FITAS);

        geraBlocosOrdenados(fitas,area);
        
        int fitaFinal = intercalaBlocos(fitas,N_FITAS);
        cout << "fita final: " << fitaFinal << endl;
        
        geraFitas_txt(fitas);
        
        deleta_arqs(fitas);
        c2 = clock();
        
        tempo = ((c2 - c1)*1.0)/CLOCKS_PER_SEC; //calcula o tempo gasto em segundos
	}

	else if(metodo == 2){

	}

	else if(metodo == 3){
		
	
	}

	else if(metodo == 4){
        
        iniciaContadores(); //inicializa os contadores de leituras, comparações e leituras com 0
        
        FILE* ArqLEs;   // controla o Ls e o Es
        FILE* ArqLi;    // controla o Li
        FILE* ArqEi;    // controla o Ei
        
        //Abre os ponteiros no arquivo de entrada        
        if((ArqLEs=fopen("PROVAO.bin","r+b"))==NULL){
            puts ("Arquivo nao pode ser aberto...");
            exit (1);
        }
        
        if((ArqLi=fopen("PROVAO.bin","r+b"))==NULL){
            puts ("Arquivo nao pode ser aberto...");
            exit (1);
        }
        
        if((ArqEi=fopen("PROVAO.bin","r+b"))==NULL){
            puts ("Arquivo nao pode ser aberto...");
            exit (1);
        }
        
        c1 = clock();
        QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, quantidade);  
        c2 = clock();
        
        tempo = ((c2 - c1)*1.0)/CLOCKS_PER_SEC; //calcula o tempo gasto em segundos
        
        fclose (ArqLi);
        fclose (ArqEi);
        fclose (ArqLEs);
        
        geraArq_txt (quantidade); //a partir do binario ordenado, gera um txt.
	}
  
	cout << endl;

    // Exibe os resuldados para analise
    cout << "QTD: " << quantidade <<endl;
	cout << "TEMPO DE EXECUCAO: " << fixed << tempo << " segundos" << endl;
	cout << "LEITURAS: " << returnLeituras() << endl;
    cout << "ESCRITAS: " << returnEscritas() << endl;
	cout << "COMPARACOES: " << returnComparacoes() << endl;

	return 0;
}
