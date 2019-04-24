/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: danilo
 *
 * Created on 23 de Abril de 2019, 16:59
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
int main(int argc, char** argv) 
{
    //int initialState[16] = {7,11,8,3,14,0,6,15,1,4,13,9,5,12,2,10}; //Estado inicial
    int initialState[16] = {12,9,0,6,8,3,5,14,2,4,11,7,10,1,15,13}; //Estado inicial
    //int initialState[16] = {13,0,9,12,11,6,3,5,15,8,1,10,4,14,2,7}; //Estado inicial
    
    
    
  /*Leitura de entradas*/
    char* metodo = argv[1];
    
    int i=2;
    int j;
    while(i<argc)
    {
        j=0;
        while(j<16)
        {
            initialState[j] = atoi(argv[i]);
            j++;
            i++;
        }    
        nodo inicial = CriaInicial(initialState);//cria o inicial
        astar(inicial) == 1 ? printf("\nSolucao Encontrada\n") : printf("\nSem Solucao\n");
    }
        return 0;
}

