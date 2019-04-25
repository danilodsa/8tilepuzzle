#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <set>
#include <cstring> 
#include "nodo.hpp"

using namespace std;

nodo CriaInicial(int state[16])
{
    nodo ini = (nodo) malloc(sizeof(struct Nodo));
    
    if(ini != NULL)
    {
        /*copia pai pro filho*/
        memcpy(ini->estado, state, sizeof(int) * 16);
        
        ini->id = calcId(ini->estado);
        ini->pai = NULL;
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
            memcpy(novo->estado, pai->estado, sizeof(int) * 16);
            //troca posições
            int aux = novo->estado[pos]; 
            novo->estado[pos] = novo->estado[posAux];
            novo->estado[posAux] = aux;
            novo->filhos[0] = NULL;
            novo->filhos[1] = NULL;
            novo->filhos[2] = NULL;
            novo->filhos[3] = NULL;            
            
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
    
    int goal[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    
    for(int i=0; i<16; i++)
    {
        if (n->estado[i] != goal[i])
        {
            return 0;
        }
    }
    return 1;
}

/*Calcula ID do nodo atraves do estado*/
long unsigned int calcId(int state[16])
{
    long unsigned int soma = 0;
    long unsigned int multiplier;
    
    for(int i=0;i<16;i++)
    {
        multiplier = 1;
        for (int j=i+1; j<16; j++)
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
    printf("\n\t%d %d %d %d\n", n->estado[0], n->estado[1], n->estado[2], n->estado[3]);
    printf("\t%d %d %d %d\n", n->estado[4], n->estado[5], n->estado[6], n->estado[7]);
    printf("\t%d %d %d %d\n", n->estado[8], n->estado[9], n->estado[10], n->estado[11]);
    printf("\t%d %d %d %d\n", n->estado[12], n->estado[13], n->estado[14], n->estado[15]);

}

//faz um for até encontrar o blank
int verificaPosicaoBlank(nodo atual)
{
    for (int i = 0; i < 16; i++)
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
        if (pos >= 4)//se é maior que 2 pode mover para cima
        {
            posAux = pos - 4;
            atual = CriaNodoFilho(pai, pos, posAux,0);
        }
    }
    else if (opc == 1) //a
    {
        if (pos % 4 != 0)//se o resto de divisão por 4 é zero então está na lateral esquerda
        {
            posAux = pos - 1;
            atual = CriaNodoFilho(pai, pos, posAux,1);
        }
    }
    else if (opc == 2) //d
    {
        if (pos % 4 != 3)//se o resto de divisão por 3 é 2 então está na lateral direita
        {
            posAux = pos + 1;
            atual = CriaNodoFilho(pai, pos, posAux,2);
        }
    }
    else if (opc == 3) //s
    {
        if (pos <= 11)//se é menor que 6 pode mover pra baixo
        {
            posAux = pos + 4;
            atual = CriaNodoFilho(pai, pos, posAux,3);
        }
    }
    return atual;
}

/*Contagem do caminho*/
int extractPath(nodo n)
{
    int pathLen = 0;
    while(n->pai != NULL)
    {
        pathLen++;
        n = n->pai;
    }
    return pathLen;
}



/***********************HEURISICA***********************/
int manhattanElementoUnico(int num, int pos)
{
	return (abs(num / 4 - pos / 4) + abs(num % 4 - pos % 4));
	//printf("%d, %d, resultado:%d\n", num+1, pos+1, x);
}

int manhattan(int vet[16])
{
	int soma = 0;
	for (int i = 0; i < 16; i++)
		if (vet[i] != 0)
			soma += manhattanElementoUnico(vet[i], i);
	return soma;
}

void destruct(nodo n)
{
    if(n == NULL) return;
    
    for(int i=0; i<4; i++)
    {
        destruct(n->filhos[i]);
    }
    free(n);
}