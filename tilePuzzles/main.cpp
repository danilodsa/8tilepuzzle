/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: danilo
 *
 * Created on 15 de Abril de 2019, 15:25
 */

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <set>
#include <cstring> 
#include "nodo.hpp"
#include "search.hpp"


using namespace std;

/*
 * 
 */

/*MAIN*/
int main(int argc, char** argv)
{
    int i = 2;
    int j;
    int initialState[9] = {3,0,8,7,5,2,1,6,4}; //Estado inicial
    
    
    /*Leitura de entradas*/
    char* metodo = argv[1];
 
//    while(i<argc)
//    {
//        j=0;
//        while(j<9)
//        {
//            initialState[j] = atoi(argv[i]);
//            j++;
//            i++;
//        }
        nodo atual = CriaInicial(initialState);//cria o inicial
        /*Execucao do metodo(raiz)*/
        //bfsTree(atual) == 0 ? printf("\nSolucao Encontrada\n") : printf("\nSem Solucao\n");
        idfs(atual) == 0 ? printf("\nSolucao Encontrada\n") : printf("\nSem Solucao\n");
//    }
    
}