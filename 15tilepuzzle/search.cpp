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
    if(isGoal(root))
    {
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
            for(int i=0; i<4; i++)
            {
                nodo nLinha = move(n,i);
                if(nLinha != NULL)
                {
                    gen++;
                    if(isGoal(nLinha))
                    {
                        imprimeNodo(n);
                        int count = extractPath(n);
                        printf("Comprimento: %d\n", count);
                        printf("Nodos Gerados: %d\n", gen);
                        printf("Nodos Expandidos: %d", exp);
                        return 1;
                    }
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


