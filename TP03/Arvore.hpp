#ifndef _ARVORE_HPP_
#define _ARVORE_HPP_
#include<vector>
#include<string>
using namespace std;
#include "Exp.hpp"

class Exp;
class No_arv_parse {
public:
  string simb;
  int regra; // -1 = terminal
  string dado_extra;
  vector<No_arv_parse *> filhos;
  No_arv_parse();
};

class Arvore {
public:
  No_arv_parse * raiz;
  Arvore(No_arv_parse * rr);
  void imprime(No_arv_parse * no);
  void debug();
  Exp* simplificaExp(No_arv_parse * no);
  Exp* simplifica_simbolos();
};

#endif
