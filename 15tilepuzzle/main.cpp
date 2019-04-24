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
    int initialState[16];
    
  /*Leitura de entradas*/
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
        if(astar(inicial) == 0)
        {
            printf("Sem solução.");
        }
                
    }
        return 0;
}

