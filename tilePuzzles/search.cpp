#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>
#include "nodo.hpp"
#include "search.hpp"
#include <cmath>
#include <time.h>

using namespace std;

/**************************BFS******************************/
int bfsGraph(nodo root)
{
    clock_t start, end, total;
    start = clock();
    int geradosCount = 0;
    int exp = 0;    
    /*cria closed set*/
    unordered_map<int,nodo> closed;
    /***********/
    /*Verifica se a raiz nao e GOAL*/
    if(isGoal(root))
    {
        end = clock();
        total = (double)(end - start)/CLOCKS_PER_SEC;
        printf("%d,%d,%f,%d,%d",exp,0,total,0,root->h);
        return 1;
    }
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
        exp++;
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
                        end = clock();
                        total = (double)(end - start)/CLOCKS_PER_SEC;
                        printf("%d,%d,%f,%d,%d",exp,0,total,0,root->h);                        
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
int idfs(nodo root)
{
    for(int limit=0; limit<1000; limit++)
    {
        printf("limit %d \n",limit);
        int solution = depth_limited_search(root,limit);
        if(solution == 1)
        {
            return 1;
        }
    }
    return 0;
}


int depth_limited_search(nodo n, int limit)
{
    /*Verifica se e GOAL*/
    if(isGoal(n))
    {
        return 1;
    }
    
    if(limit > 0)
    {
        /*Para cada nodo filho gerado*/
        for(int i=0; i<4;i++)
        {
            nodo nLinha = move(n,i);
            if(nLinha != NULL)
            {
                /*Recursao*/
                int solution = depth_limited_search(nLinha,(limit-1));
                free(nLinha);
                if(solution == 1)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**************************ASTAR******************************/

class compareForAStar
{
  bool reverse;
public:
  compareForAStar(const bool& revparam=false)
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
    priority_queue<nodo,vector<nodo>,compareForAStar> open;
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
                int count = extractPath(n);
                printf("Comprimento: %d\n", count);
                printf("Nodos Gerados: %d\n", gen);
                printf("Nodos Expandidos: %d", exp);
                return 0;
            }
            for(int i=0; i<4; i++)
            {
                nodo nLinha = move(n,i);
                if(nLinha != NULL)
                {
                    gen++;
                    if(nLinha->h < INFINITY)
                    {
                        open.push(nLinha);
                    }
                }
            }
            exp++;
        }
                
    }
    
}

/**************************IDASTAR******************************/

int idastar(nodo root)
{
    int fLimit = root->h;
    while(fLimit != INFINITY)
    {
        pair<int,int> ret = idastar_recursive_search(root,fLimit);
        fLimit = ret.first;
        int solution = ret.second;
        if(solution != 0)
        {
            return 1;
        }
    }
    return 0;
        
}

pair<int,int> idastar_recursive_search(nodo n,int fLimit)
{
    int fn = n->g + n->h;
    
    if(fn > fLimit)
    {
        return make_pair(fn,0);
    }

    if(isGoal(n))
    {
        imprimeNodo(n);
        return make_pair(NULL,1);
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
                pair<int,int> ret = idastar_recursive_search(nLinha,fLimit);
                int recLimit = ret.first;
                int solution = ret.second;
                if (solution == 1)
                {
                    return make_pair(NULL,solution);
                }
                nextLimit = min(nextLimit,recLimit);
                
            }
        }
    }
    return make_pair(nextLimit,NULL);
}

/**************************GBFS******************************/

class compareForGBFS
{
  bool reverse;
public:
  compareForGBFS(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const nodo lhs, const nodo rhs) const
  {
//    if (reverse) return (lhs>rhs);
//    else return (lhs<rhs);
        int lhsF = lhs->h;
        int rhsF = rhs->h;

        if(lhsF > rhsF){
            return 0;
        }
        else if(lhsF < rhsF){
            return 1;
        }
        else{
            return 1;
        }      
  }
};


int gbfs(nodo root)
{
    /*open set*/
    priority_queue<nodo,vector<nodo>,compareForGBFS> open;
    
    /*closed set*/
    unordered_map<int,nodo> closed;
    
    if(isGoal(root))
    {
        return 0;
    }
    open.push(root);
    
    while(!open.empty())
    {
        nodo n = open.top();
        open.pop();
        if(closed.count(n->id) <= 0)
        {
            closed.emplace(n->id,n);
            for(int i=0;i<4;i++)
            {
                nodo nLinha = move(n,i);
                if(nLinha != NULL)
                {
                    if(isGoal(nLinha))
                    {
                        imprimeNodo(nLinha);
                        return 0;
                    }
                    open.push(nLinha);
                }
            }
        }

    }
    return 1;
    
}
