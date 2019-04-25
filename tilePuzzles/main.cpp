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
    /*Limita a execução a 10min e 8gb de ram*/
    system("ulimit -t 600 && ulimit -v 8000000");
    int i = 2;
    int j;

    int initialState[9]; //Estado inicial
    
    /*Leitura de entradas*/
    char* metodo = argv[1];
 
    while(i<argc)
    {
        j=0;
        while(j<9)
        {
            initialState[j] = atoi(argv[i]);
            j++;
            i++;
        }
        
        nodo inicial = CriaInicial(initialState);//cria o inicial
        /*Execucao do metodo(raiz)*/

        
        
        if (!strcmp(metodo, "-bfs"))
        {
            if(bfsGraph(inicial) != 1)
            {
                printf("\nSem Solucao\n");
            }            
        }
        else if (!strcmp(metodo, "-idfs"))
        {        
            if(idfs(inicial) != 1)
            {
                printf("\nSem Solucao\n");
            }            
        }
        else if (!strcmp(metodo, "-astar"))
        {
            if(astar(inicial) != 1)
            {
                printf("\nSem Solucao\n");
            }
        }
        else if (!strcmp(metodo, "-idastar"))
        {
            if(idastar(inicial) != 1)
            {
                printf("\nSem Solucao\n");
            }
        }
        else if (!strcmp(metodo, "-gbfs"))
        {
            if(gbfs(inicial) != 1)
            {
                printf("\nSem Solucao\n");
            }            
        }
    }
}