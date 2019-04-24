#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <set>
#include <cstring> 
#include "nodo.hpp"

using namespace std;

nodo CriaInicial(int state[9])
{
    nodo ini = (nodo) malloc(sizeof(struct Nodo));
    
    if(ini != NULL)
    {
        /*copia pai clock_t start = clock();pro filho*/
        memcpy(ini->estado, state, sizeof(int) * 9);
        
        ini->pai=NULL;
        ini->id = calcId(state);
        ini->filhos[0] = NULL;
        ini->filhos[1] = NULL;
        ini->filhos[2] = NULL;
        ini->filhos[3] = NULL;
        ini->h = manhattan(state);
        ini->g = 0;
        return ini;
    }
    /*Se nao criar o nodo*/
    exit(1);
}

//cria nodo do tipo filho, copia, e troca as posições
nodo CriaNodoFilho(nodo pai, int pos, int posAux, int nFilho)//p1 e p2 devem trocar de posição
{
	nodo novo = (nodo) malloc(sizeof(struct Nodo));
        if(novo != NULL)
        {
            memcpy(novo->estado, pai->estado, sizeof(int) * 9);
            //troca posições
            int aux = novo->estado[pos]; 
            novo->estado[pos] = novo->estado[posAux];
            novo->estado[posAux] = aux;
            novo->pai = pai;    
            pai->filhos[nFilho] = novo;

            novo->id = calcId(novo->estado);
            
            novo->h = manhattan(novo->estado);
            novo->g = pai->g + 1;
            
            return novo;
        }
        exit(1);
}

int isGoal(nodo n)
{
    
    int goal[9] = {0,1,2,3,4,5,6,7,8};
    
    for(int i=0; i<9; i++)
    {
        if (n->estado[i] != goal[i])
        {
            return 0;
        }
    }
    return 1;
}

/*Calcula ID do nodo atraves do estado*/
int calcId(int state[9])
{
    int soma = 0;
    int multiplier;
    
    for(int i=0;i<9;i++)
    {
        multiplier = 1;
        for (int j=i+1; j<9; j++)
        {
            multiplier *= 10;
        }
        soma += multiplier * state[i];
    }
    return soma;
}

void imprimeNodo(nodo n)
{
    //system("clear");
    printf("\n\t%d %d %d\n", n->estado[0], n->estado[1], n->estado[2]);
    printf("\t%d %d %d\n", n->estado[3], n->estado[4], n->estado[5]);
    printf("\t%d %d %d\n\n", n->estado[6], n->estado[7], n->estado[8]);

}

//faz um for até encontrar o blank
int verificaPosicaoBlank(nodo atual)
{
    for (int i = 0; i < 9; i++)
    {
        if (atual->estado[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

//verificação posição do blank, depois verifica intenção de movimento, e se possivel cria uma copia do filho com o movimento
nodo move(nodo pai, int opc)
{
    nodo atual = NULL;
    int pos = verificaPosicaoBlank(pai);
    int posAux;
    if (opc == 0) //w
    {
        if (pos >= 3)//se é maior que 2 pode mover para cima
        {
            posAux = pos - 3;
            atual = CriaNodoFilho(pai, pos, posAux,0);
        }
    }
    else if (opc == 1) //a
    {
        if (pos % 3 != 0)//se o resto de divisão por 3 é zero então está na lateral esquerda
        {
            posAux = pos - 1;
            atual = CriaNodoFilho(pai, pos, posAux,1);
        }
    }
    else if (opc == 2) //d
    {
        if (pos % 3 != 2)//se o resto de divisão por 3 é 2 então está na lateral direita
        {
            posAux = pos + 1;
            atual = CriaNodoFilho(pai, pos, posAux,2);
        }
    }
    else if (opc == 3) //s
    {
        if (pos <= 5)//se é menor que 6 pode mover pra baixo
        {
            posAux = pos + 3;
            atual = CriaNodoFilho(pai, pos, posAux,3);
        }
    }
    return atual;
}

int extractPath(nodo n)
{
    int count = 0;
    while(n->pai != NULL)
    {
        count++;
        n = n->pai;
    }
    return count;
}



/***********************HEURISICA***********************/
int manhattanElementoUnico(int num, int pos)
{
    return (abs(num / 3 - pos / 3) + abs(num % 3 - pos % 3));
    //printf("%d, %d, resultado:%d\n", num+1, pos+1, x);
}

int manhattan(int vet[9])
{
    int soma = 0;
    for (int i = 0; i < 9; i++)
    	if (vet[i] != 0)
            soma += manhattanElementoUnico(vet[i], i);
    return soma;
}