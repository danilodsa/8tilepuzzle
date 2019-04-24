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

/*************************Relatório*************************/
relat relCria(nodo root)
{
    relat novo = (relat) malloc(sizeof(struct Relatorio));
    
    if(novo != NULL)
    {
        //exp, comp, tempo, vMedio, hIni, start, end
        novo->exp=0;
        novo->comp=0;
        novo->tempo=0;
        novo->vMedio=0;
        novo->hIni = root->h;
        novo->start= (double) clock();
        novo->end=0;
        
        return novo;
    }
    /*Se nao criar o nodo*/
    exit(1);
}

void relCalculaVMedio(relat rel, nodo n)
{
    if(n->pai!=NULL)
        relCalculaVMedio(rel, n->pai);
    //imprimeNodo(n);
    rel->comp++;
    rel->vMedio += n->h;
}

void relFinaliza(relat rel, nodo final)
{
    //finaliza o timer e calcula temcriaRelatoriopo total
    rel->end = (double) clock();
    rel->tempo = (double) (rel->end-rel->start)/CLOCKS_PER_SEC;
    
    //calcula vmedio e comp
    //printf("Imprimindo Caminho percorrido.\n");
    relCalculaVMedio(rel, final);
    rel->comp--;//desconsiderando o pai do caminho
    int x = extractPath(final);
    printf("_#_%d\n",x);
    rel->vMedio = rel->vMedio/rel->comp;
    
    //imprime relatório
    printf("___e:%d, c:%d, t:%f, vm:%d, hi:%d\n", rel->exp, rel->comp, rel->tempo, rel->vMedio, rel->hIni);
    //printf("%d, %d, %f, %d, %d", rel->exp, rel->comp, rel->tempo, rel->vMedio, rel->hIni);
}

/**************************BFS******************************/
int bfsGraph(nodo root)
{
    relat rel = relCria(root);
    int geradosCount = 0;
    
    /*cria closed set*/
    unordered_map<int,nodo> closed;
    /***********/
    /*Verifica se a raiz nao e GOAL*/
    if(isGoal(root))            
    {
        relFinaliza(rel, root);
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
        rel->exp++;
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
                        relFinaliza(rel, nLinha);
                        return 1;
                    }
                }

            }
        }
   }
    /*Nao tem solucao*/
    return 0;
}

/**************************IDFS******************************/
int idfs(nodo root)
{
    relat rel = relCria(root);
    
    for(int limit=0; limit<1000; limit++)
    {
        //printf("limit %d \n",limit);
        rel->exp=0;
        int solution = depth_limited_search(root, limit, rel);
        if(solution == 1)
        {
            return 1;
        }
    }            
    return 0;
}

            
int depth_limited_search(nodo n, int limit, relat rel)
{
    /*Verifica se e GOAL*/
    if(isGoal(n))
    {
        relFinaliza(rel, n);
        return 1;
    }
    
    if(limit > 0)
    {
        rel->exp++;
        /*Para cada nodo filho gerado*/
        for(int i=0; i<4;i++)
        {
            nodo nLinha = move(n,i);
            if(nLinha != NULL)
            {
                /*Recursao*/
                int solution = depth_limited_search(nLinha,(limit-1), rel);
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
            return 1;
        }
        else if(lhsF < rhsF){
            return 0;
        }
        else if(lhs->h > rhs->h){
            return 1;
        }else
        {
            return 0;
        }
  }
};


int astar(nodo root)
{
    relat rel = relCria(root);
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
                relFinaliza(rel, n);
                return 1;
            }
            rel->exp++;
            for(int i=0; i<4; i++)
            {
                nodo nLinha = move(n,i);
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
    return 0;
}

/**************************IDASTAR******************************/
int idastar(nodo root)
{
    relat rel = relCria(root);
    
    int fLimit = root->h;
    while(fLimit != INFINITY)
    {
        pair<int,int> ret = idastar_recursive_search(root,fLimit, rel);
        fLimit = ret.first;
        int solution = ret.second;
        if(solution != 0)
        {
            return 1;
        }
    }
    return 0;
        
}

pair<int,int> idastar_recursive_search(nodo n,int fLimit, relat rel)
{
    int fn = n->g + n->h;
    
    if(fn > fLimit)
    {
        return make_pair(fn,0);
    }

    if(isGoal(n))
    {
        imprimeNodo(n);
        relFinaliza(rel, n);
        return make_pair(NULL,1);
    }
    
    int  nextLimit = INFINITY;
    /*Para cada filho GERADO*/
    rel->exp++;
    for(int i=0; i<4; i++)
    {
        nodo nLinha = move(n,i);
        if(nLinha != NULL)
        {
            if(nLinha->h < INFINITY)
            {
                pair<int,int> ret = idastar_recursive_search(nLinha,fLimit, rel);
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
        if(lhs->h > rhs->h){
            return 1;
        }else
        {
            return 0;
        }
  }
};


int gbfs(nodo root)
{
    relat rel = relCria(root);
    
    /*open set*/
    priority_queue<nodo,vector<nodo>,compareForGBFS> open;
    
    /*closed set*/
    unordered_map<int,nodo> closed;
    
    if(isGoal(root))
    {
        relFinaliza(rel, root);
        return 1;
    }
    open.push(root);
    
    while(!open.empty())
    {
        nodo n = open.top();
        open.pop();
        if(closed.count(n->id) <= 0)
        {
            closed.emplace(n->id,n);
            rel->exp++;
            for(int i=0;i<4;i++)
            {
                nodo nLinha = move(n,i);
                if(nLinha != NULL)
                {
                    if(isGoal(nLinha))
                    {
                        imprimeNodo(nLinha);
                        relFinaliza(rel, nLinha);
                        return 1;
                    }
                    open.push(nLinha);
                }
            }
        }
    }
    return 0;
}