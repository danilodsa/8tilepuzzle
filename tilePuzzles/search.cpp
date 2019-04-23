#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>
#include "nodo.hpp"
#include "search.hpp"
#include <cmath>

using namespace std;

/**************************BFS******************************/
int bfsGraph(nodo root)
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
                        imprimeNodo(nLinha);
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

/**************************IDFS******************************/

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

/**************************ASTAR******************************/

class compare
{
  bool reverse;
public:
  compare(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const nodo lhs, const nodo rhs) const
  {
//    if (reverse) return (lhs>rhs);
//    else return (lhs<rhs);
        int lhsF = lhs->g + lhs->h;
        int rhsF = rhs->g + rhs->h;

        if(lhsF > rhsF){
            return 0;
        }
        else if(lhsF < rhsF){
            return 1;
        }
        else if(lhs->h > rhs->h){
            return 0;
        }
        else{
            return 1;
        }      
  }
};


int astar(nodo root)
{
    int gen = 0;
    int exp = 0;
    /*cria closed set*/
    unordered_map<int,nodo> closed;
    /***********/
    /*cria open set*/
    priority_queue<nodo,vector<nodo>,compare> open;
    /**************/    
    if(root->h < INFINITY)
    {
        open.push(root);
    }
    while(!open.empty())
    {
        nodo n = open.top();
        open.pop();
        
        if(closed.count(n->id) <= 0)
        {
            closed.emplace(n->id,n);
            if(isGoal(n))
            {
                imprimeNodo(n);
                printf("Nodos Gerados: %d\n", gen);
                printf("Nodos Expandidos: %d", exp);
                return 0;
            }
            exp++;
            for(int i=0; i<4; i++)
            {
                nodo nLinha = move(n,i);
                gen++;
                if(nLinha != NULL)
                {
                if(nLinha->h < INFINITY)
                    {
                        open.push(nLinha);
                    }
                }
            }
        }
                
    }
    
}

/**************************IDASTAR******************************/

int idastar(nodo root)
{
    int fLimit = root->h;
    while(fLimit != INFINITY)
    {
        pair<int,int> ret = idastar_recursive_serach(root,fLimit);
        fLimit = ret.first;
        int solution = ret.second;
        if(solution != 0)
        {
            return 0;
        }
    }
    return 1;
        
}

pair<int,int> idastar_recursive_serach(nodo n,int fLimit)
{
    int fn = n->g + n->h;
    
    if(fn > fLimit)
    {
        fLimit = fn;
        return make_pair(fn,NULL);
    }

    if(isGoal(n))
    {
        imprimeNodo(n);
        return make_pair(NULL,0);
    }
    
    int  nextLimit = INFINITY;
    /*Para cada filho GERADO*/
    for(int i=0; i<4; i++)
    {
        nodo nLinha = move(n,i);
        if(nLinha != NULL)
        {
            if(nLinha->h < INFINITY)
            {
                pair<int,int> ret = idastar_recursive_serach(nLinha,fLimit);
                int recLimit = ret.first;
                int solution = ret.second;
                if (solution == 0)
                {
                    return make_pair(NULL,solution);
                }
                nextLimit = min(nextLimit,recLimit);
                
            }
        }
    }
    return make_pair(nextLimit,NULL);
}