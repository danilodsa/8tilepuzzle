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
    //12,9,0,6,8,3,5,14,2,4,11,7,10,1,15,13
    int initialState[16] = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //Estado inicial
    nodo inicial = CriaInicial(initialState);//cria o inicial
    astar(inicial) == 1 ? printf("\nSolucao Encontrada\n") : printf("\nSem Solucao\n");
    return 0;
}

