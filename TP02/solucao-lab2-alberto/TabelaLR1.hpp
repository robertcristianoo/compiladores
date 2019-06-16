#ifndef _TABELALR1_HPP_
#define _TABELALR1_HPP_
#include<vector>
#include<string>
#include<iostream>
#include<fstream>   
#include<sstream>
#include<map>
using namespace std;

class Transicao {
public:
  int tipo; // 0-vazio, 1 - shift, 2 - goto, 3-reduz, 4-aceita
  int reducao; // qual regra no vetor de gramatica
  int prox_estado;
  string impressao();
  Transicao(string tok); 
};

class Tabela_LR1 {
public:
  map<string,int> simbolo_coluna;
  vector<vector<Transicao> > Tab;
  void debug();
  Tabela_LR1(ifstream &arq_tabela_lr1);
};

#endif
