#include <iostream>
#include <cstring>
#include "stdlib.h"
#include "stdio.h"
#include "QuickSort.hpp"
#include "Aluno.hpp"
#include "geraArqs.hpp"
#include "QuickExterno.hpp"

using namespace std;

#define TAM 471705 //Quantidade máxima de resgistros 

//Le o arquivo de texto até a quantidade escolhida e gera um binario
void geraArq_bin(char situacao, int quantidade){
	FILE* PROVAO;
	FILE* ORD = NULL;
	
	Aluno* Alunos = new Aluno[quantidade];
	Aluno a;

	if((PROVAO = fopen("PROVAO.TXT", "r"))==NULL){
		cout << "erro na abertura do arquivo";
		exit(1);
	}

    for (int k = 0; k < quantidade;){
        fscanf(PROVAO,"%ld %lf %s %[^\n]s",&a.inscricao, &a.nota, a.estado, a.cidade);
        //Bloco que separa as duas ultimas strings (curso e nota) que são lidas juntas 
        for (int i=0, j=0, b=0; i < 49; ++i){
            if(!b && a.cidade[i+1]==' ' && a.cidade[i+2]==' '){
                a.cidade[i+1] = '\0';
                b=1;
                i+=2;
            }
            else if (b && a.cidade[i+1] != ' '){
                a.curso[j++] = a.cidade[i];
                if (j>=31) break;
            }   
        }
        Alunos[k++] = a;
    }
    
    if (situacao == '3'){
        if((ORD = fopen("PROVAO.bin", "wb"))==NULL){
        cout << "erro na abertura do arquivo";
        exit(1);
        }
        fwrite(Alunos,sizeof(Aluno),quantidade,ORD);
    }
    else{
        quicksort(Alunos,quantidade);   // Caso não seja a ultima situação (desordenado) ordena a quntidade de 
                                        //registos e escreve no arquivo de saída

        if(situacao == '1'){
            if((ORD = fopen("PROVAO.bin", "wb"))==NULL){
                cout << "erro na abertura do arquivo";
                exit(1);
            }
            fwrite(Alunos,sizeof(Aluno),quantidade,ORD);
        }   
        else if(situacao == '2'){
            if((ORD = fopen("PROVAO.bin", "wb"))==NULL){
                cout << "erro na abertura do arquivo";
                exit(1);
            }
            Aluno aux;
            for (int i = 0; i < quantidade/2; ++i){
                aux = Alunos[i];
                Alunos[i] = Alunos[(quantidade -1)-i];
                Alunos[(quantidade -1)-i] = aux;
            }
            fwrite(Alunos,sizeof(Aluno),quantidade,ORD);
        }    
    }
	fclose(PROVAO);
	fclose(ORD);
	delete [] Alunos;
}

// Volta o arquivo binario que foi usado como entrada para um arquivo texto afim de validar a ordenação
void geraArq_txt (int quantidade){
    FILE* arq;
    FILE* arqTxt;
    Aluno A;
         
    if ((arqTxt = fopen ("PROVAO_ORD.txt", "w")) == NULL ){
        cout<<"Erro ao gerar arquivo final (PROVAO_ORD)"<<endl;
        exit(1);
    }
    if ((arq = fopen ("PROVAO.bin", "rb")) == NULL ){
        cout<<"Erro ao gerar arquivo final (PROVAO_ORD)"<<endl;
        exit(1);
    }
    for (int i=0; i<quantidade; i++){ // lê do arquivo binário e converte para o arquivo txt
        fread (&A, sizeof(Aluno), 1,arq);
        fprintf(arqTxt, "%ld %.1lf %s %s    %s\n",A.inscricao, A.nota, A.estado, A.cidade, A.curso);
         
    }
    fclose(arqTxt);
    fclose (arq);
    remove("PROVAO.bin");
}

//Transforma as fitas binarias em texto
void geraFitas_txt (Fita* fitas){
    FILE* arq;
    FILE* arqTxt;
    char aux[20];
    Aluno A;
    for (int i = 0; i < N_FITAS; ++i){
        strcpy(aux,fitas[i].nome_arq);
        strcat(aux,".txt");
        if ((arqTxt = fopen (aux, "w")) == NULL ){
            cout<<"Erro ao gerar arquivo final (PROVAO_ORD)"<<endl;
            exit(1);
        }
        if ((arq = fopen (fitas[i].nome_arq, "rb")) == NULL ){
            cout<<"Erro ao gerar arquivo final"<<endl;
            exit(1);
        }
        fseek(arq,0,2);
        long tam = ftell(arq)/sizeof(Aluno);
        rewind(arq);
    
        for (int i=0; i<tam; i++){ // lê do arquivo binário e converte para o arquivo txt
            fread (&A, sizeof(Aluno), 1,arq);
            fprintf(arqTxt, "%ld %.1lf %s %s    %s\n",A.inscricao, A.nota, A.estado, A.cidade, A.curso);
        }
        fclose(arqTxt);
        fclose (arq);
    }
}