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

#define SIZE 362880

using namespace std;

/*
 * 
 */

typedef struct Nodo *nodo;
struct Nodo
{
    int id;
    int estado[9];
    nodo pai;
    nodo filhos[4];
};


int calcId(int state[9]);
int bfsTree(nodo root);
nodo move(nodo pai, int opc);
int verificaPosicaoBlank(nodo atual);
void mostraMenu(nodo atual);
int isGoal(nodo n);
nodo CriaNodoFilho(nodo pai, int pos, int posAux, int nFilho);


nodo CriaInicial(int state[9])
{
    nodo ini = (nodo) malloc(sizeof(struct Nodo));
    
    if(ini != NULL)
    {
        memcpy(ini->estado, state, sizeof(int) * 9);//copia pai pro filho
        
        ini->id = calcId(state);
        ini->filhos[0] = NULL;
        ini->filhos[1] = NULL;
        ini->filhos[2] = NULL;
        ini->filhos[3] = NULL;
                
        return ini;
    }
    //Se nao criar o nodo
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
            
            return novo;
        }
        exit(1);
}


int isGoal(nodo n)
{
    
    int goal[9] = {1,2,3,4,5,6,7,8,0};
    
    for(int i=0; i<9; i++)
    {
        if (n->estado[i] != goal[i])
        {
            return 0;
        }
    }
    return 1;
}

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






void mostraMenu(nodo atual)
{
    //system("clear");
    printf("\n\t%d %d %d\n", atual->estado[0], atual->estado[1], atual->estado[2]);
    printf("\t%d %d %d\n", atual->estado[3], atual->estado[4], atual->estado[5]);
    printf("\t%d %d %d\n\n", atual->estado[6], atual->estado[7], atual->estado[8]);
//    printf("Digite uma tecla para mover o blank:\n");
//    printf("w - cima\n");
//    printf("a - esquerda\n");
//    printf("d - direita\n");
//    printf("s - baixo\n");
//    printf("0 - Sair\n");
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

int bfsTree(nodo root)
{
    /*cria closed set*/
    unordered_map<int,nodo> closed;
    /***********/
    

    
    /*Verifica se a raiz nao e GOAL*/
    if(isGoal(root))
    {
        return 1;
    }
    int geradosCount = 0;
    int expandidosCount = 0;
    nodo nLinha = NULL;
    
    /*cria open set*/
    set<nodo> open;
    /*Insere raiz em open*/
    open.insert(root);
    /*Itera sobre open*/
    while(!open.empty())
    {
                    
        /*Recupera nodo de open*/
        nodo n = *open.begin();
        open.erase(open.begin());
        /*Expande nodo*/
        expandidosCount++;
        
        /*Insere nodo em closed*/
        closed.emplace(n->id,n);
        for(int i=0;i<4;i++)
        {
            nLinha = move(n,i);
            if(nLinha != NULL)
            {
                /*Verifica se nLinha está em closed*/
                if(closed.count(nLinha->id) >= 1)
                {
                    continue;
                }
                else /*Nao esta em closed*/
                {
                    geradosCount++;
                    printf("%d c %ld o %ld\n",geradosCount,closed.size(),open.size());
                    if(geradosCount % SIZE == 0)
                    {
                        printf("MAXIMO");
                        
                    }         
                    /*Insere elemento em open*/
                    open.insert(nLinha);
                    if(isGoal(nLinha))
                    {
                        printf("GOAL ");
                        for(int j=0;j<9;j++)
                        {
                            printf("%d ",nLinha->estado[j]);
                        }
                        printf("\nnodos gerados %d\n",geradosCount);
                        printf("nodos expandidos %d\n",expandidosCount);
                        return 0;

                    }
                }

            }
        }
   }
    /*Nao tem solucao*/
    return 1;

}



/*MAIN*/
int main(int argc, char** argv)
{
    int i = 2;
    int j;
    int initialState[9] = {8,1,2,0,4,3,7,6,5}; //Estado inicial
    
    
    /*Leitura de entradas*/
    printf("%s",argv[1]);
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
        bfsTree(atual) == 0 ? printf("\nSolucao Encontrada\n") : printf("\nSem Solucao\n");
//    }
    
}