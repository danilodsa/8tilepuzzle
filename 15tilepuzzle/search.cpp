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
    rel->vMedio = rel->vMedio/rel->comp;
    
    //imprime relatório
    printf("___e:%d\t c:%d\t t:%f\t vm:%d\t hi:%d\n", rel->exp, rel->comp, rel->tempo, rel->vMedio, rel->hIni);
    //printf("%d, %d, %f, %d, %d", rel->exp, rel->comp, rel->tempo, rel->vMedio, rel->hIni);
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
        }
        else{
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
    if(isGoal(root))
    {
        relFinaliza(rel, root);
        return 1;
    }
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
            rel->exp++;
            for(int i=0; i<4; i++)
            {
                nodo nLinha = move(n,i);
                if(nLinha != NULL)
                {
                    if(isGoal(nLinha))
                    {
                        /*IMPRIMIR dados*/
                        relFinaliza(rel, nLinha);
                        return 1;
                    }
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


