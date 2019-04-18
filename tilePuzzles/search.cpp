#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <set>
#include <cstring> 
#include "nodo.hpp"
#include "search.hpp"

using namespace std;

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
        /*Remove nodo de open*/
        open.erase(open.begin());
        /*Insere nodo em closed*/
        closed.emplace(n->id,n);
        /*Expande nodo*/
        expandidosCount++;
        for(int i=0;i<4;i++)
        {
            nLinha = move(n,i);
            if(nLinha != NULL)
            {
                /*Verifica se nLinha está em closed*/
                if(closed.count(nLinha->id) >= 1)
                {
                    /*Se esta em closed, nao gera*/
                    continue;
                }
                else /*Nao esta em closed*/
                {
                    geradosCount++;
                    /*Insere nodo gerado em open*/
                    open.insert(nLinha);
                    /*Verifica se o nodo gerado é GOAL*/
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

int depth_limited_search(nodo root, int limit)
{
    /*Verifica se a raiz e GOAL*/
    if(isGoal(root))
    {
        return 0;
    }
    
    if(limit > 0)
    {
        /*Para cada nodo filho gerado*/
        for(int i=0; i<4;i++)
        {
            nodo nLinha = move(root,i);
            if(nLinha == NULL)
            {
                continue;
            }
            else
            {
                /*Recursao*/
                int solution = depth_limited_search(nLinha,(limit-1));
                free(nLinha);
                if(solution == 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}


int idfs(nodo root)
{
    for(int limit=0; limit<10; limit++)
    {
        printf("limit %d \n",limit);
        int solution = depth_limited_search(root,limit);
        if(solution == 0)
        {
            return 0;
        }
    }
    return 1;
}
