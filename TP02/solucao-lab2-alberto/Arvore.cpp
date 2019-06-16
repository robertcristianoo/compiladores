#include "Arvore.hpp"
#include<iostream>
using namespace std;

No_arv_parse::No_arv_parse() {
  simb = "";
  regra = -1; //terminal
  dado_extra = "";
  filhos.clear();
}

Arvore_parse::Arvore_parse(No_arv_parse * rr) {
  raiz = rr;
}

void Arvore_parse::imprime(No_arv_parse * no) {
  cerr << "[" <<no->simb<<","<< no->regra << ","<<no->dado_extra << ":";
  for (int i = 0; i < no->filhos.size(); ++i) {
    imprime(no->filhos[i]);
  }
  cerr << "]";
}

void Arvore_parse::debug(){
  imprime(raiz);
  cerr << endl;
}

Exp* expressao_de_terminal(No_arv_parse * no) {
  if (no->simb == string("NUM")) {
    return new ExpNum(stoi(no->dado_extra));
  }
  if (no->simb == string("NUM_FLOAT")) {
    return new ExpNumFloat(stod(no->dado_extra));
  }
  if (no->simb == string("ID")) {
    return new ExpID(no->dado_extra);
  }
  if (no->simb == string("STRING")) {
    return new ExpString(no->dado_extra);
  }
  return NULL;
}

/** Reaproveita nos e nao desaloca.*/
Exp* Arvore_parse::simplificado(No_arv_parse * no) {
  switch(no->regra) {
  case -1: return expressao_de_terminal(no); //terminal
  case 1: case 11: case 17: case 29: case 30: case 31: case 32:
    return simplificado(no->filhos[0]); // regra X -> Y e equivalentes
    break;
  case 25: return simplificado(no->filhos[1]); // C -> ( E )
  case 2: case 10: case 16:
    return new ExpDoisOp(OperadorBin::gera_operador_bin(no->filhos[1]->regra), simplificado(no->filhos[0]), simplificado(no->filhos[2]));
  case 26: case 27: case 28: 
    return new ExpUmOp(OperadorUnario::gera_operador_unario(no->regra), simplificado(no->filhos[1]));
  default:
    return NULL;
  }
}

Exp* Arvore_parse::simplifica_simbolos() {
  return simplificado(raiz);
}

