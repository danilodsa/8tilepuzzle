/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newfile.hpp
 * Author: danilo
 *
 * Created on 17 de Abril de 2019, 13:40
 */

#ifndef NEWFILE_HPP
#define NEWFILE_HPP

typedef struct Nodo *nodo;
struct Nodo
{
    long unsigned int id;
    int estado[16];
    int h;
    int g;
    nodo pai;
    nodo filhos[4];
};

long unsigned int calcId(int state[16]);
nodo move(nodo pai, int opc);
int verificaPosicaoBlank(nodo atual);
void imprimeNodo(nodo atual);
int isGoal(nodo n);
nodo CriaNodoFilho(nodo pai, int pos, int posAux, int nFilho);
nodo CriaInicial(int state[16]);
int manhattan(int vet[16]);
int extractPath(nodo n);
void destruct(nodo n);
#endif /* NEWFILE_HPP */

