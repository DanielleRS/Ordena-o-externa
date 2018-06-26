#include <cstring>
#include <iostream>
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "Fita.hpp"
#include "contaDados.hpp"
#include "QuickSort.hpp"
using namespace std;

void inicializaFitas(Fita *fitas, int tam){
    char nomeFita[20];
    char num[3];

    for(int i=0, j=0; i<tam; i++){
        if(i < tam/2){
            incrementaComparacoes();
            fitas[i].dir = true;
            fitas[i].ativa = true;
            fitas[i].n_blocos = 0;
            fitas[i].pos_leitura = 0;
        }
        else{
            incrementaComparacoes();
            fitas[i].dir = false;
            fitas[i].ativa = true;
            fitas[i].n_blocos = 0;
            fitas[i].pos_leitura = 0;
        }
        TLista_Inicia(&fitas[i].tam_blocos);
        //gera nome dos arquivos das fitas e seta na estrutura
        if(i<10){                
            num[0] = 48+i;
            num[1] = '\0';
            strcpy(nomeFita, "fita");
            strcat(nomeFita, num);
            strcat(nomeFita, ".bin");
            strcpy(fitas[i].nome_arq, nomeFita);    
        }
        else{       
            num[0] = 49;
            num[1] = 48+(i-10);
            num[2] = '\0';
            strcpy(nomeFita, "fita");
            strcat(nomeFita, num);
            strcat(nomeFita, ".bin"); 
            strcpy(fitas[i].nome_arq, nomeFita); 
            j++;
        }
    }
}

void fecha_fitas(Fita* fitas){
    for (int i = 0; i < N_FITAS; ++i)
        fclose(fitas[i].arq);
}

void abrir_fitas(Fita* fitas){
    for (int i = 0; i < N_FITAS; ++i){
        if((fitas[i].arq = fopen(fitas[i].nome_arq,"wb")) == NULL){
            puts ("Fita nao pode ser aberta...");
            exit (1);
        }
    }
}

void abrir_fitas_leituras(Fita* fitas){
    for (int i = 0; i < N_FITAS; ++i){
        if((fitas[i].arq = fopen(fitas[i].nome_arq,"r+b")) == NULL){
            puts ("Fita não pôde ser aberta...");
            exit (1);
        }
        fseek(fitas[i].arq,fitas[i].pos_leitura,0);
    }
}

void deleta_arqs(Fita* fitas){
    for (int i = 0; i < N_FITAS; ++i)
        remove(fitas[i].nome_arq);
}

void geraBlocosOrdenados(Fita* fitas, Aluno* area){
    int i=0, j=0, n=0;    
    FILE* arq_entrada;

    if((arq_entrada=fopen("PROVAO.bin","r+b"))==NULL){
        puts ("Arquivo nao pode ser aberto...");
        exit (1);
    }
    
    abrir_fitas(fitas);
    
    while(true){
        incrementaLeituras();
        n = fread(area,sizeof(Aluno),TAMAREA,arq_entrada);
        if(n == TAMAREA){
            incrementaComparacoes();
            quicksort(area,TAMAREA);
            if(fitas[i].dir == true){
                incrementaComparacoes();
                incrementaEscritas();
                fwrite(area,sizeof(Aluno),TAMAREA,fitas[i].arq);
                fitas[i].n_blocos++;
               insereFim(&fitas[i].tam_blocos, TAMAREA);
                i++;
            }
            else{
                incrementaComparacoes();
                i=0; j=1;
                incrementaEscritas();
                fwrite(area,sizeof(Aluno),TAMAREA,fitas[i].arq);
                fitas[i].n_blocos++;
               insereFim(&fitas[i].tam_blocos, TAMAREA);
                i++;
            }
        }
        else if((n < TAMAREA) && (n != 0)){
            incrementaComparacoes();
            quicksort(area,n);
            if(j == 0){
                incrementaComparacoes();
                if(fitas[i].dir == true){
                    incrementaComparacoes();
                    incrementaEscritas();
                    fwrite(area,sizeof(Aluno),n,fitas[i].arq);
                    fitas[i].n_blocos++;
                    insereFim(&fitas[i].tam_blocos, n);
                }
                else{
                    incrementaComparacoes();
                    i=0; j=1;
                    incrementaEscritas();
                    fwrite(area,sizeof(Aluno),n,fitas[i].arq);
                    fitas[i].n_blocos++;
                    insereFim(&fitas[i].tam_blocos, n);
                }
            }
        }
        else break;
    } // fim do while
    fecha_fitas(fitas);
    rewind(arq_entrada);
    fclose(arq_entrada);
}

int intercalaBlocos(Fita* fitas, int tam){
    Aluno *areaIntercala = new Aluno[tam/2];
    double maior = INT_MIN;
    int posMaior=0, posMaior2=0, i, j, nFitasDes=0, aux=tam/2, nFitasSemBlocos=tam/2, nIntercalacao=0, aux2=0, aux3=0, aux4=0;
    bool entrouNoWhileInterno=false, transicao=false, acabouDeInverter=false;

    while(nFitasSemBlocos < tam-1){ // apenas uma fita possui um bloco
    	abrir_fitas_leituras(fitas);
    	nFitasDes=0; // reinicia a contagem de fitas desativadas
    	for(i=0, j=0; i<tam; i++){ // coloca o primeiro registro de cada bloco na memoria
			if(fitas[i].dir == true){ // pega registro apenas de fita de entrada
				if(fitas[i].n_blocos > 0){
					incrementaComparacoes();
					fread(&areaIntercala[j],sizeof(Aluno),1,fitas[i].arq);
					if(areaIntercala[j].nota > maior){
						incrementaComparacoes();
						maior = areaIntercala[j].nota;
						posMaior = j;
					}
					j++;
					decrementaPrimeiro(&fitas[i].tam_blocos);
				}
				else if(fitas[i].n_blocos == 0){
					nFitasDes++;
					if(aux4 == 0){
						nFitasSemBlocos++;
					}
					areaIntercala[i].nota = -1;
				}
			}
		}
    	aux4++;
		maior = INT_MIN; // valor de maior e reiniciado

		if(fitas[(tam/2)-1].dir == true) i=aux; // se fita 9 for de entrada, a primeira de saida eh a fita 10
		else i=aux; // caso contrario fita 1 eh de saida

		while(nFitasDes < (tam/2)){ // intercalacao dos blocos correntes em uma fita de saida
			if(transicao){ // se a segunda metade de fitas for de entrada posMaior2 aponta pra fita e posMaior pra memoria
				posMaior2 = posMaior + tam/2;
			}
			else{
				posMaior2 = posMaior;
			}
			incrementaEscritas();
			fwrite(&areaIntercala[posMaior],sizeof(Aluno),1,fitas[i].arq); // escreve na fita de saida
			if (fitas[posMaior2].ativa == false){
				areaIntercala[posMaior].nota = -1;
			}
			incrementaPos(&fitas[i].tam_blocos, fitas[i].n_blocos);
			if(fitas[posMaior2].ativa == true){
				incrementaComparacoes();
				incrementaLeituras();
				fread(&areaIntercala[posMaior],sizeof(Aluno),1,fitas[posMaior2].arq); // le o proximo registro
				decrementaPrimeiro(&fitas[posMaior2].tam_blocos);
				if(getPrimeiro(&fitas[posMaior2].tam_blocos) == 0){
					fitas[posMaior2].ativa = false;
					removeInicio(&fitas[posMaior2].tam_blocos);
					fitas[posMaior2].n_blocos--;
					if(fitas[posMaior2].n_blocos == 0){
						nFitasSemBlocos++;
					}
					nFitasDes++;
					// desativa a posicao do vetor referente a fita desativada
					if(nFitasDes == (tam/2)){
						quicksort(areaIntercala,tam/2);
						for(int k=0; k<tam/2; k++){
							if(areaIntercala[k].nota != -1){
								fwrite(&areaIntercala[k],sizeof(Aluno),1,fitas[i].arq);
							}
							else break;
						}
					}
				}
				entrouNoWhileInterno = true;
			}

			for(int k=aux2; k<aux2+tam/2; k++){ // caso as fitas estejam invertidas k comeca em 10
				if(!transicao){
					if(areaIntercala[k].nota != -1){
						if(areaIntercala[k].nota > maior){
							incrementaComparacoes();
							maior = areaIntercala[k].nota;
							posMaior = k;
						}
					}
				}
				else{
					if(areaIntercala[k-tam/2].nota != -1){
						if(areaIntercala[k-tam/2].nota > maior){
							incrementaComparacoes();
							maior = areaIntercala[k-tam/2].nota;
							posMaior = k-tam/2;
						}
					}
				}
			}
			maior = INT_MIN;
		}

		if(aux < tam/2){
			for(int k=tam/2; k<tam; k++){
				fitas[k].ativa = true;
			}
			aux3 = tam/2;
		}
		else if(aux >= tam/2){
			for(int k=0; k<tam/2; k++){
				fitas[k].ativa = true;
			}
			aux3 = 0;
		}

		if(entrouNoWhileInterno){
			fitas[i].n_blocos++; // mais um bloco foi gerado na fita de saida
			nFitasSemBlocos--;
		}

		i++; aux++; nIntercalacao++;

		//inverte fitas
		if(fitas[aux3].n_blocos == 0){
			if(aux >= tam/2)
                aux = 0;
            else 
                aux = tam/2;
            
            for(int k=0; k<tam; k++){
				if(fitas[k].dir == true){
					fitas[k].dir = false; // fitas de entrada se tornam de saida
					fitas[k].pos_leitura = 0;
				}
				else{
					fitas[k].dir = true; // fitas de saida se tornam de entrada
					fitas[k].pos_leitura = 0;
				}
			}

            if(aux2 == 0)
                aux2 = tam/2;
            else 
                aux2 = 0;
            
            if(transicao){
            	transicao = false;
            }
            else{
            	transicao = true;
            }

            acabouDeInverter = true;
		}

		if(aux==tam){ aux = tam/2;}
		else if(aux==tam/2){ aux = 0;}

		for(int k=0; k<tam; k++){
			if(!acabouDeInverter){
				fitas[k].pos_leitura = ftell(fitas[k].arq);
			}
		}

		entrouNoWhileInterno = false;

		acabouDeInverter = false;

		fecha_fitas(fitas);
    }

    return i-1;
}
