#ifndef ALUNOS_HPP_
#define ALUNOS_HPP_

#define TAMAREA 10

typedef struct{
    long inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Aluno;

void insertion (Aluno*,int);

#endif
