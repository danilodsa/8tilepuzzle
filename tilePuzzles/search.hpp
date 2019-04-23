/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   search.hpp
 * Author: danilo
 *
 * Created on 17 de Abril de 2019, 13:34
 */

#ifndef SEARCH_HPP
#define SEARCH_HPP

int bfsGraph(nodo root);
int idfs(nodo root);
int depth_limited_search(nodo root, int limit);
int astar(nodo root);
int idastar(nodo root);
std::pair<int,int> idastar_recursive_serach(nodo n,int fLimit);
int gbfs(nodo root);

#endif /* SEARCH_HPP */

