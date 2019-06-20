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
	int inicia(vector< pair< pair<string,int>, Valor_t> > &var);
	int simplificaListaParam(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var);
	int simplificaIL(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var, int enumType);
	Exp* simplificaExp(No_arv_parse * no, vector< pair< pair<string,int>, Valor_t> > &var);
	void simplificaFun(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var);
	void calcula(vector< pair< pair<string,int>, Valor_t> > &var);
};

#endif
